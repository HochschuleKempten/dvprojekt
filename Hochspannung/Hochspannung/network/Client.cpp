#include "Client.h"
#include <boost\asio\placeholders.hpp>
#include <boost\asio\connect.hpp>
#include <boost\lexical_cast.hpp>
#include <iostream>

namespace Network {

CClient::CClient(std::string stIP, unsigned short usPort) :
CNode(), m_bEndpointValid(false) {
	setServerData(stIP, boost::lexical_cast<std::string, unsigned short>(usPort));
}

CClient::~CClient() {
}

bool CClient::setServerData(std::string stIP, std::string usPort) {
	error_code ec;
	m_endpointIterator = ip::tcp::resolver(m_ioService).resolve({ stIP, usPort }, ec);

	if (!ec) {
		m_bEndpointValid = true;
		return true;
	} else {
		m_bEndpointValid = false;
		return false;
	}
}

bool CClient::connect() {
	if (m_bEndpointValid) {
		async_connect(m_socket,
			m_endpointIterator,
			boost::bind(&CClient::connectCompleteHandler, this, placeholders::error, placeholders::iterator)
		);

		return true;
	} else {
		return false;
	}
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