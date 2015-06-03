#pragma once
#include "Node.h"
#include "GameObject.h"

namespace Network {

class CNetworkService {
private:
	/**
	 * @brief Default constructor.
	 */
	CNetworkService();

	CNetworkService(const CNetworkService&) = delete;

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
	 * @return
	 */
	bool searchGames();

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
	CNode::State getConnectionState();

	/**
	* @brief Returns the current type.
	* @return the current type.
	*/
	CNode::Type getType();

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
	 * @param sValue any other value to send.
	 * @param bApprovalNeeded set true, if the command shall be send as a request.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendSetObject(int iObjectID, int iCoordX, int iCoordY, std::string stPlayer, bool bApprovalNeeded = false);

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
	 * @param iCoordX the x coordinate of the object that should be deleted.
	 * @param iCoordY the y coordinate of the object that should be deleted.
	 * @param bApprovalNeeded set true, if the command shall be send as a request.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendDeleteObject(int iCoordX, int iCoordY, bool bApprovalNeeded = false);

	/**
	 * @brief Send the command to set the mapsize.
	 * @param iSizeX the maps size in x direction.
	 * @param iSizeY the maps size in y direction.
	 * @param bApprovalNeeded set true, if the command shall be send as a request.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendSetMapsize(int iSizeX, int iSizeY, bool bApprovalNeeded = false);

	/**
	 * @brief Send the command to set an entire row of the map.
	 * @param iRow the number of the row to set.
	 * @param vRowData the data of the fields of the row.
	 * @param bApprovalNeeded set true, if the command shall be send as a request.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendSetMapRow(int iRow, std::vector<FieldTransfer> vRowData, bool bApprovalNeeded = false);

	/**
	 * @brief Send the command for a sabotage.
	 * @param iSabotageID the ID of the sabotage.
	 * @param iCoordX the x-coordinate for the sabotage.
	 * @param iCoordY the y-coordinate for the sabotage.
	 * @param bApprovalNeeded set true, if the command shall be send as a request.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendSabotage(int iSabotageID, int iCoordX, int iCoordY, bool bApprovalNeeded = false);

	/**
	 * @brief Send the command for turning a powerplant on or off.
	 * @param iCoordX the x-coordinate for the powerplant to be turned on/off.
	 * @param iCoordY the y-coordinate for the powerplant to be turned on/off.
	 * @param bStateOn the state to be sent.
	 * @param bApprovalNeeded set true, if the command shall be send as a request.
	 * @return true if message could be sent, false otherwise.
	 */
	bool sendSwitchState(int iCoordX, int iCoordY, bool bStateOn, bool bApprovalNeeded = false);

	/**
	 * @brief Send the command back as an answer.
	 * @param type The type of the answer: only REFUSAL or APPROVAL.
	 * @param transferObject the command, which shall be approved.
	 * @return true if message could be sent and the type was valid, false otherwise.
	 */
	bool sendAnswer(CTransferObject::Type type, CTransferObject& transferObject);

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

	/**
	 * @brief Set the local IP address to use.
	 * @param stLocalAddress the local address to use.
	 */
	void setLocalAddress(std::string stLocalAddress);

private:
	/**
	 * @brief Transorm the command to a CMessage and send it.
	 * @param bApprovalNeeded set true, if the command shall be send as a request.
	 * @param action the Action.
	 * @param iObjectID the objects ID.
	 * @param iCoordX the x coordinate.
	 * @param iCoordY the y coordinate.
	 * @param sValue any other value to send.
	 */
	void sendAsMessage(bool bApprovalNeeded, CTransferObject::Action action, int iObjectID = -1, int iCoordX = -1, int iCoordY = -1, std::string sValue = "");

	CNode* m_pNode = nullptr;
	std::string m_stLocalAddress;
};

}