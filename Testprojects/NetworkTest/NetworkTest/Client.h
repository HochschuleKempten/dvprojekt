#pragma once
#include <boost\asio\io_service.hpp>
#include <boost\asio\ip\tcp.hpp>
#include <deque>
#include "Message.h"

using namespace boost::asio;
using namespace boost::system;

class CClient {
public:
	CClient(io_service& io_service);
	~CClient();

	void close();
	void write(const CMessage& msg);

	void do_connect(ip::tcp::resolver::iterator& endpoint_iterator);

private:
	void do_write();
	void do_readHeader();
	void do_readBody();


	io_service& m_io_service;
	ip::tcp::socket m_socket;
	CMessage m_messageRead;
	std::deque<CMessage> m_dequeMessageWrite;
};

