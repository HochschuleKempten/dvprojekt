#include "Server.h"
#include <boost\asio\placeholders.hpp>
#include <iostream>

namespace Network {

CServer::CServer() :
CNode(), m_acceptor(m_ioService) {
}

CServer::~CServer() {
}

void CServer::stop() {
	m_ioService.post([this]() {
		m_acceptor.close();
	});
	CNode::stop();
}

bool CServer::connect() {
	// start the tcp server and wait for incoming connections
	m_acceptor.open(m_localEndpointTcp.protocol());
	m_acceptor.bind(m_localEndpointTcp);
	m_acceptor.listen(0);
	m_socketTcp = ip::tcp::socket(m_ioService);

	m_acceptor.async_accept(m_socketTcp,
		boost::bind(&CServer::acceptCompleteHandler, this, placeholders::error)
	);
	std::cout << "Server started. Waiting for incoming connections..." << std::endl;

	// start the udp server and wait for incoming search requests
	m_socketUdp.open(m_localEndpointUdp.protocol());
	m_socketUdp.bind(m_localEndpointUdp);
	m_socketUdp.async_receive_from(buffer(m_acUdpMessage),
		m_remoteEndpointUdp,
		boost::bind(&CServer::udpDataRecievedHandler, this, placeholders::error, placeholders::bytes_transferred)
	);

	// currently nothing can go wrong here
	return true;
}

void CServer::acceptCompleteHandler(const error_code& error) {
	if (!error) {
		m_socketTcp.set_option(ip::tcp::no_delay(true));

		std::cout << "Connected to client " << m_socketTcp.remote_endpoint() << std::endl;

		m_acceptor.close();
		m_bConnected = true;
		readHeader();

		//startPing(m_socketTcp.remote_endpoint().address().to_string());
		
		m_connectionTimer.expires_from_now(boost::posix_time::seconds(0));
		m_connectionTimer.async_wait(boost::bind(&CNode::checkConnectionHandler, this, placeholders::error));
	} else {
		handleConnectionError(error);
	}
}

void CServer::udpDataRecievedHandler(const boost::system::error_code& error, std::size_t /*bytesTransferred*/) {
	if (!error) {
		// TODO check message content

		std::string stMessage = "Testgame"; // TODO make variable
		m_socketUdp.async_send_to(buffer(stMessage.c_str(), stMessage.length()), 
			m_remoteEndpointUdp,
			boost::bind(&CServer::udpDataSentHandler, this, placeholders::error, placeholders::bytes_transferred)
		);

	} else {
		handleConnectionError(error);
	}
}

void CServer::udpDataSentHandler(const boost::system::error_code& error, std::size_t /*bytesTransferred*/) {
	handleConnectionError(error);
}

}