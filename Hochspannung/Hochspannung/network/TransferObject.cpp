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

CMessage CTransferObject::toMessage() {
	return createMessage(m_type, m_action, m_iTransObjectID, m_iCoordX, m_iCoordY, m_stValue);
}


CTransferObject CTransferObject::fromMessage(CMessage& message) {
	std::vector<std::string> transferObjectMember;
	std::stringstream ss(message.getBody()); // Turn the string into a stream.
	std::string token;

	while (getline(ss, token, ';')) {
		transferObjectMember.push_back(token);
	}

	return CTransferObject(
		static_cast<CTransferObject::Type>(boost::lexical_cast<int>(transferObjectMember.at(0))),
		static_cast<CTransferObject::Action>(boost::lexical_cast<int>(transferObjectMember.at(1))),
		boost::lexical_cast<int>(transferObjectMember.at(2)),
		boost::lexical_cast<int>(transferObjectMember.at(3)),
		boost::lexical_cast<int>(transferObjectMember.at(4)),
		transferObjectMember.at(5)
	);
}

CMessage CTransferObject::createMessage(Type type, Action action, int iTransObjectID, int iCoordX, int iCoordY, std::string stValue) {
	std::string stMessage = boost::lexical_cast<std::string>(type)+";";
	stMessage += boost::lexical_cast<std::string>(action)+";";
	stMessage += boost::lexical_cast<std::string>(iTransObjectID)+";";
	stMessage += boost::lexical_cast<std::string>(iCoordX)+";";
	stMessage += boost::lexical_cast<std::string>(iCoordY)+";";
	stMessage += stValue + ";";

	return CMessage(stMessage);
}

}