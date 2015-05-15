#include "GameObject.h"

namespace Network {

CGameObject::CGameObject(const ip::address& serverAddress, const unsigned short usServerPort, const std::string& stName) :
m_serverAddress(serverAddress), m_usServerPort(usServerPort), m_stName(stName) {
}

CGameObject::~CGameObject() {
}

std::string CGameObject::getServerIP() const {
	return m_serverAddress.to_string();
}

unsigned short CGameObject::getServerPort() const {
	return m_usServerPort;
}

std::string CGameObject::getName() const {
	return m_stName;
}

}
