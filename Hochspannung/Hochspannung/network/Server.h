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
	 * @param stLocalAddress the local IP address to use.
	 */
	explicit CServer(std::string stName, std::string stLocalAddress = "0.0.0.0");

	/**
	 * @brief Default constructor.
	 */
	~CServer();

	/**
	 * @brief Returns the type of the node.
	 * @return the type of the node.
	 */
	Type getType() override;

	/**
	 * @brief Stop the server.
	 * Closes any active connection and stops sending/reciving messages.
	 */
	void stop() override;

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
	/**
	 * @brief Set everything into a state that a connection from a client can be accepted.
	 * @return true, if the preperations were successful, false otherwise.
	 */
	bool connect() override;

	/**
	 * @brief Start the tcp server.
	 * @return true, if nothing went wrong, false otherwise.
	 */
	bool startTcpServer();

	/**
	 * @brief Start the udp server.
	 * @return true, if nothing went wrong, false otherwise.
	 */
	bool startUdpServer();

	/**
	 * @brief Accept handler.
	 * This handler is called when async_accept completes.
	 * Don`t call it directly!
	 * @param error the error code to handle.
	 */
	void acceptCompleteHandler(const error_code& error);

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

	std::string m_stName;
	ip::tcp::acceptor m_acceptor;
};

}