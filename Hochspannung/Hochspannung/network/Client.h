#pragma once
#include "Node.h"

using namespace boost::asio;

/**
 * @class CClient
 * @brief Client class for the communication between two game sessions.
 */
class CClient : public CNode {
public:
	/**
	 * @brief Constructor that takes the ip and port.
	 * @param ip the IP of the target server.
	 * @param port the port to connect to.
	 */
	CClient(std::string ip, std::string port);

	/**
	 * @brief Default constructor.
	 */
	~CClient();

private:
	void connect();

	void connectCompleteHandler(const boost::system::error_code& ec, ip::tcp::resolver::iterator iterator);

	ip::tcp::resolver m_resolver;
	ip::tcp::resolver::iterator m_endpointIterator;
};

