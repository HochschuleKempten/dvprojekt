#pragma once
#include "Node.h"


namespace Network {

using namespace boost::asio;
using boost::system::error_code;

/**
 * @class CServer
 * @brief Server class for the communication between two game sessions.
 */
class CServer : public CNode {
public:
	/**
	 * @brief Constructor.
	 * @param stName the server/game name.
	 */
	CServer(std::string stName);

	/**
	 * @brief Default constructor.
	 */
	~CServer();

	/**
	 * @brief Stop the server.
	 * Closes any active connection and stops sending/reciving messages.
	 */
	void stop();

	/**
	 * @brief Sets the server/game name.
	 * @param stName the server/game name.
	 */
	void setName(std::string stName);

	/**
	* @brief Returns the server/game name.
	* @return the server/game name.
	*/
	std::string getName();

private:
	bool connect();
	bool startTcpServer();
	bool startUdpServer();

	void acceptCompleteHandler(const error_code& error);
	void udpDataRecievedHandler(const boost::system::error_code& error, std::size_t bytesTransferred);
	void udpDataSentHandler(const boost::system::error_code& error, std::size_t bytesTransferred);

	std::string m_stName;
	ip::tcp::acceptor m_acceptor;
};

}