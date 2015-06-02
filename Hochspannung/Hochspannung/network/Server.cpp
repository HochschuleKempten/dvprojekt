#include "Server.h"
#include <boost\asio\placeholders.hpp>
#include <boost\property_tree\json_parser.hpp>
#include <iostream>

namespace Network {

CServer::CServer(std::string stName, std::string stLocalAddress) :
CNode(stLocalAddress), m_stName(stName), m_acceptor(m_ioService) {
}

CServer::~CServer() {
}

CNode::Type CServer::getType() {
	return SERVER;
}

void CServer::stop() {
	m_ioService.post([this]() {
		m_acceptor.close();
	});
	CNode::stop();
}

void CServer::setName(std::string stName) {
	m_stName = stName;
}

std::string CServer::getName() {
	return m_stName;
}

bool CServer::connect() {
	// start the tcp server and wait for incoming connections
	if (startTcpServer()) {
		m_acceptor.async_accept(m_socketTcp,
			boost::bind(&CServer::acceptCompleteHandler, this, placeholders::error)
		);
		m_connectionState = PENDING;
	} else {
		m_connectionState = CLOSED;
		return false;
	}

	// start the udp server and wait for incoming search requests
	if (startUdpServer()) {
		m_socketUdp.async_receive_from(m_udpMessage.prepare(512),
			m_remoteEndpointUdp,
			boost::bind(&CServer::udpDataRecievedHandler, this, placeholders::error, placeholders::bytes_transferred)
		);
	} else {
		// Do nothing as the UDP server is not essential for playing.
	}

	std::cout << "Server started. Waiting for incoming connections..." << std::endl;

	return true;
}


bool CServer::startTcpServer() {
	if (!m_acceptor.is_open()) {
		error_code error;

		m_acceptor.open(m_localEndpointTcp.protocol(), error);
		if (error) {
			handleConnectionError(error);
			return false;
		}

		m_acceptor.bind(m_localEndpointTcp, error);
		if (error) {
			handleConnectionError(error);
			return false;
		}

		m_acceptor.listen(0, error);
		if (error) {
			handleConnectionError(error);
			return false;
		}
	}

	return true;
}

bool CServer::startUdpServer() {
	if (!m_socketUdp.is_open()) {
		error_code error;

		m_socketUdp.open(m_localEndpointUdp.protocol(), error);
		if (error) {
			handleConnectionError(error);
			return false;
		}

		m_socketUdp.bind(m_localEndpointUdp, error);
		if (error) {
			handleConnectionError(error);
			return false;
		}
	}

	return true;
}

void CServer::acceptCompleteHandler(const error_code& error) {
	if (!error) {
		m_socketTcp.set_option(ip::tcp::no_delay(true));

		std::cout << "Connected to client " << m_socketTcp.remote_endpoint() << std::endl;

		m_acceptor.close();
		m_connectionState = CONNECTED;
		readHeader();

		m_connectionTimer.expires_from_now(boost::posix_time::seconds(0));
		m_connectionTimer.async_wait(boost::bind(&CNode::checkConnectionHandler, this, placeholders::error));
	} else {
		handleConnectionError(error);
	}
}

void CServer::udpDataRecievedHandler(const boost::system::error_code& error, std::size_t bytesTransferred) {
	if (!error) {
		// queue next message
		m_socketUdp.async_receive_from(m_udpMessage.prepare(512),
			m_remoteEndpointUdp,
			boost::bind(&CServer::udpDataRecievedHandler, this, placeholders::error, placeholders::bytes_transferred)
		);

		// parse received message
		boost::property_tree::ptree jsonTree;
		try {
			m_udpMessage.commit(bytesTransferred);
			boost::property_tree::read_json(std::istream(&m_udpMessage), jsonTree);

			std::string stName = jsonTree.get<std::string>("name", "");

			if (stName == "?") {
				std::string stMessage = "{ \"name\": \"" + m_stName + "\" }";
				m_socketUdp.async_send_to(buffer(stMessage.c_str(), stMessage.length()),
					m_remoteEndpointUdp,
					boost::bind(&CServer::udpDataSentHandler, this, placeholders::error, placeholders::bytes_transferred)
				);
			}
		} catch (boost::property_tree::ptree_error /*error*/) {
			// received message is invalid -> ignore it
		}

		// clear for next message
		m_udpMessage.consume(512);
	} else {
		handleConnectionError(error);
	}
}

void CServer::udpDataSentHandler(const boost::system::error_code& error, std::size_t /*bytesTransferred*/) {
	handleConnectionError(error);
}

}