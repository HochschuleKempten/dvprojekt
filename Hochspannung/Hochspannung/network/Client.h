#pragma once
#include "Computer.h"

using namespace boost::asio;

class CClient : public CComputer {
public:
	CClient(std::string ip, std::string port);
	~CClient();

private:
	void connect();

	void connectCompleteHandler(const boost::system::error_code& ec, ip::tcp::resolver::iterator iterator);

	ip::tcp::resolver m_resolver;
	ip::tcp::resolver::iterator m_endpointIterator;
};

