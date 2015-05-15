#pragma once
#include <boost\asio\ip\address.hpp>

using namespace boost::asio;

namespace Network {

class CGameObject {
public:
	CGameObject(const ip::address& serverAddress, const unsigned short usServerPort, const std::string& stName);
	~CGameObject();

	std::string getServerIP();
	unsigned short getServerPort();
	std::string getName();

private:
	ip::address m_serverAddress;
	unsigned short m_usServerPort;
	std::string m_stName;
};

}

