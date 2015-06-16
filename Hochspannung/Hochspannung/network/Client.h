#pragma once
#include "Node.h"
#include "GameObject.h"
#include <unordered_map>

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
	 * @param stRemoteAddress the IP address of the target server.
	 * @param usRemotePortTcp the tcp port of the target server.
	 */
	explicit CClient(std::string stRemoteAddress = "", unsigned short usRemotePortTcp = m_usPortTcp);

	/**
	 * @brief Default constructor.
	 */
	~CClient();

	/**
	 * @brief Returns the type of the node.
	 * @return the type of the node.
	 */
	Type getType() override;

	/**
	 * @brief Sets the servers connection data.
	 * @param stRemoteAddress the IP address of the target server.
	 * @param usRemotePortTcp the port to connect to.
	 * @return true if the given data is valid, false otherwise.
	 */
	bool setServerData(std::string stRemoteAddress, unsigned short usRemotePortTcp = m_usPortTcp);

	/**
	 * @brief Searches for game server in the local network.
	 * @return true, if the search request was sent successfully.
	 */
	bool searchGames();
	
	/**
	 * @brief Returns a list of found games in the local network.
	 * @return the list containing information of every hosted game found in the network.
	 */
	const std::unordered_map<std::string, CGameObject>& getGameList();

private:
	/**
	 * @brief Try to connect to a server asynchronously.
	 * @return true, if the attempt to connect was started successfully, false otherwise.
	 */
	bool connect() override;

	/**
	 * @brief Start the tcp client.
	 * @return true, if nothing went wrong, false otherwise.
	 */
	bool startTcpClient();

	/**
	 * @brief Start the udp client.
	 * @return true, if nothing went wrong, false otherwise.
	 */
	bool startUdpClient();

	/**
	 * @brief Connect handler.
	 * This handler is called when async_connect completes.
	 * Don`t call it directly!
	 * @param error the error code to handle.
	 */
	void connectCompleteHandler(const error_code& error);

	/**
	 * @brief Connect timeout handler.
	 * This handler is called when async_wait completes.
	 * Don`t call it directly!
	 * @param error the error code to handle.
	 */
	void connectTimoutHandler(const error_code& error);

	/**
	 * @brief Recieve handler.
	 * This handler is called when async_recieve completes.
	 * Don`t call it directly!
	 * @param error the error code to handle.
	 * @param bytesTransferred the amount of written bytes.
	 */
	void udpDataRecievedHandler(const boost::system::error_code& error, std::size_t bytesTransferred);

	/**
	 * @brief Send handler.
	 * This handler is called when async_send completes.
	 * Don`t call it directly!
	 * @param error the error code to handle.
	 * @param bytesTransferred the amount of written bytes.
	 */
	void udpDataSentHandler(const boost::system::error_code& error, std::size_t /*bytesTransferred*/);

	ip::tcp::endpoint m_remoteEndpointTcp;
	bool m_bEndpointValid;

	std::unordered_map<std::string, CGameObject> m_gameList;
};

}