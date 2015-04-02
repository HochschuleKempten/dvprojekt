#include "Client.h"
#include <boost\asio\connect.hpp>
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <iostream>

CClient::CClient(io_service& io_service) :
	m_io_service(io_service), m_socket(io_service) {
}

CClient::~CClient() {
}

void CClient::close() {
	m_io_service.post([this]() {
		m_socket.close();
	});
}

void CClient::write(const CMessage& msg) {
	m_io_service.post([this, msg]() {
		bool write_in_progress = !m_dequeMessageWrite.empty();
		m_dequeMessageWrite.push_back(msg);

		if (!write_in_progress) {
			do_write();
		}
	});
}

void CClient::do_connect(ip::tcp::resolver::iterator& endpoint_iterator) {
	async_connect(m_socket,
		endpoint_iterator,
		[this](error_code ec, ip::tcp::resolver::iterator iterator) {
			if (!ec) {
				std::cout << "Connected to server " << this->m_socket.remote_endpoint() << std::endl;
				do_readHeader();
			} else {
				std::cout << ec.message() << std::endl;
			}
		}
	);
}

void CClient::do_write() {
	async_write(m_socket,
		buffer(m_dequeMessageWrite.front().getData(), m_dequeMessageWrite.front().getLength()),
		[this](error_code ec, std::size_t length) {

			if (!ec) {
				m_dequeMessageWrite.pop_front();

				if (!m_dequeMessageWrite.empty()) {
					do_write();
				}
			} else {
				m_socket.close();
			}
		}
	);
}

void CClient::do_readHeader() {
	async_read(m_socket, 
		buffer(m_messageRead.getData(), CMessage::headerLength),
		[this](error_code ec, std::size_t length) {

			if (!ec && m_messageRead.decodeHeader()) {
				do_readBody();
			} else {
				m_socket.close();
			}
		}
	);
}

void CClient::do_readBody() {
	async_read(m_socket,
		buffer(m_messageRead.getBody(), m_messageRead.getBodyLength()),
		[this](error_code ec, std::size_t length) {

			if (!ec) {
				std::cout << ">>";
				std::cout.write(m_messageRead.getBody(), m_messageRead.getBodyLength());
				std::cout << "\n";
				do_readHeader();
			} else {
				m_socket.close();
			}
		}
	);
}
