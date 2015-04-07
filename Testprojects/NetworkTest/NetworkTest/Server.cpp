#include "Server.h"
#include <boost\asio\placeholders.hpp>
#include <iostream>

CServer::CServer(int port) :
CComputer(), m_acceptor(m_io_service, ip::tcp::endpoint(ip::tcp::v4(), port)) {
}

CServer::~CServer() {
}

void CServer::connect() {
	m_acceptor.async_accept(m_socket, 
		boost::bind(&CServer::acceptCompleteHandler, this, placeholders::error)
	);
}

void CServer::acceptCompleteHandler(const boost::system::error_code& ec) {
	if (!ec) {
		std::cout << "Connected to client " << m_socket.remote_endpoint() << std::endl;

		m_dequeTextToPrint.emplace_back("Connected to client " + m_socket.remote_endpoint().address().to_string());

		readHeader();
	} else {
		std::cout << "Connecting to client failed: " << ec.message() << std::endl;

		m_dequeTextToPrint.emplace_back(ec.message());
	}
}

void CServer::writeCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec) {
		m_dequeMessagesToWrite.pop_front();

		if (!m_dequeMessagesToWrite.empty()) {
			do_write();
		}
	} else {
		m_socket.close();
	}
}

void CServer::readHeaderCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec && m_messageRead.decodeHeader()) {
		readBody();
	} else {
		m_socket.close();
	}
}

void CServer::readBodyCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec) {
		std::cout << ">>";
		std::cout.write(m_messageRead.getBody(), m_messageRead.getBodyLength());
		std::cout << "\n";

		m_dequeTextToPrint.emplace_back(m_messageRead.getBody(), m_messageRead.getBodyLength());

		readHeader();
	} else {
		m_socket.close();
	}
}