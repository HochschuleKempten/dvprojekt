#pragma once
#include "Computer.h"

using namespace boost::asio;

class CServer : public CComputer {
public:
	CServer(int port);
	~CServer();

private:
	void connect();

	void acceptCompleteHandler(const boost::system::error_code& ec);

	ip::tcp::endpoint m_endpoint;
	ip::tcp::acceptor m_acceptor;
};

