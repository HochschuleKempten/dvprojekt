#include "Pinger.h"
#include <boost\asio\placeholders.hpp>
#include <boost\bind\bind.hpp>
#include "IcmpMessage.h"

namespace Network {

CPinger::CPinger(io_service& ioService) :
m_ioService(ioService), m_socket(m_ioService, ip::icmp::v4()), m_timer(ioService), m_iCurrentSequenceNumber(0), m_iLatestLatency(-1) {

}

CPinger::~CPinger() {
}

void CPinger::start(std::string stIP) {
	m_endpointIterator = ip::icmp::resolver(m_ioService).resolve({ ip::icmp::v4(), stIP.c_str(), "" });
	ping();
}

void CPinger::stop() {
	m_timer.cancel();
	m_socket.shutdown(ip::tcp::socket::shutdown_both);
	m_iLatestLatency = -1;
}

int CPinger::getLatestLatency() {
	return m_iLatestLatency;
}

void CPinger::ping() {
	send();
	receive();
}

void CPinger::send() {
	CIcmpMessage icmpMessage;
	icmpMessage.setType(CIcmpMessage::Type::ECHO_REQUEST);
	icmpMessage.setCode(0);
	icmpMessage.setIdentifier(getIdentifier());
	icmpMessage.setSequenceNumber(++m_iCurrentSequenceNumber);
	icmpMessage.setBody("Echo");

	streambuf streambuffer;
	std::ostream os(&streambuffer);
	os << icmpMessage;

	// remember sent time
	m_timeSent = boost::posix_time::microsec_clock::universal_time();
	m_socket.send_to(streambuffer.data(), *m_endpointIterator);

	// wait for timeout
	m_timer.expires_at(m_timeSent + boost::posix_time::seconds(5));
	m_timer.async_wait(boost::bind(&CPinger::timoutHandler, this, placeholders::error));
}

void CPinger::receive() {
	m_replyBuffer.consume(m_replyBuffer.size());
	m_socket.async_receive(m_replyBuffer.prepare(65536), 
		boost::bind(&CPinger::receiveCompleteHandler, this, placeholders::error, placeholders::bytes_transferred));
}

void CPinger::receiveCompleteHandler(const error_code& error, std::size_t bytesTransferred) {
	if (!error) {
		boost::posix_time::ptime timeRecieved = boost::posix_time::microsec_clock::universal_time();

		CIcmpMessage icmpMessage;
		m_replyBuffer.commit(bytesTransferred);
		std::istream is(&m_replyBuffer);

		// discard ip header and parse icmp header
		is.ignore(20);
		is >> icmpMessage;

		if (icmpMessage.getType() == CIcmpMessage::Type::ECHO_REPLY
			&& icmpMessage.getIdentifier() == getIdentifier()
			&& icmpMessage.getSequenceNumber() == m_iCurrentSequenceNumber) {

			m_iLatestLatency = (timeRecieved - m_timeSent).total_milliseconds();
			// stop timout timer
			m_timer.cancel();
			// send next ping (at least 1 sec after last send)
			m_timer.expires_at(m_timeSent + boost::posix_time::seconds(1));
			m_timer.async_wait(boost::bind(&CPinger::ping, this));
		}
	} else {
		m_timer.cancel();
		std::cout << error.message() << std::endl;
	}
}

void CPinger::timoutHandler(const error_code& error) {
	if (!error) {
		std::cout << "Timeout" << std::endl;
		m_iLatestLatency = -1;
		// send next ping (at least 1 sec after last send)
		m_timer.expires_at(m_timeSent + boost::posix_time::seconds(1));
		m_timer.async_wait(boost::bind(&CPinger::ping, this));
	} else if (error != boost::asio::error::operation_aborted) {
		std::cout << error.message() << std::endl;
	}
}

unsigned short CPinger::getIdentifier() {
	return static_cast<unsigned short>(::GetCurrentProcessId());
}

}