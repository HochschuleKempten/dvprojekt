#include "Node.h"
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <boost\asio\placeholders.hpp>
#include <boost\lexical_cast.hpp>
#include <vector>
#include "..\logic\LUtility.h"

namespace Network {

CNode::CNode() :
m_ioService(io_service()), m_socket(m_ioService), m_timer(m_ioService), m_bConnected(false) {
}

CNode::~CNode() {
	m_thread.join();
}

bool CNode::start() {
	if (!isConnected()) {
		if (connect()) {
			if (!m_thread.try_join_for(boost::chrono::duration<int>())) {
				m_thread = boost::thread([this]() {
					m_ioService.run();
				});
			}

			return true;
		}
	}
	
	return false;
}

void CNode::stop() {
	m_ioService.post([this]() {
		m_socket.shutdown(ip::tcp::socket::shutdown_both);
		m_socket.close();
	});
	m_thread.join();

	m_bConnected = false;

	std::cout << "Connection closed" << std::endl;
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
		const char* pcMessage = m_messageRead.getBody();
		std::string stMessage = retrieveString(pcMessage, 512);
		std::vector<std::string> transferObjectMember = split(stMessage, ';');

		CTransferObject transferObject(
			static_cast<Action>(boost::lexical_cast<int>(transferObjectMember.at(0))), 
			boost::lexical_cast<int>(transferObjectMember.at(1)), 
			boost::lexical_cast<int>(transferObjectMember.at(2)), 
			boost::lexical_cast<int>(transferObjectMember.at(3)), 
			transferObjectMember.at(4)
		);

		m_dequeActionsToExecute.push_back(transferObject);

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
			std::cout << "Connection refused by remote computer -> Trying again..." << std::endl;

			m_timer.expires_from_now(boost::posix_time::seconds(1));
			m_timer.wait();
			connect(); // try to reconnect
			break;

		case WSAECONNRESET:
			m_bConnected = false;
			std::cout << "Connection was closed by remote host -> Trying to reconnect..." << std::endl;

			m_timer.expires_from_now(boost::posix_time::seconds(1));
			m_timer.wait();
			connect(); // try to reconnect
			break;

		default:
			m_bConnected = false;
			std::cout << "System Error: " << ec.message() << std::endl;

			m_ioService.post([this]() {
				m_socket.shutdown(ip::tcp::socket::shutdown_both);
				m_socket.close();
			}); // close connection, just to be sure
			break;
		}
	} else {
		m_bConnected = false;
		std::cout << "Error: " << ec.message() << std::endl;

		m_ioService.post([this]() {
			m_socket.shutdown(ip::tcp::socket::shutdown_both);
			m_socket.close();
		}); // close connection, just to be sure
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

std::string CNode::retrieveString(const char* mes, unsigned int maxLen) {
	size_t len = 0;
	while ((len < maxLen) && (mes[len] != '\0')) {
		len++;
	}
	return std::string(mes, len);
}

}