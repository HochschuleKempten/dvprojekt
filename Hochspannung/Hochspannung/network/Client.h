#pragma once
#include "Node.h"

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
	 * @param sIP the IP of the target server.
	 * @param stIP the port to connect to.
	 */
	CClient(std::string stIP, unsigned short usPort);

	/**
	 * @brief Default constructor.
	 */
	~CClient();

	/**
	 * @brief Sets the servers connection data.
	 * @param sIP the IP of the target server.
	 * @param stIP the port to connect to.
	 * @return true if the given data is valid, false otherwise.
	 */
	bool setServerData(std::string stIP, std::string sPort);

private:
	bool connect();

	void connectCompleteHandler(const error_code& ec, ip::tcp::resolver::iterator iterator);

	ip::tcp::resolver::iterator m_endpointIterator;
	bool m_bEndpointValid;
};

}