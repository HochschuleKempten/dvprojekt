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
	 * @brief Constructor that takes the server port.
	 * @param usPort the server should listen to.
	 */
	CServer(unsigned short usPort);

	/**
	 * @brief Default constructor.
	 */
	~CServer();

private:
	bool connect();

	void acceptCompleteHandler(const error_code& ec);

	ip::tcp::endpoint m_endpoint;
	ip::tcp::acceptor m_acceptor;
};

}