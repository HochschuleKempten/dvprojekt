#pragma once
#include "Client.h"
#include "Server.h"

namespace Network {

enum State {
	CONNECTED,
	CLOSED,
	PENDING
};

enum Type {
	NONE,
	SERVER,
	CLIENT
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
	 * If a game is already hosted, nothing is done and false returned.
	 * If a connection to another server exists, the connection is closed before the server is started.
	 * @param stName the server/game name.
	 * @return true, if succesful, false otherwise.
	 */
	bool host(std::string stName = "Defaultname");

	/**
	 * @brief Connect to a server hosting a game.
	 * If a game is currently hosted, the server is closed before trying to connect to the new server.
	 * If a connection to a server already exists, the connection is rebuild with the new adddress.
	 * @param stIP the IP of the server to connect to.
	 * @return true, if succesful, false otherwise.
	 */
	bool connect(std::string stIP);

	/**
	 * @brief Searches asynchronously for game server in the local network.
	 * Closes any active connection or server.
	 */
	void searchGames();

	/**
	 * @brief Returns a list of found games in the local network.
	 * @return the list containing information of every hosted game found in the network.
	 */
	std::vector<CGameObject> getGameList();

	/**
	 * @brief Close the active server or connection.
	 */
	void close();

	/**
	 * @brief Reconnect to the server or restart the server.
	 */
	void restart();

	/**
	 * @brief Returns the current connection state (Not solid atm!).
	 * @return the current connection state.
	 */
	State getConnectionState();

	/**
	* @brief Returns the current type.
	* @return the current type.
	*/
	Type getType();

	/**
	 * @brief Returns the current latency to the remote computer if connected.
	 * @return the current latenzy (in ms) or -1 if not connected
	 */
	int getLatency();

	/**
	 * @brief Send the command to start the game.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendStartGame();

	/**
	 * @brief Send the command to stop the game.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendStopGame();

	/**
	 * @brief Send the command to pause the game.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendPauseGame();

	/**
	 * @brief Send the command to continue the game.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendContinueGame();

	/**
	 * @brief Send the command to set a new object.
	 * @param iObjectId the objects ID.
	 * @param iCoordX the x coordinate where the new object should be set.
	 * @param iCoordY the y coordinate where the new object should be set.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendSetObject(int iObjectID, int iCoordX, int iCoordY);

	/**
	 * @brief Send the command to move an object.
	 * @param iObjectId the objects ID.
	 * @param iCoordXSource the source x coordinate.
	 * @param iCoordYSouce the source y coordinate.
	 * @param iCoordXDest the destination x coordinate.
	 * @param iCoordYDest the destination y coordinate.
	 * @return true if message could be sent, false otherwise.
	 */
	//bool sendMoveObject(int iObjectID, int iCoordXSource, int iCoordYSouce, int iCoordXDest, int iCoordYDest);

	/**
	 * @brief Send the command to delete an object.
	 * @param iObjectId the objects ID.
	 * @param iCoordX the x coordinate of the object that should be deleted.
	 * @param iCoordY the y coordinate of the object that should be deleted.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendDeleteObject(int iObjectID, int iCoordX, int iCoordY);

	/**
	 * @brief Send the command to set the mapsize.
	 * @param iSizeX the maps size in x direction.
	 * @param iSizeY the maps size in y direction.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendSetMapsize(int iSizeX, int iSizeY);

	/**
	 * @brief Returns the next action from deque, if available.
	 * @return the first CTransferObject from the deque, or an empty object if none is available.
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
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendAsMessage(Action action, int iObjectID = -1, int iCoordX = -1, int iCoordY = -1, std::string sValue = "");

	CNode* m_pNode = 0;
	State m_connectionState;
	Type m_type;
};

}