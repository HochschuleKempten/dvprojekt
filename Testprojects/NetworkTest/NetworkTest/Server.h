#pragma once
#include <boost\asio\io_service.hpp>
#include <boost\asio\ip\tcp.hpp>
#include <deque>
#include "Message.h"

using namespace boost::asio;
using namespace boost::system;

class CServer {
public:
	CServer(io_service& io_service, const ip::tcp::endpoint& endpoint);
	~CServer();

	void close();
	void write(const CMessage& msg);

	void do_accept();

private:
	void do_write();
	void do_readHeader();
	void do_readBody();

	io_service& m_io_service;
	ip::tcp::acceptor m_acceptor;
	ip::tcp::socket m_socket;

	CMessage m_messageRead;
	std::deque<CMessage> m_dequeMessageWrite;
};

