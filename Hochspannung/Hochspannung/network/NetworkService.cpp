#include "NetworkService.h"
#include <boost\lexical_cast.hpp>

namespace Network {

CNetworkService::CNetworkService() :
m_type(NONE) {
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

bool CNetworkService::host(std::string stName) {
	if (m_type == CLIENT) {
		close();
	}

	if (m_pNode == 0) {
		m_pNode = new CServer(stName);
		m_type = SERVER;
	}

	if (m_pNode->start()) {
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::connect(const std::string& stIP)
{
	//if (m_type == CLIENT) {
	//	m_pNode->stop();
	//	static_cast<CClient*>(m_pNode)->setServerData(stIP);
	//} else if (m_type == SERVER) {
	//	close();
	//}
	if (m_type != NONE) {
		close();
	}

	if (m_pNode == 0) {
		m_pNode = new CClient(stIP);
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

	if (m_pNode == 0) {
		m_pNode = new CClient();
		m_type = CLIENT;
	}

	return static_cast<CClient*>(m_pNode)->searchGames();
}

std::vector<CGameObject> CNetworkService::getGameList() {
	if (m_pNode != 0 && m_type == CLIENT) {
		return static_cast<CClient*>(m_pNode)->getGameList();
	} else {
		return std::vector<CGameObject>();
	}
}

void CNetworkService::close() {
	if (m_pNode != 0) {
		m_pNode->stop();
		delete m_pNode;
		m_pNode = 0;
		m_type = NONE;
	}
}

void CNetworkService::restart() {
	if (m_pNode != 0) {
		m_pNode->restart();
	}
}

State CNetworkService::getConnectionState() {
	if (m_pNode != 0) {
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

bool CNetworkService::sendSetObject(int iObjectID, int iCoordX, int iCoordY, std::string stPlayer) {
	return sendAsMessage(Action::SET_OBJECT, iObjectID, iCoordX, iCoordY, stPlayer);
}

//bool sendMoveObject(int iObjectID, int iCoordXSource, int iCoordYSouce, int iCoordXDest, int iCoordYDest) {
//}

bool CNetworkService::sendDeleteObject(int iCoordX, int iCoordY) {
	return sendAsMessage(Action::DELETE_OBJECT, -1, iCoordX, iCoordY);
}

bool CNetworkService::sendSetMapsize(int iSizeX, int iSizeY) {
	return sendAsMessage(Action::SET_MAPSIZE, -1, iSizeX, iSizeY);
}

bool CNetworkService::sendSetMapRow(int iRow, std::vector<FieldTransfer> vRowData) {
	std::string stRowData = "";
	for (std::vector<FieldTransfer>::iterator it = vRowData.begin(); it != vRowData.end(); ++it) {
		stRowData += boost::lexical_cast<std::string>(it->iObjectID) + "$" 
				  + boost::lexical_cast<std::string>(it->iPlayerID) + "$" 
				  + boost::lexical_cast<std::string>(it->iFieldLevel) + "$" 
				  + boost::lexical_cast<std::string>(it->iFieldType) + "$";
	}

	if (stRowData.back() == (char)"$") {
		stRowData.pop_back();
	}

	return sendAsMessage(Action::SET_MAPROW, -1, iRow, 0, stRowData);
}

CTransferObject CNetworkService::getNextActionToExecute() {
	if (m_pNode != 0) {
		return m_pNode->getNextActionToExecute();
	} else {
		return CTransferObject();
	}
}

bool CNetworkService::isActionAvailable() {
	if (m_pNode != 0) {
		return m_pNode->isActionAvailable();
	} else {
		return false;
	}
}

bool CNetworkService::sendAsMessage(Action action, int iObjectID, int iCoordX, int iCoordY, std::string sValue) {
	if (getConnectionState() == CONNECTED) {
		// transforms the action to std::string
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