#include "Client.h"
#include <boost\asio\placeholders.hpp>
#include <boost\asio\connect.hpp>
#include <iostream>

namespace Network {

CClient::CClient(std::string ip, std::string port) :
CNode(), m_resolver(m_io_service) {
	m_endpointIterator = ip::tcp::resolver(m_io_service).resolve({ip, port});
}

CClient::~CClient() {
}

void CClient::connect() {
	async_connect(m_socket, 
		m_endpointIterator,
		boost::bind(&CClient::connectCompleteHandler, this, placeholders::error, placeholders::iterator)
	);
}

void CClient::connectCompleteHandler(const error_code& ec, ip::tcp::resolver::iterator iterator) {
	if (!ec) {
		std::cout << "Connected to server " << m_socket.remote_endpoint() << std::endl;

		m_bConnected = true;
		readHeader();
	} else {
		handleConnectionError(ec);
	}
}

}