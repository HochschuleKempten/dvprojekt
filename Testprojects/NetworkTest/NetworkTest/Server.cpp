#include "Server.h"
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <iostream>

CServer::CServer(io_service& io_service, const ip::tcp::endpoint& endpoint) : 
	m_io_service(io_service), m_acceptor(io_service, endpoint), m_socket(io_service) {
}

CServer::~CServer() {
}

void CServer::close() {
	m_io_service.post(
		[this]() {
			m_socket.close(); 
		}
	);
}

void CServer::write(const CMessage& msg) {
	m_io_service.post(
		[this, msg]() {
			bool write_in_progress = !m_dequeMessageWrite.empty();
			m_dequeMessageWrite.push_back(msg);

			if (!write_in_progress) {
				do_write();
			}
		}
	);
}

void CServer::do_accept() {
	m_acceptor.async_accept(m_socket, 
		[this](boost::system::error_code ec) {

			if (!ec) {
				std::cout << "Connected to client " << this->m_socket.remote_endpoint() << std::endl;
				do_readHeader();
			}
		}
	);
}

void CServer::do_write() {
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


void CServer::do_readHeader() {
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

void CServer::do_readBody() {
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