#pragma once
#include "TransferObject.h"
#include <boost\lexical_cast.hpp>

namespace Network {

CTransferObject::CTransferObject(Type type, Action action, int iTransObjectID, int iCoordX, int iCoordY, std::string sValue) :
m_type(type), m_action(action), m_iTransObjectID(iTransObjectID), m_iCoordX(iCoordX), m_iCoordY(iCoordY), m_stValue(sValue) {
}

CTransferObject::~CTransferObject() {
}

CTransferObject::Type CTransferObject::getType() {
	return m_type;
}

void CTransferObject::setType(Type type) {
	m_type = type;
}

CTransferObject::Action CTransferObject::getAction() {
	return m_action;
}

void CTransferObject::setAction(Action action) {
	m_action = action;
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

void CTransferObject::setValue(std::string sValue) {
	m_stValue = sValue;
}

std::vector<FieldTransfer> CTransferObject::getValueAsVector() {
	std::vector<FieldTransfer> fieldTransferObjects;
	FieldTransfer fieldTransfer;

	std::vector<std::string> fieldTransferStrings;
	std::stringstream ss(m_stValue); // Turn the string into a stream.
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

void CTransferObject::encode() {
	std::string stMessage = boost::lexical_cast<std::string>(m_type) + ";";
	stMessage += boost::lexical_cast<std::string>(m_action) + ";";
	stMessage += boost::lexical_cast<std::string>(m_iTransObjectID) + ";";
	stMessage += boost::lexical_cast<std::string>(m_iCoordX) + ";";
	stMessage += boost::lexical_cast<std::string>(m_iCoordY) + ";";
	stMessage += m_stValue + ";";

	m_iLength = stMessage.length();

	if (m_iLength <= 255) {
		m_acData[0] = static_cast<char>(m_iLength);
		memcpy(&(m_acData[1]), stMessage.c_str(), m_iLength);
	}
}


void CTransferObject::decode() {
	std::vector<std::string> transferObjectMember;
	std::stringstream ss(&m_acData[1]); // Turn the string into a stream.
	std::string token;

	while (getline(ss, token, ';')) {
		transferObjectMember.push_back(token);
	}

	m_type = static_cast<CTransferObject::Type>(boost::lexical_cast<int>(transferObjectMember.at(0)));
	m_action = static_cast<CTransferObject::Action>(boost::lexical_cast<int>(transferObjectMember.at(1)));
	m_iTransObjectID = boost::lexical_cast<int>(transferObjectMember.at(2));
	m_iCoordX = boost::lexical_cast<int>(transferObjectMember.at(3));
	m_iCoordY = boost::lexical_cast<int>(transferObjectMember.at(4));
	m_stValue = transferObjectMember.at(5);
}

char* CTransferObject::getData() {
	return m_acData;
}

int CTransferObject::getDataLength() {
	return m_iLength + 1;
}

}