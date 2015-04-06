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
	void writeCompleteHandler(const boost::system::error_code& ec, std::size_t length);
	void readHeaderCompleteHandler(const boost::system::error_code& ec, std::size_t length);
	void readBodyCompleteHandler(const boost::system::error_code& ec, std::size_t length);

	ip::tcp::resolver::iterator m_endpointIterator;
};

