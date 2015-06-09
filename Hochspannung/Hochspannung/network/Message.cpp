#include "Message.h"

namespace Network {

CMessage::CMessage() {
}

CMessage::CMessage(const std::string& messageContent) {
	int iLength = messageContent.length();

	if (iLength <= iMaxBodyLength) {

		for (int i = 0; i < iHeaderLength; i++) {
			m_acData[i] = static_cast<unsigned char>((iLength >> ((iHeaderLength - i - 1) * 8)) & 0xFF);
		}

		memcpy(getBody(), messageContent.c_str(), iLength);
	} else {
		for (int i = 0; i < iHeaderLength; i++) {
			m_acData[i] = static_cast<unsigned char>(0);
		}
	}
}

unsigned char* CMessage::getData() {
	return m_acData;
}

unsigned char* CMessage::getHeader() {
	return m_acData;
}

unsigned char* CMessage::getBody() {
	return m_acData + iHeaderLength;
}

int CMessage::getBodyLength() {
	int iLength = 0;
	for (int i = 0; i < iHeaderLength; i++) {
		iLength += static_cast<int>(m_acData[i]) << ((iHeaderLength - i - 1) * 8);
	}

	return iLength;
}

int CMessage::getLength() {
	return getBodyLength() + iHeaderLength;
}

}