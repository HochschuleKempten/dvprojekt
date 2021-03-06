#pragma once
#include <string>

namespace Network {

/**
 * @class CMessage
 * @brief Base class for the communication between two game sessions.
 */
class CMessage {

public:
	/**
	 * the fixed length of the header.
	 */
	const static int iHeaderLength = 2;

	/**
	 * the fixed max length of the body.
	 */
	const static int iMaxBodyLength = 1024;

	/**
	 * @brief Constructor.
	 */
	CMessage();

	/**
	 * @brief Constructor.
	 * @param messageContent the messages content.
	 */
	explicit CMessage(const std::string& messageContent);

	unsigned char* getData();
	unsigned char* getHeader();
	unsigned char* getBody();

	int getBodyLength();
	int getLength();

private:
	unsigned char m_acData[iHeaderLength + iMaxBodyLength];
};

}