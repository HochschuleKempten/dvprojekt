#pragma once
#include "Node.h"

using namespace boost::asio;

/**
 * @class CServer
 * @brief Server class for the communication between two game sessions.
 */
class CServer : public CNode {
public:
	/**
	 * @brief Constructor that takes the server port.
	 * @param port the server should listen to.
	 */
	CServer(int port);

	/**
	 * @brief Default constructor.
	 */
	~CServer();

private:
	void connect();

	void acceptCompleteHandler(const boost::system::error_code& ec);

	ip::tcp::endpoint m_endpoint;
	ip::tcp::acceptor m_acceptor;
};

