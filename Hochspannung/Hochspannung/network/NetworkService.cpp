#include "NetworkService.h"
#include "Client.h"
#include "Server.h"
#include <boost\lexical_cast.hpp>

namespace Network {

CNetworkService::CNetworkService() :
m_stLocalAddress("0.0.0.0") {
}

CNetworkService::~CNetworkService() {
	delete m_pNode;
}

CNetworkService& CNetworkService::instance() {
	static CNetworkService instance;
	return instance;
}

bool CNetworkService::host(std::string stName) {
	if (getType() == CNode::Type::CLIENT) {
		close();
	}

	if (m_pNode == nullptr) {
		m_pNode = new CServer(stName, m_stLocalAddress);
	}

	if (m_pNode->start()) {
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::connect(std::string stIP) {
	if (getType() == CNode::Type::CLIENT) {
		m_pNode->stop();
		static_cast<CClient*>(m_pNode)->setServerData(stIP);
	} else if (getType() == CNode::Type::SERVER) {
		close();
	}

	if (m_pNode == nullptr) {
		m_pNode = new CClient(stIP);
		m_pNode->setLocalAddress(m_stLocalAddress);
	}

	if (m_pNode->start()) {
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::searchGames() {
	if (getType() == CNode::Type::CLIENT) {
		m_pNode->stop();
	} else if (getType() == CNode::Type::SERVER) {
		close();
	}

	if (m_pNode == nullptr) {
		m_pNode = new CClient();
		m_pNode->setLocalAddress(m_stLocalAddress);
	}

	return static_cast<CClient*>(m_pNode)->searchGames();
}

std::vector<CGameObject> CNetworkService::getGameList() {
	if (m_pNode != nullptr && getType() == CNode::Type::CLIENT) {
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
	}
}

void CNetworkService::restart() {
	if (m_pNode != nullptr) {
		m_pNode->restart();
	}
}

CNode::State CNetworkService::getConnectionState() {
	if (m_pNode != nullptr) {
		return m_pNode->getConnectionState();
	} else {
		return CNode::State::CLOSED;
	}
}

CNode::Type CNetworkService::getType() {
	if (m_pNode != nullptr) {
		return m_pNode->getType();
	} else {
		return CNode::Type::NONE;
	}
}

int CNetworkService::getLatency() {
	if (getConnectionState() == CNode::State::CONNECTED) {
		return m_pNode->getLatency();
	} else {
		return -1;
	}
}

bool CNetworkService::sendStartGame() {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(false, CTransferObject::Action::START_GAME);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendStopGame() {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(false, CTransferObject::Action::END_GAME);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendPauseGame() {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(false, CTransferObject::Action::PAUSE_GAME);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendContinueGame() {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(false, CTransferObject::Action::CONTINUE_GAME);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendSetObject(int iObjectID, int iCoordX, int iCoordY, std::string stPlayer, bool bApprovalNeeded) {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(bApprovalNeeded, CTransferObject::Action::SET_OBJECT, iObjectID, iCoordX, iCoordY, stPlayer);
		return true;
	} else {
		return false;
	}
}

//bool sendMoveObject(int iObjectID, int iCoordXSource, int iCoordYSouce, int iCoordXDest, int iCoordYDest) {
//}

bool CNetworkService::sendDeleteObject(int iCoordX, int iCoordY, bool bApprovalNeeded) {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(bApprovalNeeded, CTransferObject::Action::DELETE_OBJECT, -1, iCoordX, iCoordY);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendSetMapsize(int iSizeX, int iSizeY, bool bApprovalNeeded) {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(bApprovalNeeded, CTransferObject::Action::SET_MAPSIZE, -1, iSizeX, iSizeY);
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendSetMapRow(int iRow, std::vector<FieldTransfer> vRowData, bool bApprovalNeeded) {
	if (getConnectionState() == CNode::State::CONNECTED) {
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

		sendAsMessage(bApprovalNeeded, CTransferObject::Action::SET_MAPROW, -1, iRow, 0, stRowData);
	
		return true;
	} else {
		return false;
	}
}

bool CNetworkService::sendSabotage(int iSabotageID, int iCoordX, int iCoordY, bool bApprovalNeeded) {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(bApprovalNeeded, CTransferObject::Action::SEND_SABOTAGE, iSabotageID, iCoordX, iCoordY, "");
		return true;
	}
	else {
		return false;
	}
}

bool CNetworkService::sendSwitchState(int iCoordX, int iCoordY, bool bStateOn, bool bApprovalNeeded) {
	if (getConnectionState() == CNode::State::CONNECTED) {
		sendAsMessage(bApprovalNeeded, CTransferObject::Action::SEND_SWITCH_STATE, -1, iCoordX, iCoordY, boost::lexical_cast<std::string>(bStateOn));
		return true;
	}
	else {
		return false;
	}
}

bool CNetworkService::sendAnswer(CTransferObject::Type type, CTransferObject& transferObject) {
	if (getConnectionState() == CNode::State::CONNECTED && 
		(type == CTransferObject::Type::REFUSAL || type == CTransferObject::Type::APPROVAL)) {

		transferObject.setType(type);
		m_pNode->write(transferObject);

		return true;
	} else {
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

void CNetworkService::sendAsMessage(bool bApprovalNeeded, CTransferObject::Action action, int iObjectID, int iCoordX, int iCoordY, std::string sValue) {
	CTransferObject::Type type;
	if (bApprovalNeeded) {
		type = CTransferObject::Type::REQUEST;
	} else {
		type = CTransferObject::Type::NORMAL;
	}

	CTransferObject transferObject(type, action, iObjectID, iCoordX, iCoordY, sValue);
	m_pNode->write(transferObject);
}

}