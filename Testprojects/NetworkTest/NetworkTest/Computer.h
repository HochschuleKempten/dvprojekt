#pragma once
#include <boost\thread\thread.hpp>
#include <boost\asio\ip\tcp.hpp>
#include <deque>
#include "Vektoria\Writing.h"
#include "Message.h"

using namespace boost::asio;

class CComputer {
public:
	CComputer();
	~CComputer();

	void start();
	void stop();
	void restart();
	bool isConnected();

	void write(const CMessage& msg);

	bool isTextLeft();
	std::string getLatestText();

protected:
	virtual void connect() = 0;
	void do_write();
	void readHeader();
	void readBody();

	virtual void writeCompleteHandler(const boost::system::error_code& ec, std::size_t length) = 0;
	virtual void readHeaderCompleteHandler(const boost::system::error_code& ec, std::size_t length) = 0;
	virtual void readBodyCompleteHandler(const boost::system::error_code& ec, std::size_t length) = 0;

	io_service m_io_service; 
	boost::thread m_thread;
	ip::tcp::socket m_socket;

	bool m_bConnected;

	CMessage m_messageRead;
	std::deque<CMessage> m_dequeMessagesToWrite;
	std::deque<std::string> m_dequeTextToPrint;
};