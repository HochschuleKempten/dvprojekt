#pragma once
#include "Client.h"
#include "Server.h"

namespace Network {

enum State {
	CONNECTED,
	CLOSED,
	PENDING
};

class CNetworkService {

private:
	/**
	 * @brief Default constructor.
	 */
	CNetworkService();

	/**
	 * @brief Copy constructor.
	 */
	CNetworkService(const CNetworkService&);

public:
	/**
	 * Fixed server port.
	 */
	const static unsigned short usPort = 2345;

	/**
	 * @brief Default deconstructor.
	 */
	~CNetworkService();

	/**
	 * @brief Returns the instance of CNetworkService.
	 * @return the instance of CNetworkService.
	 */
	static CNetworkService& instance();

	/**
	 * @brief Start a server to host a game.
	 * If a game is already hosted or a connection to another server exists, nothing is done and false returned.
	 * @return true, if succesful, false otherwise.
	 */
	bool host();

	/**
	 * @brief Connect to a server hosting a game.
	 * If a game is already hosted or a connection to another server exists, nothing is done and false returned.
	 * @param stIP the IP of the server to connect to.
	 * @return true, if succesful, false otherwise.
	 */
	bool connect(std::string stIP);

	/**
	 * @brief Close the active server or connection.
	 */
	void close();

	/**
	 * @brief Returns the current connection state (Not solid atm!).
	 * @return the current connection state.
	 */
	State getConnectionState();

	/**
	 * @brief Send the command to start the game.
	 */
	void sendStartGame();

	/**
	 * @brief Send the command to stop the game.
	 */
	void sendStopGame();

	/**
	 * @brief Send the command to pause the game.
	 */
	void sendPauseGame();

	/**
	 * @brief Send the command to continue the game.
	 */
	void sendContinueGame();

	/**
	 * @brief Send the command to set a new object.
	 * @param iObjectId the objects ID.
	 * @param iCoordX the x coordinate where the new object should be set.
	 * @param iCoordY the y coordinate where the new object should be set.
	 */
	void sendSetObject(int iObjectID, int iCoordX, int iCoordY);

	/**
	 * @brief Send the command to move an object.
	 * @param iObjectId the objects ID.
	 * @param iCoordXSource the source x coordinate.
	 * @param iCoordYSouce the source y coordinate.
	 * @param iCoordXDest the destination x coordinate.
	 * @param iCoordYDest the destination y coordinate.
	 */
	//void sendMoveObject(int iObjectID, int iCoordXSource, int iCoordYSouce, int iCoordXDest, int iCoordYDest);

	/**
	 * @brief Send the command to delete an object.
	 * @param iObjectId the objects ID.
	 * @param iCoordX the x coordinate of the object that should be deleted.
	 * @param iCoordY the y coordinate of the object that should be deleted.
	 */
	void sendDeleteObject(int iObjectID, int iCoordX, int iCoordY);

	/**
	 * @brief Returns the next action from deque, if available.
	 * @return the first CTransferObject from the deque, or an empty object if none none is available.
	 */
	CTransferObject getNextActionToExecute();

	/**
	 * @brief Returns if a next action is available.
	 * @return true, if a next action is available, false otherwise.
	 */
	bool isActionAvailable();

private:
	/**
	 * @brief Transorm the command to a CMessage and send it.
	 * @param action the Action.
	 * @param iObjectID the objects ID.
	 * @param iCoordX the x coordinate.
	 * @param iCoordY the y coordinate.
	 * @param sValue any other value to send.
	 */
	void sendAsMessage(Action action, int iObjectID = -1, int iCoordX = -1, int iCoordY = -1, std::string sValue = NULL);

	CNode* m_pNode = 0;
	State m_ConnectionState;
};

}