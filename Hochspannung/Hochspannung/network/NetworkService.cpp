#include "NetworkService.h"
#include <boost\lexical_cast.hpp>

namespace Network {

CNetworkService::CNetworkService() :
m_ConnectionState(CLOSED) {
}

CNetworkService::CNetworkService(const CNetworkService&) {
}

CNetworkService::~CNetworkService() {
	delete m_pNode;
}

CNetworkService& CNetworkService::instance() {
	static CNetworkService instance;
	return instance;
}

bool CNetworkService::host() {
	if (m_pNode == 0) {
		m_pNode = new CServer(usPort);

		if (m_pNode->start()) {
			m_ConnectionState = PENDING;
			return true;
		}
	}

	return false;
}

bool CNetworkService::connect(std::string stIP) {
	if (m_pNode == 0) {
		m_pNode = new CClient(stIP, usPort);

		if (m_pNode->start()) {
			m_ConnectionState = PENDING;
			return true;
		}
	}
	
	return false;
}

void CNetworkService::close() {
	if (m_pNode != 0) {
		m_pNode->stop();
		delete m_pNode;
		m_pNode = 0;
		m_ConnectionState = CLOSED;
	}
}

State CNetworkService::getConnectionState() {
	// just a workaround for the moment
	if (m_pNode->isConnected()) {
		m_ConnectionState = CONNECTED;
	}

	return m_ConnectionState;
}

void CNetworkService::sendStartGame() {
	sendAsMessage(Action::START_GAME);
}

void CNetworkService::sendStopGame() {
	sendAsMessage(Action::END_GAME);
}

void CNetworkService::sendPauseGame() {
	sendAsMessage(Action::PAUSE_GAME);
}

void CNetworkService::sendContinueGame() {
	sendAsMessage(Action::CONTINUE_GAME);
}

void CNetworkService::sendSetObject(int iObjectID, int iCoordX, int iCoordY) {
	sendAsMessage(Action::SET_OBJECT, iObjectID, iCoordX, iCoordY);
}

//void sendMoveObject(int iObjectID, int iCoordXSource, int iCoordYSouce, int iCoordXDest, int iCoordYDest) {
//}

void CNetworkService::sendDeleteObject(int iObjectID, int iCoordX, int iCoordY) {
	sendAsMessage(Action::DELETE_OBJECT, iObjectID, iCoordX, iCoordY);
}

CTransferObject CNetworkService::getNextActionToExecute() {
	return m_pNode->getNextActionToExecute();
}

bool CNetworkService::isActionAvailable() {
	return m_pNode->isActionAvailable();
}

void CNetworkService::sendAsMessage(Action action, int iObjectID, int iCoordX, int iCoordY, std::string sValue) {

	// transforms the action to string
	// delimiter is a semicolon
	std::string stMessage = boost::lexical_cast<std::string>(action) + ";";
	stMessage += boost::lexical_cast<std::string>(iObjectID) + ";";
	stMessage += boost::lexical_cast<std::string>(iCoordX) + ";";
	stMessage += boost::lexical_cast<std::string>(iCoordY) + ";";
	stMessage += sValue + ";";

	CMessage message(stMessage.c_str());
	m_pNode->write(message);
}

}