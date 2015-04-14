#pragma once
#include <boost\thread\thread.hpp>
#include <boost\asio\ip\tcp.hpp>
#include <boost\asio\deadline_timer.hpp>
#include <deque>
#include "Vektoria\Writing.h"
#include "Message.h"
#include "TransferObject.h"

namespace Network {

using namespace boost::asio;
using boost::system::error_code;

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
	virtual ~CNode();
	
	/**
	 * @brief Start the node.
	 * Attempts to build up a connection by calling connect.
	 * Must be called before any messages can be send or recieved.
	 * @return true, if successful, false otherwise (even if already connected).
	 */
	bool start();

	/**
	 * @brief Stop the node.
	 * Closes any active connection and stops sending/reciving messages.
	 */
	void stop();

	/**
	 * @brief Restart the node.
	 */
	void restart();

	/**
	 * @brief Returns if the connection is currently open.
	 * @return true, if the connection is open, false otherwise.
	 */
	bool isConnected();

	/**
	 * @brief Sends the given message
	 * @param message the CMessage to send
	 */ 
	void write(const CMessage& message);

	/**
	 * @brief Returns the next action from deque, if available.
	 * @return the first CTransferObject from the deque, or an empty object if none none is available.
	 */
	CTransferObject getNextActionToExecute();

	/**
	* @brief Returns if a next action is available.
	* @return true, if a next action is available, false otherwise.
	*/
	bool isActionAvailable();

protected:

	/**
	 * @brief This method is called by start() to connect to another node.
	 * @return true, if the attempt to connect was started successfully, false otherwise.
	 */
	virtual bool connect() = 0;

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
	void writeCompleteHandler(const error_code& ec, std::size_t length);

	/**
	 * @brief Read handler.
  	 * This handler is called when async_read completes. 
	 * Don`t call it directly!
	 */
	void readHeaderCompleteHandler(const error_code& ec, std::size_t length);
	
	/**
	 * @brief Read handler.
	 * This handler is called when async_read completes. 
	 * Don`t call it directly!
	 */
	void readBodyCompleteHandler(const error_code& ec, std::size_t length);

	/**
	 * @brief Handles any connection errors.
	 * A convenience method that should be called in case of connection errors for centralized error handling (e.g. by handlers).
	 * @param ec the error code to handle.
	 */
	void handleConnectionError(const error_code& ec);

	/**
	 * @brief Returns a string from a char array
	 * @param mes the pointer to the message
	 * @param maxLen the maximum length of the message
	 * @return std::string
	 */
	std::string retrieveString(const char* mes, unsigned int maxLen);

	io_service m_ioService;

	boost::thread m_thread;
	ip::tcp::socket m_socket;
	deadline_timer m_timer;

	bool m_bConnected;

	CMessage m_messageRead;
	std::deque<CMessage> m_dequeMessagesToWrite;
	
	std::deque<CTransferObject> m_dequeActionsToExecute;
};

}