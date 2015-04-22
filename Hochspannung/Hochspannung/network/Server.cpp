#include "Server.h"
#include <boost\asio\placeholders.hpp>
#include <iostream>

namespace Network {

CServer::CServer(unsigned short usPort) :
CNode(), m_acceptor(m_ioService), m_endpoint(ip::tcp::endpoint(ip::tcp::v4(), usPort)) {
}

CServer::~CServer() {
}

bool CServer::connect() {
	m_acceptor.open(m_endpoint.protocol());
	m_acceptor.bind(m_endpoint);
	m_acceptor.listen(0);

	m_socket = ip::tcp::socket(m_ioService);

	m_acceptor.async_accept(m_socket, 
		boost::bind(&CServer::acceptCompleteHandler, this, placeholders::error)
	);

	return true;
}

void CServer::acceptCompleteHandler(const error_code& ec) {
	if (!ec) {
		std::cout << "Connected to client " << m_socket.remote_endpoint() << std::endl;

		m_acceptor.close();
		m_bConnected = true;
		readHeader();
	} else {
		handleConnectionError(ec);
	}
}

}