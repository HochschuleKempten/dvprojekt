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
		if (m_pzwConsole != 0) {
			m_pzwConsole->PrintString("Connected to client");
		} else {
			std::cout << "Connected to client " << m_socket.remote_endpoint() << std::endl;
		}
		readHeader();
	} else {
		if (m_pzwConsole != 0) {
			char acText[20];
			memcpy(acText, ec.message().data(), 20);
			m_pzwConsole->PrintString(acText);
		} else {
			std::cout << "Connecting to client failed: " << ec.message() << std::endl;
		}
	}
}

void CServer::writeCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec) {
		m_dequeMessageWrite.pop_front();

		if (!m_dequeMessageWrite.empty()) {
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
		if (m_pzwConsole != 0) {
			char acText[20];
			memcpy(acText, m_messageRead.getBody(), 20);
			m_pzwConsole->PrintString(acText);
		} else {
			std::cout << ">>";
			std::cout.write(m_messageRead.getBody(), m_messageRead.getBodyLength());
			std::cout << "\n";
		}
		readHeader();
	} else {
		m_socket.close();
	}
}