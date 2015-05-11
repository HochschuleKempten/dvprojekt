#pragma once
#include "Node.h"
#include "GameObject.h"

using namespace boost::asio;

namespace Network {

using namespace boost::asio;
using boost::system::error_code;

/**
 * @class CClient
 * @brief Client class for the communication between two game sessions.
 */
class CClient : public CNode {
public:
	/**
	 * @brief Constructor that takes the ip and port.
	 * @param stIP the IP of the target server.
	 * @param usPortTcpServer the tcp port of the target server.
	 */
	CClient(const std::string& stIP = "", unsigned short usPortTcpServer = m_usPortTcp);

	/**
	 * @brief Default constructor.
	 */
	~CClient();

	/**
	 * @brief Sets the servers connection data.
	 * @param stIP the IP of the target server.
	 * @param usPortTcpServer the port to connect to.
	 * @return true if the given data is valid, false otherwise.
	 */
	bool setServerData(const std::string& stIP, unsigned short usPortTcpServer = m_usPortTcp);

	/**
	 * @brief Searches for game server in the local network.
	 * @return
	 */
	bool searchGames();
	
	/**
	 * @brief Returns a list of found games in the local network.
	 * @return the list containing information of every hosted game found in the network.
	 */
	std::vector<CGameObject>& getGameList();

private:
	bool connect() override;
	bool startUdpClient();

	void connectCompleteHandler(const error_code& error);
	void connectTimoutHandler(const error_code& error);
	void udpDataRecievedHandler(const boost::system::error_code& error, std::size_t bytesTransferred);
	void udpDataSentHandler(const boost::system::error_code& error, std::size_t bytesTransferred);

	ip::tcp::endpoint m_remoteEndpointTcp;
	bool m_bEndpointValid;

	std::vector<CGameObject> m_gameList;
};

}