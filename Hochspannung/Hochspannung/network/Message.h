#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

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
	const static int iHeaderLength = 4;

	/**
	 * the fixed max length of the body.
	 */
	const static int iMaxBodyLength = 512;

	/**
	 * @brief Default constructor.
	 */
	CMessage();

	/**
	 * @brief Constructor that takes the messages content.
	 * @param content the messages content that should be send.
	 */
	CMessage(const char* pcContent);

	/**
	 * @brief Default deconstructor.
	 */
	~CMessage();

	/**
	 * @brief Set the messages content.
	 * @param content the messages content that should be send.
	 */
	void setContent(const char* pcContent);

	/**
	 * @brief Returns the complete message data.
	 * @return a pointer to the complete message data
	 */
	char* getData();

	/**
	 * @brief Returns the messages full length (body + header).
	 * @return the messages full length
	 */
	int getLength() const;

	/**
	 * @brief Returns the messages body (the actual message)
	 * @return a pointer to the messages body
	 */
	char* getBody();

	/**
	 * @brief Returns the bodies length
	 * @return the bodies length
	 */
	int getBodyLength() const;

	/**
	 * @brief set the bodies length.
	 * @param iBodyLength the new length of the body.
	 */
	void setBodyLength(int iBodyLength);

	/**
	 * @brief Decodes the header.
	 * Calculates the bodies (with the header information)
	 * and compares it with the max legth.
	 * @return true if the bodies length is to long
	 */
	bool decodeHeader();

private:
	/**
	 * @brief Encode the header.
	 * The header is written into the message data.
	 */
	void encodeHeader();

	char m_acData[iHeaderLength + iMaxBodyLength];
	int m_iBodyLength;
};

}