#include "Computer.h"
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <boost\asio\placeholders.hpp>

CComputer::CComputer() :
m_io_service(io_service()), m_socket(m_io_service) {
}

CComputer::~CComputer() {
	m_thread.join();
	delete m_pzwConsole;
}

void CComputer::start() {
	if (!isConnected()) {
		connect();

		if (!m_thread.try_join_for(boost::chrono::duration<int>())) {
			m_thread = boost::thread([this]() {
				m_io_service.run();
			});
		}
	}
}

void CComputer::stop() {
	m_io_service.post([this]() {
		m_socket.close();
	});
	m_thread.join();

	if (!isConnected()) {
		std::cout << "Connection closed" << std::endl;
	} else {
		std::cout << "Failed to close connection" << std::endl;
	}
}

void CComputer::restart() {
	stop();
	start();
}

bool CComputer::isConnected() {
	return m_socket.is_open();
}

void CComputer::write(const CMessage& msg) {
	m_io_service.post([this, msg]() {
		bool write_in_progress = !m_dequeMessageWrite.empty();
		m_dequeMessageWrite.push_back(msg);

		if (!write_in_progress) {
			do_write();
		}
	});
}

void CComputer::setConsole(Vektoria::CWriting* pConsole) {
	m_pzwConsole = pConsole;
}

void CComputer::do_write() {
	async_write(m_socket,
		buffer(m_dequeMessageWrite.front().getData(), m_dequeMessageWrite.front().getLength()),
		boost::bind(&CComputer::writeCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CComputer::readHeader() {
	async_read(m_socket,
		buffer(m_messageRead.getData(), CMessage::headerLength),
		boost::bind(&CComputer::readHeaderCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CComputer::readBody() {
	async_read(m_socket,
		buffer(m_messageRead.getBody(), m_messageRead.getBodyLength()),
		boost::bind(&CComputer::readBodyCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}