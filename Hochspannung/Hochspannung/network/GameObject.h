#pragma once
#include <boost\asio\ip\address.hpp>

using namespace boost::asio;

namespace Network {

class CGameObject {
public:
	CGameObject(ip::address serverAddress, unsigned short usServerPort, std::string stName);
	~CGameObject();

	std::string getServerIP() const;
	unsigned short getServerPort() const;
	std::string getName() const;

private:
	ip::address m_serverAddress;
	unsigned short m_usServerPort;
	std::string m_stName;
};

}

