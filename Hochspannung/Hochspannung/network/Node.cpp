#include "Node.h"
#include <boost\asio\write.hpp>
#include <boost\asio\read.hpp>
#include <boost\asio\placeholders.hpp>
#include <boost\lexical_cast.hpp>

namespace Network {

CNode::CNode() :
m_io_service(io_service()), m_socket(m_io_service), m_bConnected(false) {
}

CNode::~CNode() {
	m_thread.join();
}

void CNode::start() {
	if (!isConnected()) {
		connect();

		if (!m_thread.try_join_for(boost::chrono::duration<int>())) {
			m_thread = boost::thread([this]() {
				m_io_service.run();
			});
		}
	}
}

void CNode::stop() {
	m_io_service.post([this]() {
		m_socket.shutdown(ip::tcp::socket::shutdown_both);
		m_socket.close();
	});
	m_thread.join();

	m_bConnected = false;

	std::cout << "Connection closed" << std::endl;
}

void CNode::restart() {
	stop();
	start();
}

bool CNode::isConnected() {
	return m_bConnected;
}

void CNode::write(const CMessage& message) {
	m_io_service.post([this, message]() {
		bool write_in_progress = !m_dequeMessagesToWrite.empty();

		if (!write_in_progress) {
			do_write();
		}
	});
}

void CNode::do_write() {
	async_write(m_socket,
		buffer(m_dequeMessagesToWrite.front().getData(), m_dequeMessagesToWrite.front().getLength()),
		boost::bind(&CNode::writeCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::readHeader() {
	async_read(m_socket,
		buffer(m_messageRead.getData(), CMessage::headerLength),
		boost::bind(&CNode::readHeaderCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::readBody() {
	async_read(m_socket,
		buffer(m_messageRead.getBody(), m_messageRead.getBodyLength()),
		boost::bind(&CNode::readBodyCompleteHandler, this, placeholders::error, placeholders::bytes_transferred)
	);
}

void CNode::writeCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {
		m_dequeMessagesToWrite.pop_front();

		if (!m_dequeMessagesToWrite.empty()) {
			do_write();
		}
	} else {
		handleConnectionError(ec);
	}
}

void CNode::readHeaderCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {
		if (m_messageRead.decodeHeader()) { // message is to long
			readBody();
		}
	} else {
		handleConnectionError(ec);
	}
}

void CNode::readBodyCompleteHandler(const error_code& ec, std::size_t /*length*/) {
	if (!ec) {
		std::cout << ">>";
		std::cout.write(m_messageRead.getBody(), m_messageRead.getBodyLength());
		std::cout << "\n";

		readHeader();
	} else {
		handleConnectionError(ec);
	}
}

void CNode::handleConnectionError(const error_code& ec) {
	if (ec.category() == boost::system::system_category()) {
		switch (ec.value()) {
		case ERROR_SUCCESS:
			// no error
			break;

		case ERROR_CONNECTION_REFUSED:
			m_bConnected = false;
			std::cout << "Connection refused by remote computer -> Trying again..." << std::endl;
			connect(); // try to reconnect
			break;

		case WSAECONNRESET:
			m_bConnected = false;
			std::cout << "Connection was closed by remote host -> Trying to reconnect..." << std::endl;
			connect(); // try to reconnect
			break;

		default:
			m_bConnected = false;
			std::cout << "System Error: " << ec.message() << std::endl;
			m_io_service.post([this]() {
				m_socket.shutdown(ip::tcp::socket::shutdown_both);
				m_socket.close();
			}); // close connection, just to be sure
			break;
		}
	} else {
		m_bConnected = false;
		std::cout << "Error: " << ec.message() << std::endl;
		m_io_service.post([this]() {
			m_socket.shutdown(ip::tcp::socket::shutdown_both);
			m_socket.close();
		}); // close connection, just to be sure
	}
}

CTransferObject CNode::getTransferObject() {
	CTransferObject transferObject = m_dequeActionsToExecute.front();
	m_dequeActionsToExecute.pop_front();
	return transferObject;
}

void CNode::writeTransferObjectsToMessageDeque(Action action, int iObjID, int iCoordX, int iCoordY, std::string sValue) {
	CMessage message;
	std::string transferObjectString = "";

	// transforms the action to string
	// delimiter is a semicolon
	transferObjectString = boost::lexical_cast<std::string>(action) + ";";
	transferObjectString += boost::lexical_cast<std::string>(iObjID)+";";
	transferObjectString += boost::lexical_cast<std::string>(iCoordX)+";";
	transferObjectString += boost::lexical_cast<std::string>(iCoordY)+";";
	transferObjectString += sValue + ";";

	// write message on m_dequeMessagesToWrite
	const char* messageStr = transferObjectString.c_str();
	message.setContent(messageStr);
	write(message);
}

void CNode::writeMessagesToTransferObjectDeque() {
	CTransferObject transferObject;
	CMessage message;
	std::string messageStr;
	std::string transferObjMember[5];
	const char* pcMess;
	size_t pos = 0;


	while (!m_dequeMessagesToRead.empty()) {
		message = m_dequeMessagesToRead.front();
		pcMess = message.getBody();
		messageStr = retrieveString((char*)pcMess, 512);

		for (int i = 0; i < 5; i++) {
			pos = messageStr.find(";");
			transferObjMember[i] = messageStr.substr(0, pos);
			messageStr.erase(0, pos + 1);
		}

		transferObject.setAction(boost::lexical_cast<Action>(transferObjMember[0]));
		transferObject.setTransObjectID(boost::lexical_cast<int>(transferObjMember[1]));
		transferObject.setCoordX(boost::lexical_cast<int>(transferObjMember[2]));
		transferObject.setCoordY(boost::lexical_cast<int>(transferObjMember[3]));
		transferObject.setValue(transferObjMember[4]);

		m_dequeActionsToExecute.push_back(transferObject);

		m_dequeMessagesToRead.pop_front();
	}
}

std::string CNode::retrieveString(char* mes, unsigned int maxLen) {
	size_t len = 0;
	while ((len < maxLen) && (mes[len] != '\0')) {
		len++;
	}
	return std::string(mes, len);
}

}