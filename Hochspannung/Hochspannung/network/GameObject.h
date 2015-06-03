#pragma once
#include <boost\asio\ip\address.hpp>

using namespace boost::asio;

namespace Network {

class CGameObject {
public:
	CGameObject(const ip::address& serverAddress, const unsigned short usServerPort, const std::string& stName);
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

