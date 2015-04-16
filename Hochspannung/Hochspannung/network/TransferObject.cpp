#include "TransferObject.h"

namespace Network {

CTransferObject::CTransferObject(Action action, int iTransObjectID, int iCoordX, int iCoordY, std::string stValue) :
m_Action(action), m_iTransObjectID(iTransObjectID), m_iCoordX(iCoordX), m_iCoordY(iCoordY), m_stValue(stValue) {
}

CTransferObject::~CTransferObject() {
}

Action CTransferObject::getAction() {
	return m_Action;
}

void CTransferObject::setAction(Action action) {
	m_Action = action;
}

int CTransferObject::getTransObjectID() {
	return m_iTransObjectID;
}

void CTransferObject::setTransObjectID(int iTransObjectID) {
	m_iTransObjectID = iTransObjectID;
}

int CTransferObject::getCoordX() {
	return m_iCoordX;
}

void CTransferObject::setCoordX(int iCoordX) {
	m_iCoordX = iCoordX;
}

int CTransferObject::getCoordY() {
	return m_iCoordY;
}

void CTransferObject::setCoordY(int iCoordY) {
	m_iCoordY = iCoordY;
}

std::string CTransferObject::getValue() {
	return m_stValue;
}

void CTransferObject::setValue(std::string stValue) {
	m_stValue = stValue;
}

}