#include "Client.h"
#include <boost\asio\placeholders.hpp>
#include <boost\asio\connect.hpp>
#include <iostream>

CClient::CClient(std::string ip, std::string port) :
CComputer() {
	m_endpointIterator = ip::tcp::resolver(m_io_service).resolve({ ip, port });
}

CClient::~CClient() {
}

void CClient::connect() {
	async_connect(m_socket, 
		m_endpointIterator,
		boost::bind(&CClient::connectCompleteHandler, this, placeholders::error, placeholders::iterator)
	);
}

void CClient::connectCompleteHandler(const boost::system::error_code& ec, ip::tcp::resolver::iterator iterator) {
	if (!ec) {
		std::cout << "Connected to server " << m_socket.remote_endpoint() << std::endl;

		m_dequeTextToPrint.emplace_back("Connected to server " + m_socket.remote_endpoint().address().to_string());

		readHeader();
	} else {
		std::cout << "Connecting to server failed: " << ec.message() << std::endl;

		m_dequeTextToPrint.emplace_back(ec.message());
	}
}

void CClient::writeCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec) {
		m_dequeMessagesToWrite.pop_front();

		if (!m_dequeMessagesToWrite.empty()) {
			do_write();
		}
	} else {
		m_socket.close();
	}
}

void CClient::readHeaderCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
	if (!ec && m_messageRead.decodeHeader()) {
		readBody();
	} else {
		m_socket.close();
	}
}

void CClient::readBodyCompleteHandler(const boost::system::error_code& ec, std::size_t length) {
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