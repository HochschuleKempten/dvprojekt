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

void CNetworkService::restart() {
	if (m_pNode != 0) {
		m_pNode->restart();
	}
}

State CNetworkService::getConnectionState() {
	// just a workaround for the moment
	if (m_pNode != 0 && m_pNode->isConnected()) {
		m_ConnectionState = CONNECTED;
	}

	return m_ConnectionState;
}

int CNetworkService::getLatency() {
	if (getConnectionState() == CONNECTED) {
		return m_pNode->getLatency();
	} else {
		return -1;
	}
}

bool CNetworkService::sendStartGame() {
	return sendAsMessage(Action::START_GAME);
}

bool CNetworkService::sendStopGame() {
	return sendAsMessage(Action::END_GAME);
}

bool CNetworkService::sendPauseGame() {
	return sendAsMessage(Action::PAUSE_GAME);
}

bool CNetworkService::sendContinueGame() {
	return sendAsMessage(Action::CONTINUE_GAME);
}

bool CNetworkService::sendSetObject(int iObjectID, int iCoordX, int iCoordY) {
	return sendAsMessage(Action::SET_OBJECT, iObjectID, iCoordX, iCoordY);
}

//bool sendMoveObject(int iObjectID, int iCoordXSource, int iCoordYSouce, int iCoordXDest, int iCoordYDest) {
//}

bool CNetworkService::sendDeleteObject(int iObjectID, int iCoordX, int iCoordY) {
	return sendAsMessage(Action::DELETE_OBJECT, iObjectID, iCoordX, iCoordY);
}

bool CNetworkService::sendSetMapsize(int iSizeX, int iSizeY) {
	return sendAsMessage(Action::SET_MAPSIZE, -1, iSizeX, iSizeY);
}

CTransferObject CNetworkService::getNextActionToExecute() {
	return m_pNode->getNextActionToExecute();
}

bool CNetworkService::isActionAvailable() {
	return m_pNode->isActionAvailable();
}

bool CNetworkService::sendAsMessage(Action action, int iObjectID, int iCoordX, int iCoordY, std::string sValue) {

	if (getConnectionState() == CONNECTED) {
		// transforms the action to string
		// delimiter is a semicolon
		std::string stMessage = boost::lexical_cast<std::string>(action)+";";
		stMessage += boost::lexical_cast<std::string>(iObjectID)+";";
		stMessage += boost::lexical_cast<std::string>(iCoordX)+";";
		stMessage += boost::lexical_cast<std::string>(iCoordY)+";";
		stMessage += sValue + ";";

		CMessage message(stMessage.c_str());
		m_pNode->write(message);

		return true;
	} else {
		return false;
	}
}

}