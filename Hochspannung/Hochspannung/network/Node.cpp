#include "Node.h"
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <boost\asio\placeholders.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\date_time\posix_time\posix_time.hpp>

namespace Network {

CNode::CNode(std::string stLocalAddress) :
m_ioService(io_service()), m_work(m_ioService), m_socketTcp(m_ioService), m_socketUdp(m_ioService),
m_localEndpointTcp(ip::tcp::endpoint(ip::address_v4::from_string(stLocalAddress), m_usPortTcp)),
m_localEndpointUdp(ip::udp::endpoint(ip::address_v4::from_string(stLocalAddress), m_usPortUdp)), 
m_connectionState(CLOSED), m_bCheckResponseReceived(true), m_iRetryCounter(0), 
m_connectionTimer(m_ioService), m_iLatestLatency(-1) {
	
	m_thread = boost::thread([this]() {
		try {
			m_ioService.run();
		} catch (boost::system::system_error error) {
			std::cout << "Unexpected Exception occurred while running io_service: " << error.what() << std::endl;
		}
	});
}

CNode::~CNode() {
	m_ioService.stop();
	m_thread.join();
}

CNode::Type CNode::getType() {
	return NONE;
}

bool CNode::start() {
	if (m_connectionState == CLOSED && connect()) {
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
	m_connectionState = CLOSED;
	std::cout << "Stopped node." << std::endl;
}

void CNode::restart() {
	stop();
	start();
}

CNode::State CNode::getConnectionState() {
	return m_connectionState;
}

void CNode::write(CTransferObject& transferObject) {
	m_ioService.post([this, transferObject]() {
		bool write_in_progress = !m_dequeActionsToWrite.empty();
		m_dequeActionsToWrite.push_back(transferObject);

		if (!write_in_progress) {
			do_write();
		}
	});
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
			m_connectionState = CONNECTED;
			m_iRetryCounter = 0;

			CTransferObject transferObject(CTransferObject::Type::NORMAL, CTransferObject::Action::CHECK_CONNECTION, -1, -1, -1, 
				boost::posix_time::to_iso_string(boost::posix_time::microsec_clock::universal_time()));
			write(transferObject);

			m_connectionTimer.expires_from_now(boost::posix_time::seconds(2));
			m_connectionTimer.async_wait(boost::bind(&CNode::checkConnectionHandler, this, placeholders::error));
		} else {
			m_connectionState = CLOSED;
			m_iLatestLatency = -1;

			if (m_iRetryCounter < 5) {
				std::cout << "Connection lost. Try to reconnect. (" << m_iRetryCounter << ")" << std::endl;

				CTransferObject transferObject(CTransferObject::Type::NORMAL, CTransferObject::Action::CHECK_CONNECTION, -1, -1, -1,
					boost::posix_time::to_iso_string(boost::posix_time::microsec_clock::universal_time()));
				write(transferObject);

				m_connectionTimer.expires_from_now(boost::posix_time::seconds(2));
				m_connectionTimer.async_wait(boost::bind(&CNode::checkConnectionHandler, this, placeholders::error));

				m_iRetryCounter++;
			} else {
				std::cout << "Closing connection." << std::endl;
				stop();
			}

		}
	} else if (error != error::operation_aborted) {
		std::cout << error.message() << std::endl;
	}
}

void CNode::setLocalAddress(std::string stLocalAddress) {
	m_localEndpointTcp = ip::tcp::endpoint(ip::address_v4::from_string(stLocalAddress), m_usPortTcp);
	m_localEndpointUdp = ip::udp::endpoint(ip::address_v4::from_string(stLocalAddress), m_usPortUdp);
}

void CNode::do_write() {
	m_dequeActionsToWrite.front().encode();

	async_write(m_socketTcp,
		buffer(m_dequeActionsToWrite.front().getData(), m_dequeActionsToWrite.front().getDataLength()),
		boost::bind(&CNode::writeCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);

}

void CNode::readHeader() {
	async_read(m_socketTcp,
		buffer(m_messageRead.getData(), 1),
		boost::bind(&CNode::readHeaderCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::readBody() {
	async_read(m_socketTcp,
		buffer(&(m_messageRead.getData()[1]), static_cast<int>(m_messageRead.getData()[0])),
		boost::bind(&CNode::readBodyCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::writeCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {
		m_dequeActionsToWrite.pop_front();

		if (!m_dequeActionsToWrite.empty()) {
			do_write();
		}
	} else {
		handleConnectionError(ec);
	}
}

void CNode::readHeaderCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {
		readBody();
	} else {
		handleConnectionError(ec);
	}
}

void CNode::readBodyCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {
		m_messageRead.decode();

		boost::posix_time::ptime timeSent;

		switch (m_messageRead.getAction()) {
		case CTransferObject::Action::CHECK_CONNECTION:
			write(CTransferObject(CTransferObject::Type::NORMAL, CTransferObject::Action::CHECK_RESPONSE, -1, -1, -1, m_messageRead.getValue()));
			break;
		case CTransferObject::Action::CHECK_RESPONSE:
			timeSent = boost::posix_time::from_iso_string(m_messageRead.getValue());
			m_iLatestLatency = static_cast<int>((boost::posix_time::microsec_clock::universal_time() - timeSent).total_milliseconds()) / 2;
			std::cout << m_iLatestLatency << std::endl;
			m_bCheckResponseReceived = true;
			break;
		default:
			m_dequeActionsToExecute.push_back(m_messageRead);
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

}