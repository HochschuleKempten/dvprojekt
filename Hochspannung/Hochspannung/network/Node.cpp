#include "Node.h"
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <boost\asio\placeholders.hpp>
#include <boost\lexical_cast.hpp>
#include <vector>

namespace Network {

CNode::CNode() :
m_ioService(io_service()), m_socket(m_ioService), m_bConnected(false), m_bCheckResponseReceived(true), m_connectionTimer(m_ioService) {

	try {
		m_pPinger = new CPinger(m_ioService);
	} catch (boost::system::system_error error) {
		if (error.code().value() == WSAEACCES) {
			std::cout << "Please restart the program as admin to use the ping." << std::endl;
		} else {
			std::cout << error.what() << std::endl;
		}
	}
}

CNode::~CNode() {
	delete m_pPinger;
	m_thread.join();
}

bool CNode::start() {
	if (!isConnected()) {
		if (connect()) {
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
		}
	}
	
	return false;
}

void CNode::stop() {
	m_connectionTimer.cancel();
	m_ioService.post([this]() {
		m_socket.close();
	});
	m_thread.join();
}

void CNode::restart() {
	stop();
	start();
}

bool CNode::isConnected() {
	return m_bConnected;
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
	async_write(m_socket,
		buffer(m_dequeMessagesToWrite.front().getData(), m_dequeMessagesToWrite.front().getLength()),
		boost::bind(&CNode::writeCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::readHeader() {
	async_read(m_socket,
		buffer(m_messageRead.getData(), CMessage::iHeaderLength),
		boost::bind(&CNode::readHeaderCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::readBody() {
	async_read(m_socket,
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

		std::cout << m_messageRead.getBody() << std::endl;


		const char* pcMessage = m_messageRead.getBody();
		std::string stMessage = retrieveString((char*)pcMessage, 512);

		std::vector<std::string> transferObjectMember;
		std::stringstream ss(stMessage); // Turn the string into a stream.
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

		switch (transferObject.getAction()) {
		case Action::CHECK_CONNECTION:
			write(CMessage((boost::lexical_cast<std::string>(Action::CHECK_RESPONSE) + ";-1;-1;-1;;").c_str()));
			break;
		case Action::CHECK_RESPONSE:
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
			m_bConnected = false;
			std::cout << "Connection refused by remote computer." << std::endl;
			break;

		case WSAECONNRESET:
			m_bConnected = false;
			std::cout << "Connection was closed by remote host." << std::endl;
			break;

		case ERROR_SEM_TIMEOUT: // Connection attempt timed out
			m_bConnected = false;
			std::cout << "Connection attempt timed out." << std::endl;
			break;

		case ERROR_CONNECTION_ABORTED:
			m_bConnected = false;
			std::cout << "Connection was closed locally." << std::endl;
			break;

		default:
			m_bConnected = false;
			std::cout << "System Error: " << ec.message() << std::endl;
			break;
		}
	} else {
		m_bConnected = false;
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

void CNode::startPing(std::string stIP) {
	m_pPinger->start(stIP);
}

void CNode::stopPing() {
	m_pPinger->stop();
}

int CNode::getLatency() {
	return m_pPinger->getLatestLatency();
}

void CNode::checkConnectionHandler(const error_code& error) {
	if (!error) {
		if (m_bCheckResponseReceived) {
			m_bCheckResponseReceived = false;
			std::string stMessage = boost::lexical_cast<std::string>(Action::CHECK_CONNECTION) + ";-1;-1;-1;;";
			CMessage message(stMessage.c_str());
			write(message);

			m_connectionTimer.expires_from_now(boost::posix_time::seconds(2));
			m_connectionTimer.async_wait(boost::bind(&CNode::checkConnectionHandler, this, placeholders::error));
		} else {
			m_bConnected = false;
			std::cout << "Connection lost." << std::endl;
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