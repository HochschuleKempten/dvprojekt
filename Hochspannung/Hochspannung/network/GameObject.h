#pragma once
#include <boost\asio\ip\address.hpp>

using namespace boost::asio;

namespace Network {

/**
 * @class CGameObject
 * @brief Class representing a game session.
 */
class CGameObject {
public:
	/**
	 * @brief Constructor.
	 * @param serverAddress the server ip address.
	 * @param usServerPort the server port.
	 * @param stName the name of the game session.
	 */
	CGameObject(const ip::address& serverAddress, const unsigned short usServerPort, const std::string& stName);

	/**
	 * @brief Default deconstructor.
	 */
	~CGameObject();

	std::string getServerIP() const;
	unsigned short getServerPort() const;
	std::string getName() const;

private:
	friend bool operator==(const CGameObject& lhs, const CGameObject& rhs);

	ip::address m_serverAddress;
	unsigned short m_usServerPort;
	std::string m_stName;
};

}

