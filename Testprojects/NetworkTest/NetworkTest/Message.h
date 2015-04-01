#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

class CMessage {
public:
	const static int headerLength = 4;
	const static int maxBodyLength = 512;

	CMessage();
	CMessage(const char* content);
	~CMessage();

	void setContent(const char* content);

	char* getData();
	int getLength() const;

	char* getBody();
	int getBodyLength() const;
	void setBodyLength(int iBodyLength);

	bool decodeHeader();
	void encodeHeader();

private:
	char m_acData[headerLength + maxBodyLength];
	int m_iBodyLength;
};

