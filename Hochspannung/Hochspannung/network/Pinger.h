#pragma once
#include <boost\asio\streambuf.hpp>
#include <boost\asio\io_service.hpp>
#include <boost\asio\ip\icmp.hpp>
#include <boost\asio.hpp> // change to detailed posix time header

namespace Network {

using namespace boost::asio;
using boost::system::error_code;

class CPinger {
public:
	CPinger(io_service& ioService);
	~CPinger();

	void start(std::string stIP);
	void stop();

	int getLatestLatency();

private:
	void ping();
	void send();
	void receive();

	void receiveCompleteHandler(const error_code& error, std::size_t bytesTransferred);
	void timoutHandler(const error_code& error);

	unsigned short getIdentifier();

	io_service& m_ioService;
	ip::icmp::socket m_socket;
	ip::icmp::resolver::iterator m_endpointIterator;

	streambuf m_replyBuffer;
	deadline_timer m_timer;
	unsigned short m_iCurrentSequenceNumber;
	boost::posix_time::ptime m_timeSent;

	int m_iLatestLatency;
};



}