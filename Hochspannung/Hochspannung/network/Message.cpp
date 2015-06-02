#include "Message.h"

namespace Network {

CMessage::CMessage() {
}

CMessage::CMessage(const std::string& messageContent) {
	m_acData[0] = static_cast<char>(messageContent.length());
	memcpy(getBody(), messageContent.c_str(), messageContent.length());
}

char* CMessage::getData() {
	return m_acData;
}

char* CMessage::getHeader() {
	return m_acData;
}

char* CMessage::getBody() {
	return m_acData + iHeaderLength;
}

int CMessage::getBodyLength() {
	return static_cast<int>(m_acData[0]);
}

int CMessage::getLength() {
	return getBodyLength() + iHeaderLength;
}

}