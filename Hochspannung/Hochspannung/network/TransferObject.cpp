#include "TransferObject.h"

namespace Network {

CTransferObject::CTransferObject(Action action = UNDEFINED, int iTransObjectID = -1, int iCoordX = -1, int iCoordY = -1) :
m_Action(action), m_iTransObjectID(iTransObjectID), m_iCoordX(iCoordX), m_iCoordY(iCoordY) {
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

}