#include "Node.h"
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <boost\asio\placeholders.hpp>

CNode::CNode() :
m_io_service(io_service()), m_socket(m_io_service), m_bConnected(false) {
}

CNode::~CNode() {
	m_thread.join();
}

void CNode::start() {
	if (!isConnected()) {
		connect();

		if (!m_thread.try_join_for(boost::chrono::duration<int>())) {
			m_thread = boost::thread([this]() {
				m_io_service.run();
			});
		}
	}
}

void CNode::stop() {
	m_io_service.post([this]() {
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
	m_io_service.post([this, message]() {
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
		buffer(m_messageRead.getData(), CMessage::headerLength),
		boost::bind(&CNode::readHeaderCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::readBody() {
	async_read(m_socket,
		buffer(m_messageRead.getBody(), m_messageRead.getBodyLength()),
		boost::bind(&CNode::readBodyCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::writeCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec) {
		m_dequeMessagesToWrite.pop_front();

		if (!m_dequeMessagesToWrite.empty()) {
			do_write();
		}
	} else {
		handleConnectionError(ec);
	}
}

void CNode::readHeaderCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec) {
		if (m_messageRead.decodeHeader()) { // message is to long
			readBody();
		}
	} else {
		handleConnectionError(ec);
	}
}

void CNode::readBodyCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec) {
		std::cout << ">>";
		std::cout.write(m_messageRead.getBody(), m_messageRead.getBodyLength());
		std::cout << "\n";

		readHeader();
	} else {
		handleConnectionError(ec);
	}
}

void CNode::handleConnectionError(const boost::system::error_code& ec) {
	switch (ec.value()) {
	case 0:
		// no error
		break;

	case boost::asio::error::connection_reset:
		m_bConnected = false;
		std::cout << "Lost connection -> Trying to reconnect..." << std::endl;
		connect(); // try to reconnect
		break;

	default:
		std::cout << "Error: " << ec.message() << std::endl;
		m_socket.close(); // close connection, just to be sure
		break;
	}
}