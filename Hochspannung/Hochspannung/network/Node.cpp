#include "Node.h"
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <boost\asio\placeholders.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <vector>

namespace Network {

CNode::CNode() :
m_ioService(io_service()), m_socketTcp(m_ioService), m_socketUdp(m_ioService), m_localEndpointTcp(ip::tcp::endpoint(ip::tcp::v4(), m_usPortTcp)),
m_localEndpointUdp(ip::udp::endpoint(ip::udp::v4(), m_usPortUdp)),
m_connectionState(CLOSED),
m_bCheckResponseReceived(true), m_connectionTimer(m_ioService), m_iLatestLatency(-1) {

}

CNode::~CNode() {
	m_thread.join();
}

bool CNode::start() {
	if (m_connectionState == CLOSED && connect()) {
		// start the thread if not already running
		if (!m_thread.try_join_for(boost::chrono::duration<int>())) {
			m_thread = boost::thread([this]() {
				try {
					m_ioService.run();
				} catch (boost::system::system_error error) {
					std::cout << "Unexpected Exception occurred while running io_service!" << std::endl;
				}
			});
		}

		return true;
	} else {
		return false;
	}
}

void CNode::stop() {
	m_connectionTimer.cancel();
	m_ioService.post([this]() {
		m_socketTcp.close();
		m_socketUdp.close();

	});
	m_thread.join();
	m_ioService.reset();
	m_connectionState = CLOSED;
	std::cout << "Stopped node." << std::endl;
}

void CNode::restart() {
	stop();
	start();
}

State CNode::getConnectionState() {
	return m_connectionState;
}

void CNode::write(const CMessage& message) {
	m_ioService.post([this, message]() {
		bool write_in_progress = !m_dequeMessagesToWrite.empty();
		m_dequeMessagesToWrite.push_back(message);

		if (!write_in_progress) {
			do_write();
		}
	});
}

void CNode::do_write() {
	async_write(m_socketTcp,
		buffer(m_dequeMessagesToWrite.front().getData(), m_dequeMessagesToWrite.front().getLength()),
		boost::bind(&CNode::writeCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::readHeader() {
	async_read(m_socketTcp,
		buffer(m_messageRead.getData(), CMessage::iHeaderLength),
		boost::bind(&CNode::readHeaderCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::readBody() {
	async_read(m_socketTcp,
		buffer(m_messageRead.getBody(), m_messageRead.getBodyLength()),
		boost::bind(&CNode::readBodyCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::writeCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {
		m_dequeMessagesToWrite.pop_front();

		if (!m_dequeMessagesToWrite.empty()) {
			do_write();
		}
	} else {
		handleConnectionError(ec);
	}
}

void CNode::readHeaderCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {
		if (m_messageRead.decodeHeader()) { // message is to long
			readBody();
		}
	} else {
		handleConnectionError(ec);
	}
}

void CNode::readBodyCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {

		const char* pcMessage = m_messageRead.getBody();
		std::string stMessage = retrieveString((char*)pcMessage, 512);

		std::vector<std::string> transferObjectMember;
		std::stringstream ss(stMessage); // Turn the std::string into a stream.
		std::string tok;

		while (getline(ss, tok, ';')) {
			transferObjectMember.push_back(tok);
		}

		CTransferObject transferObject(
			static_cast<Action>(boost::lexical_cast<int>(transferObjectMember.at(0))), 
			boost::lexical_cast<int>(transferObjectMember.at(1)), 
			boost::lexical_cast<int>(transferObjectMember.at(2)), 
			boost::lexical_cast<int>(transferObjectMember.at(3)), 
			transferObjectMember.at(4)
		);

		boost::posix_time::ptime timeSent;

		switch (transferObject.getAction()) {
		case Action::CHECK_CONNECTION:
			write(CMessage((boost::lexical_cast<std::string>(Action::CHECK_RESPONSE) + ";-1;-1;-1;" + transferObject.getValue() + ";").c_str()));
			break;
		case Action::CHECK_RESPONSE:
			timeSent = boost::posix_time::from_iso_string(transferObject.getValue());
			m_iLatestLatency = static_cast<int>((boost::posix_time::microsec_clock::universal_time() - timeSent).total_milliseconds()) / 2;
			std::cout << m_iLatestLatency << std::endl;
			m_bCheckResponseReceived = true;
			break;
		default:
			m_dequeActionsToExecute.push_back(transferObject);
			break;
		}

		readHeader();
	} else {
		handleConnectionError(ec);
	}
}

void CNode::handleConnectionError(const error_code& ec) {
	if (ec.category() == boost::system::system_category()) {
		switch (ec.value()) {
		case ERROR_SUCCESS:
			// no error
			break;

		case ERROR_CONNECTION_REFUSED:
			m_connectionState = CLOSED;
			std::cout << "Connection refused by remote computer." << std::endl;
			break;

		case WSAECONNRESET:
			m_connectionState = CLOSED;
			m_connectionTimer.cancel();
			std::cout << "Connection was closed by remote host." << std::endl;
			break;

		case ERROR_SEM_TIMEOUT:
			m_connectionState = CLOSED;
			std::cout << "Connection attempt timed out." << std::endl;
			break;

		case ERROR_CONNECTION_ABORTED:
			m_connectionState = CLOSED;
			m_connectionTimer.cancel();
			std::cout << "Connection was aborted by the local system." << std::endl;
			break;
		
		case ERROR_OPERATION_ABORTED:
			// If you end up here without any previously requested close operations, check the threads.
			// But in most cases this error is thrown because a socket is closed and all pending handler are canceled.

			m_connectionState = CLOSED;
			//std::cout << "The operation has been aborted." << std::endl;
			break;

		default:
			m_connectionState = CLOSED;
			std::cout << "System Error: " << ec.message() << std::endl;
			break;
		}
	} else {
		m_connectionState = CLOSED;
		std::cout << "Error: " << ec.message() << std::endl;
	}
}

CTransferObject CNode::getNextActionToExecute() {
	CTransferObject transferObject;

	if (!m_dequeActionsToExecute.empty()) {
		transferObject = m_dequeActionsToExecute.front();
		m_dequeActionsToExecute.pop_front();
	}

	return transferObject;
}

bool CNode::isActionAvailable() {
	return !m_dequeActionsToExecute.empty();
}

int CNode::getLatency() {
	return m_iLatestLatency;
}

void CNode::checkConnectionHandler(const error_code& error) {
	if (!error) {
		if (m_bCheckResponseReceived) {
			m_bCheckResponseReceived = false;

			std::string stMessage = boost::lexical_cast<std::string>(Action::CHECK_CONNECTION) + ";-1;-1;-1;" + to_iso_string(boost::posix_time::microsec_clock::universal_time()) + ";";
			CMessage message(stMessage.c_str());
			write(message);

			m_connectionTimer.expires_from_now(boost::posix_time::seconds(2));
			m_connectionTimer.async_wait(boost::bind(&CNode::checkConnectionHandler, this, placeholders::error));
		} else {
			m_connectionState = CLOSED;
			m_iLatestLatency = -1;
			std::cout << "Connection lost." << std::endl;

			// TODO Reaction??
		}
	} else if (error != error::operation_aborted) {
		std::cout << error.message() << std::endl;
	}
}

std::string CNode::retrieveString(char* mes, unsigned int maxLen) {
	size_t len = 0;
	while ((len < maxLen) && (mes[len] != '\0')) {
		len++;
	}
	return std::string(mes, len);
}

}