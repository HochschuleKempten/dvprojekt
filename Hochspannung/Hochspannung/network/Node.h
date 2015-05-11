#pragma once
#include <boost\thread\thread.hpp>
#include <boost\asio\streambuf.hpp>
#include <boost\asio\ip\tcp.hpp>
#include <boost\asio\ip\udp.hpp>
#include <boost\asio\deadline_timer.hpp>
#include <boost\asio\streambuf.hpp>
#include <deque>
#include "Message.h"
#include "TransferObject.h"

namespace Network {

using namespace boost::asio;
using boost::system::error_code;

enum State {
	CONNECTED,
	CLOSED,
	PENDING
};

/**
 * @class CNode
 * @brief Base class for the communication between two game sessions.
 */
class CNode {
public:

	/**
	 * Fixed tcp port.
	 */
	const static unsigned short m_usPortTcp = 2345;

	/**
	 * Fixed udp port.
	 */
	const static unsigned short m_usPortUdp = 14999;

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
	virtual void stop();

	/**
	 * @brief Restart the node.
	 */
	void restart();

	/**
	 * @brief Returns the current connection state (Not solid atm!).
	 * @return the current connection state.
	 */
	State getConnectionState();

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

	/**
	 * @brief Returns the latency.
	 * @return the result of the last ping in milliseconds or -1 if a timeout occurred.
	 */
	int getLatency();

	/**
	 * @brief The handler for the connection checking operation. 
	 * This handler is the start of the computation of the latency.
	 * Don´t this call directly!
	 * @param the error code.
	 */
	void checkConnectionHandler(const error_code& error);

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
	 * This handler is responsible for the computation of the latency.
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
	std::string retrieveString(char* mes, unsigned int maxLen);

	io_service m_ioService;
	io_service::work m_work;
	boost::thread m_thread;
	ip::tcp::socket m_socketTcp;
	ip::udp::socket m_socketUdp;
	ip::tcp::endpoint m_localEndpointTcp;
	ip::udp::endpoint m_localEndpointUdp;
	ip::udp::endpoint m_remoteEndpointUdp;

	State m_connectionState;
	bool m_bCheckResponseReceived;

	CMessage m_messageRead;
	std::deque<CMessage> m_dequeMessagesToWrite;	
	std::deque<CTransferObject> m_dequeActionsToExecute;
	boost::asio::streambuf m_udpMessage;

	deadline_timer m_connectionTimer;

	int m_iLatestLatency;
};

}