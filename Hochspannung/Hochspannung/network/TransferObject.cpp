#pragma once
#include "TransferObject.h"
#include <boost\lexical_cast.hpp>

namespace Network {

CTransferObject::CTransferObject(Action action, int iTransObjectID, int iCoordX, int iCoordY, std::string sValue) :
m_Action(action), m_iTransObjectID(iTransObjectID), m_iCoordX(iCoordX), m_iCoordY(iCoordY), m_sValue(sValue) {
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
	return m_sValue;
}

void CTransferObject::setValue(std::string sValue) {
	m_sValue = sValue;
}

std::vector<FieldTransfer> CTransferObject::getValueAsVector() {
	std::vector<FieldTransfer> fieldTransferObjects;
	FieldTransfer fieldTransfer;

	std::vector<std::string> fieldTransferStrings;
	std::stringstream ss(m_sValue); // Turn the std::string into a stream.
	std::string tok;

	while (getline(ss, tok, '$')) {
		fieldTransferStrings.push_back(tok);
	}

	for (std::vector<std::string>::iterator it = fieldTransferStrings.begin(); it != fieldTransferStrings.end(); ++it) {
		fieldTransfer.iObjectID = boost::lexical_cast<int>(*it);
		fieldTransfer.iPlayerID = boost::lexical_cast<int>(*(++it));
		fieldTransfer.iFieldLevel = boost::lexical_cast<int>(*(++it));
		fieldTransfer.iFieldType = boost::lexical_cast<int>(*(++it));
		fieldTransferObjects.push_back(fieldTransfer);
	}

	return fieldTransferObjects;
}

}