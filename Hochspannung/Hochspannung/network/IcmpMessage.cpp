#include "IcmpMessage.h"
#include <boost/numeric/conversion/converter.hpp>

namespace Network {

CIcmpMessage::CIcmpMessage() {
}

CIcmpMessage::~CIcmpMessage() {
}

void CIcmpMessage::setType(unsigned char ucType) {
	m_ucType = ucType;
}

unsigned char CIcmpMessage::getType() {
	return m_ucType;
}

void CIcmpMessage::setCode(unsigned char ucCode) {
	m_ucCode = ucCode;
}

unsigned char CIcmpMessage::getCode() {
	return m_ucCode;
}

unsigned short CIcmpMessage::getChecksum() {
	return m_usChecksum;
}

void CIcmpMessage::setIdentifier(unsigned short usIdentifier) {
	m_usIdentifier = usIdentifier;
}

unsigned short CIcmpMessage::getIdentifier() {
	return m_usIdentifier;
}

void CIcmpMessage::setSequenceNumber(unsigned short usSequenceNumber) {
	m_usSequenceNumber = usSequenceNumber;
}

unsigned short CIcmpMessage::getSequenceNumber() {
	return m_usSequenceNumber;
}

std::ostream& operator<<(std::ostream& os, CIcmpMessage& icmpMessage) {
	icmpMessage.generateChecksum();

	// as we want to store shorts in a char array some shifting and ANDing is needed
	icmpMessage.m_acHeaderData[0] = icmpMessage.m_ucType;
	icmpMessage.m_acHeaderData[1] = icmpMessage.m_ucCode;
	icmpMessage.m_acHeaderData[2] = static_cast<unsigned char>(icmpMessage.m_usChecksum >> 8);
	icmpMessage.m_acHeaderData[3] = static_cast<unsigned char>(icmpMessage.m_usChecksum & 0xFF);
	icmpMessage.m_acHeaderData[4] = static_cast<unsigned char>(icmpMessage.m_usIdentifier >> 8);
	icmpMessage.m_acHeaderData[5] = static_cast<unsigned char>(icmpMessage.m_usIdentifier & 0xFF);
	icmpMessage.m_acHeaderData[6] = static_cast<unsigned char>(icmpMessage.m_usSequenceNumber >> 8);
	icmpMessage.m_acHeaderData[7] = static_cast<unsigned char>(icmpMessage.m_usSequenceNumber & 0xFF);

	os.write(reinterpret_cast<char*>(icmpMessage.m_acHeaderData), CIcmpMessage::iHeaderLength);
	os << icmpMessage.m_stBody.c_str();

	return os;
}

std::istream& operator>>(std::istream& is, CIcmpMessage& icmpMessage) {
	is.read(reinterpret_cast<char*>(icmpMessage.m_acHeaderData), CIcmpMessage::iHeaderLength);

	icmpMessage.m_ucType = icmpMessage.m_acHeaderData[0];
	icmpMessage.m_ucCode = icmpMessage.m_acHeaderData[1];
	icmpMessage.m_usChecksum = (icmpMessage.m_acHeaderData[2] << 8) + icmpMessage.m_acHeaderData[3];
	icmpMessage.m_usIdentifier = (icmpMessage.m_acHeaderData[4] << 8) + icmpMessage.m_acHeaderData[5];
	icmpMessage.m_usSequenceNumber = (icmpMessage.m_acHeaderData[6] << 8) + icmpMessage.m_acHeaderData[7];

	return is;
}

void CIcmpMessage::setBody(std::string stBody) {
	m_stBody = stBody;
}

std::string CIcmpMessage::getBody() {
	return m_stBody;
}

void CIcmpMessage::generateChecksum() {
	// add values up using 32-bit arithmetic
	// as some values are chars (1 byte) and the checksum is a short (2 byte) shifting is needed sometimes
	unsigned int usMessageSum = (m_ucType << 8) + m_ucCode 
								+ m_usIdentifier 
								+ m_usSequenceNumber;

	for (std::string::iterator stIterator = m_stBody.begin(); stIterator != m_stBody.end(); stIterator++) {
		usMessageSum += static_cast<unsigned char>(*stIterator) << 8;
		stIterator++;

		if (stIterator != m_stBody.end()) {
			usMessageSum += static_cast<unsigned char>(*stIterator);
		}
	}

	// add 16-bit overflow to the end
	usMessageSum = (usMessageSum >> 16) + (usMessageSum & 0xFFFF);
	// do it again
	usMessageSum += (usMessageSum >> 16);

	// use the complement as checksum
	m_usChecksum = static_cast<unsigned short>(~usMessageSum);
}

}