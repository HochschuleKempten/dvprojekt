#pragma once
#include <iostream>

//
// ICMP Header (8 Byte)
//
// 0    4    8    12   16   20   24   28   31
// +---------+---------+-------------------+
// |  Type   |  Code   |  Checksum		   |
// +---------+---------+-------------------+
// |  Identifier	   |  Sequence Number  |
// +-------------------+-------------------+
// 

namespace Network {
	
class CIcmpMessage {
public:
	const static int iHeaderLength = 8;

	enum Type {
		ECHO_REPLY = 0,
		DESTINATION_UNREACHABLE = 3,
		ECHO_REQUEST = 8
	};

	CIcmpMessage();
	~CIcmpMessage();

	void setType(unsigned char ucType);
	unsigned char getType();

	void setCode(unsigned char ucCode);
	unsigned char getCode();

	unsigned short getChecksum();

	void setIdentifier(unsigned short usIdentifier);
	unsigned short getIdentifier();

	void setSequenceNumber(unsigned short usSequenceNumber);
	unsigned short getSequenceNumber();

	friend std::ostream& operator<<(std::ostream& os, CIcmpMessage& icmpMessage);
	friend std::istream& operator>>(std::istream& is, CIcmpMessage& icmpMessage);

	void setBody(std::string stBody);
	std::string getBody();

private:
	void generateChecksum();

	unsigned char m_ucType;
	unsigned char m_ucCode;
	unsigned short m_usChecksum;
	unsigned short m_usIdentifier;
	unsigned short m_usSequenceNumber;
	unsigned char m_acHeaderData[iHeaderLength];

	std::string m_stBody;
};

}