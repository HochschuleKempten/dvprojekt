#include "Client.h"
#include <boost\asio\placeholders.hpp>
#include <boost\asio\connect.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\property_tree\json_parser.hpp>
#include <iostream>

namespace Network {

CClient::CClient(std::string stIP, unsigned short usPortTcpServer) :
CNode(), m_bEndpointValid(false) {
	if (stIP != "") {
		setServerData(stIP, usPortTcpServer);
	}
}

CClient::~CClient() {
}

bool CClient::setServerData(std::string stIP, unsigned short usPortTcpServer) {
	try {
		m_remoteEndpointTcp = ip::tcp::endpoint(ip::address_v4::from_string(stIP), usPortTcpServer);
	} catch (...) {
		m_bEndpointValid = false;
		return false;
	}

	m_bEndpointValid = true;
	return true;
}

void CClient::searchGames() {
	if (!isConnected()) {
		if (!m_socketUdp.is_open()) {
			m_socketUdp.open(m_localEndpointUdp.protocol());
			m_socketUdp.bind(m_localEndpointUdp);
			m_socketUdp.set_option(socket_base::broadcast(true));
		}

		std::string stMessage("{ \"name\": \"?\"}");
		m_socketUdp.async_send_to(buffer(stMessage.c_str(), stMessage.length()),
			ip::udp::endpoint(ip::address_v4::broadcast(), m_usPortUdp),
			boost::bind(&CClient::udpDataSentHandler, this, placeholders::error, placeholders::bytes_transferred)
		);

		std::cout << "Started searching for game servers..." << std::endl;
		m_socketUdp.async_receive_from(m_udpMessage.prepare(512),
			m_remoteEndpointUdp,
			boost::bind(&CClient::udpDataRecievedHandler, this, placeholders::error, placeholders::bytes_transferred)
		);

		if (!m_thread.try_join_for(boost::chrono::duration<int>())) {
			m_thread = boost::thread([this]() {
				try {
					m_ioService.run();
				} catch (boost::system::system_error error) {
					std::cout << "Unexpected exception occurred while running io_service: " << error.what() << std::endl;
				}
			});
		}
	}
}

std::vector<CGameObject>& CClient::getGameList() {
	return m_gameList;
}

bool CClient::connect() {
	if (m_bEndpointValid) {
		std::cout << "Trying to connect to server..." << std::endl;
		m_socketTcp.async_connect(m_remoteEndpointTcp,
			boost::bind(&CClient::connectCompleteHandler, this, placeholders::error)
		);

		return true;
	} else {
		return false;
	}
}

void CClient::connectCompleteHandler(const error_code& error) {
	if (!error) {
		//m_socket.set_option(ip::tcp::no_delay(true));
		std::cout << "Connected to server " << m_socketTcp.remote_endpoint() << std::endl;
		
		m_bConnected = true;
		readHeader();

		m_connectionTimer.expires_from_now(boost::posix_time::seconds(0));
		m_connectionTimer.async_wait(boost::bind(&CNode::checkConnectionHandler, this, placeholders::error));
	} else {
		handleConnectionError(error);
	}
}

void CClient::udpDataRecievedHandler(const boost::system::error_code& error, std::size_t bytesTransferred) {
	// queue the next message
	m_socketUdp.async_receive_from(m_udpMessage.prepare(512),
		m_remoteEndpointUdp,
		boost::bind(&CClient::udpDataRecievedHandler, this, placeholders::error, placeholders::bytes_transferred)
	);

	if (!error) {
		// parse received message
		boost::property_tree::ptree jsonTree;
		try {
			m_udpMessage.commit(bytesTransferred);
			boost::property_tree::read_json(std::istream(&m_udpMessage), jsonTree);

			std::string stName = jsonTree.get<std::string>("Name", "?");

			if (stName != "?") {
				m_gameList.push_back(CGameObject(m_remoteEndpointUdp.address(), m_usPortTcp, stName));
			}
		} catch (boost::property_tree::json_parser_error error) {
			// received message is invalid -> ignore it
		}

		//clear for next message
		m_udpMessage.consume(m_udpMessage.size());
	} else {
		handleConnectionError(error);
	}
}

void CClient::udpDataSentHandler(const boost::system::error_code& error, std::size_t /*bytesTransferred*/) {
	handleConnectionError(error);
}

}