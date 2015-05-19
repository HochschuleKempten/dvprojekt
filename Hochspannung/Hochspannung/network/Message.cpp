#include "Message.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace Network {

CMessage::CMessage() :
	m_iBodyLength(0) {
}

CMessage::CMessage(const char* pcContent) {
	setContent(pcContent);
}

CMessage::~CMessage() {
}

void CMessage::setContent(const char* pcContent) {
	m_iBodyLength = strlen(pcContent);
	memcpy(getBody(), pcContent, m_iBodyLength);
	encodeHeader();
}

char* CMessage::getData() {
	return m_acData;
}

int CMessage::getLength() const {
	return iHeaderLength + m_iBodyLength;
}

char* CMessage::getBody() {
	return m_acData + iHeaderLength;
}

int CMessage::getBodyLength() const {
	return m_iBodyLength;
}

void CMessage::setBodyLength(int iBodyLength) {
	m_iBodyLength = iBodyLength;
	if (m_iBodyLength > iMaxBodyLength) {
		m_iBodyLength = iMaxBodyLength;
	}
}

bool CMessage::decodeHeader() {
	char header[iHeaderLength + 1] = "";
	strncat(header, m_acData, iHeaderLength);
	m_iBodyLength = atoi(header);

	if (m_iBodyLength > iMaxBodyLength) {
		m_iBodyLength = 0;
		return false;
	}
	return true;
}

void CMessage::encodeHeader() {
	char header[iHeaderLength + 1] = "";
	sprintf(header, "%4d", static_cast<int>(m_iBodyLength));
	memcpy(m_acData, header, iHeaderLength);
}

}