#include "Message.h"
#include "../logic/LUtility.h"

CMessage::CMessage() :
	m_iBodyLength(0) {
}

CMessage::CMessage(const char* content) {
	setContent(content);
}

CMessage::~CMessage() {
}

void CMessage::setContent(const char* content) {
	m_iBodyLength = std::strlen(content);
	std::memcpy(getBody(), content, m_iBodyLength);
	encodeHeader();
}

char* CMessage::getData() {
	return m_acData;
}

int CMessage::getLength() const {
	return headerLength + m_iBodyLength;
}

char* CMessage::getBody() {
	return m_acData + headerLength;
}

int CMessage::getBodyLength() const {
	return m_iBodyLength;
}

void CMessage::setBodyLength(int bodyLength) {
	m_iBodyLength = bodyLength;
	if (m_iBodyLength > maxBodyLength) {
		m_iBodyLength = maxBodyLength;
	}
}

bool CMessage::decodeHeader() {
	char header[headerLength + 1] = "";
	std::strncat(header, m_acData, headerLength);
	m_iBodyLength = std::atoi(header);
	if (m_iBodyLength > maxBodyLength) {
		m_iBodyLength = 0;
		return false;
	}
	return true;
}

void CMessage::encodeHeader() {
	char header[headerLength + 1] = "";
	std::sprintf(header, "%4d", CASTS<int>(m_iBodyLength));
	std::memcpy(m_acData, header, headerLength);
}
