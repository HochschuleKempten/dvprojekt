#pragma once
#include <boost\thread\thread.hpp>
#include <boost\asio\ip\tcp.hpp>
#include <deque>
#include "Vektoria\Writing.h"
#include "Message.h"

using namespace boost::asio;

/**
 * @class CNode
 * @brief Base class for the communication between two game sessions.
 */
class CNode {
public:
	/**
	 * @brief Default constructor.
	 */
	CNode();

	/**
	 * @brief Default deconstructor.
	 */
	~CNode();
	
	/**
	 * @brief Start the node
	 * Tries to build up a connection by calling connect.
	 * Must be called before any messages can be send or recieved.
	 */
	void start();

	/**
	 * @brief Stop the node
	 * Closes any active connection and stops sending/reciving messages.
	 */
	void stop();

	/**
	 * @brief Restart the node
	 */
	void restart();

	/**
	 * @brief Returns if the connection is currently open
	 * @return true if the connection is open, false otherwise
	 */
	bool isConnected();

	/**
	 * @brief Sends the given message
	 * @param message the CMessage to send
	 */ 
	void write(const CMessage& message);

protected:

	/**
	 * @brief This method is called by start() to connect to another node.
	 */
	virtual void connect() = 0;

	/**
	 * @brief Start an asynchronous write operation.
	 * Send the first message on the stack to the connected node.
	 */
	void do_write();

	/**
	 * @brief Start an asynchronous read operation for the header.
	 * Recieve the header of the incoming message.
     */
	void readHeader();

	/**
	 * @brief Start an asynchronous read operation for the body.
	 * Recieve the body of the incoming message.
	 */
	void readBody();

	/**
	 * @brief Write handler.
	 * This handler is called when async_write completes. 
	 * Don`t call it directly!
	 */
	void writeCompleteHandler(const boost::system::error_code& ec, std::size_t length);

	/**
	 * @brief Read handler.
  	 * This handler is called when async_read completes. 
	 * Don`t call it directly!
	 */
	void readHeaderCompleteHandler(const boost::system::error_code& ec, std::size_t length);
	
	/**
	 * @brief Read handler.
	 * This handler is called when async_read completes. 
	 * Don`t call it directly!
	 */
	void readBodyCompleteHandler(const boost::system::error_code& ec, std::size_t length);

	/**
	 * @brief Handles any connection errors.
	 * A convenience method that should be called in case of connection errors for centralized error handling (e.g. by handlers).
	 * @param ec the error code to handle
	 */
	void handleConnectionError(const boost::system::error_code& ec);

	io_service m_io_service; 
	boost::thread m_thread;
	ip::tcp::socket m_socket;

	bool m_bConnected;

	CMessage m_messageRead;
	std::deque<CMessage> m_dequeMessagesToWrite;
};