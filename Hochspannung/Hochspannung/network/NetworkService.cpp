#include "NetworkService.h"
#include "Client.h"
#include "Server.h"
#include <boost\lexical_cast.hpp>

namespace Network {

CNetworkService::CNetworkService() :
m_type(NONE), m_stLocalAddress("0.0.0.0") {
}

CNetworkService::~CNetworkService() {
	delete m_pNode;
}

CNetworkService& CNetworkService::instance() {
	static CNetworkService instance;
	return instance;
}

bool CNetworkService::host(std::string stName) {
	if (m_type == CLIENT) {
		close();
	}

	if (m_pNode == nullptr) {
		m_pNode = new CServer(stName, m_stLocalAddress);
		m_type = SERVER;
	}

	if (m_pNode->start()) {
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::connect(std::string stIP) {
	if (m_type == CLIENT) {
		m_pNode->stop();
		static_cast<CClient*>(m_pNode)->setServerData(stIP);
	} else if (m_type == SERVER) {
		close();
	}

	if (m_pNode == nullptr) {
		m_pNode = new CClient(stIP);
		m_pNode->setLocalAddress(m_stLocalAddress);
		m_type = CLIENT;
	}

	if (m_pNode->start()) {
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::searchGames() {
	if (m_type == CLIENT) {
		m_pNode->stop();
	} else if (m_type == SERVER) {
		close();
	}

	if (m_pNode == nullptr) {
		m_pNode = new CClient();
		m_pNode->setLocalAddress(m_stLocalAddress);
		m_type = CLIENT;
	}

	return static_cast<CClient*>(m_pNode)->searchGames();
}

std::vector<CGameObject> CNetworkService::getGameList() {
	if (m_pNode != nullptr && m_type == CLIENT) {
		return static_cast<CClient*>(m_pNode)->getGameList();
	} else {
		return std::vector<CGameObject>();
	}
}

void CNetworkService::close() {
	if (m_pNode != nullptr) {
		m_pNode->stop();
		delete m_pNode;
		m_pNode = nullptr;
		m_type = NONE;
	}
}

void CNetworkService::restart() {
	if (m_pNode != nullptr) {
		m_pNode->restart();
	}
}

State CNetworkService::getConnectionState() {
	if (m_pNode != nullptr) {
		return m_pNode->getConnectionState();
	} else {
		return CLOSED;
	}
}

Type CNetworkService::getType() {
	return m_type;
}

int CNetworkService::getLatency() {
	if (getConnectionState() == CONNECTED) {
		return m_pNode->getLatency();
	} else {
		return -1;
	}
}

bool CNetworkService::sendStartGame() {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::START_GAME);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendStopGame() {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::END_GAME);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendPauseGame() {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::PAUSE_GAME);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendContinueGame() {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::CONTINUE_GAME);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendSetObject(int iObjectID, int iCoordX, int iCoordY, std::string stPlayer) {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::SET_OBJECT, iObjectID, iCoordX, iCoordY, stPlayer);
		return true;
	} else {
		return false;
	}
}

//bool sendMoveObject(int iObjectID, int iCoordXSource, int iCoordYSouce, int iCoordXDest, int iCoordYDest) {
//}

bool CNetworkService::sendDeleteObject(int iCoordX, int iCoordY) {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::DELETE_OBJECT, -1, iCoordX, iCoordY);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendSetMapsize(int iSizeX, int iSizeY) {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::SET_MAPSIZE, -1, iSizeX, iSizeY);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendSetMapRow(int iRow, std::vector<FieldTransfer> vRowData) {
	if (getConnectionState() == CONNECTED) {
		std::string stRowData = "";
		for (std::vector<FieldTransfer>::iterator it = vRowData.begin(); it != vRowData.end(); ++it) {
			stRowData += boost::lexical_cast<std::string>(it->iObjectID) + "$"
				+ boost::lexical_cast<std::string>(it->iPlayerID) + "$"
				+ boost::lexical_cast<std::string>(it->iFieldLevel) + "$"
				+ boost::lexical_cast<std::string>(it->iFieldType) + "$";
		}

		if (stRowData.back() == '$') {
			stRowData.pop_back();
		}

		sendAsMessage(Action::SET_MAPROW, -1, iRow, 0, stRowData);
	
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendSabotage(int iSabotageID, int iCoordX, int iCoordY) {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::SEND_SABOTAGE, iSabotageID, iCoordX, iCoordY, "");
		return true;
	}
	else {
		return false;
	}
}

bool CNetworkService::sendSwitchState(int iCoordX, int iCoordY, bool bStateOn) {
	if (getConnectionState() == CONNECTED) {
		sendAsMessage(Action::SEND_SWITCH_STATE, -1, iCoordX, iCoordY, boost::lexical_cast<std::string>(bStateOn));
		return true;
	}
	else {
		return false;
	}
}

CTransferObject CNetworkService::getNextActionToExecute() {
	if (m_pNode != nullptr) {
		return m_pNode->getNextActionToExecute();
	} else {
		return CTransferObject();
	}
}

bool CNetworkService::isActionAvailable() {
	if (m_pNode != nullptr) {
		return m_pNode->isActionAvailable();
	} else {
		return false;
	}
}

void CNetworkService::setLocalAddress(std::string stLocalAddress) {
	m_stLocalAddress = stLocalAddress;
}

void CNetworkService::sendAsMessage(Action action, int iObjectID, int iCoordX, int iCoordY, std::string sValue) {
	// transforms the action to string
	// delimiter is a semicolon
	std::string stMessage = boost::lexical_cast<std::string>(action)+";";
	stMessage += boost::lexical_cast<std::string>(iObjectID)+";";
	stMessage += boost::lexical_cast<std::string>(iCoordX)+";";
	stMessage += boost::lexical_cast<std::string>(iCoordY)+";";
	stMessage += sValue + ";";

	CMessage message(stMessage.c_str());
	m_pNode->write(message);
}

}