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
	 * @brief Default constructor.
	 */
	CServer();

	/**
	 * @brief Default constructor.
	 */
	~CServer();

	/**
	 * @brief Stop the server.
	 * Closes any active connection and stops sending/reciving messages.
	 */
	void stop();

private:
	bool connect();

	void acceptCompleteHandler(const error_code& error);
	void udpDataRecievedHandler(const boost::system::error_code& error, std::size_t bytesTransferred);
	void udpDataSentHandler(const boost::system::error_code& error, std::size_t bytesTransferred);

	ip::tcp::acceptor m_acceptor;

	std::array<char, 64> m_acUdpMessage;
};

}