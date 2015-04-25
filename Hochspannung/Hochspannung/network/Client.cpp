#include "Client.h"
#include <boost\asio\placeholders.hpp>
#include <boost\asio\connect.hpp>
#include <boost\lexical_cast.hpp>
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

		if (!m_thread.try_join_for(boost::chrono::duration<int>())) {
			m_thread = boost::thread([this]() {
				try {
					m_ioService.run();
				} catch (boost::system::system_error error) {
					std::cout << "Unexpected Exception occurred while running io_service: " << error.what() << std::endl;
				}
			});
		}

		std::string stMessage("I am searching for game servers");
		m_socketUdp.async_send_to(buffer(stMessage.c_str(), stMessage.length()),
			ip::udp::endpoint(ip::address_v4::broadcast(), m_usPortUdp),
			boost::bind(&CClient::udpDataSentHandler, this, placeholders::error, placeholders::bytes_transferred)
		);
		
		std::cout << "Started searching for game servers..." << std::endl;

		m_socketUdp.async_receive_from(buffer(m_acUdpMessage),
			m_remoteEndpointUdp,
			boost::bind(&CClient::udpDataRecievedHandler, this, placeholders::error, placeholders::bytes_transferred)
		);
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

		//startPing(m_socketTcp.remote_endpoint().address().to_string());

		m_connectionTimer.expires_from_now(boost::posix_time::seconds(0));
		m_connectionTimer.async_wait(boost::bind(&CNode::checkConnectionHandler, this, placeholders::error));
	} else {
		handleConnectionError(error);
	}
}

void CClient::udpDataRecievedHandler(const boost::system::error_code& error, std::size_t /*bytesTransferred*/) {
	if (!error) {
		// TODO check message content

		m_gameList.push_back(CGameObject(m_remoteEndpointUdp.address(), m_usPortTcp, m_acUdpMessage.data()));

		m_socketUdp.async_receive_from(buffer(m_acUdpMessage),
			m_remoteEndpointUdp,
			boost::bind(&CClient::udpDataRecievedHandler, this, placeholders::error, placeholders::bytes_transferred)
		);
	} else {
		handleConnectionError(error);
	}
}

void CClient::udpDataSentHandler(const boost::system::error_code& error, std::size_t /*bytesTransferred*/) {
	handleConnectionError(error);
}

}