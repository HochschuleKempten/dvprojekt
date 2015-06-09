#pragma once
#include "Message.h"
#include <string>
#include <vector>

namespace Network {

struct FieldTransfer {
	int iObjectID = -99;
	int iPlayerID = -99;
	int iFieldLevel = -99;
	int iFieldType = -99;
};

/**
 * @class CTransferObject
 * @brief Container class representing one logical command.
 */
class CTransferObject {
public:
	/**
	 * Specifies the different types of messages.
	 */
	enum Type {
		NORMAL,
		REQUEST,
		APPROVAL,
		REFUSAL
	};

	/**
	 * Specifies the different types of actions.
	 */
	enum Action {
		UNDEFINED,

		SET_OBJECT,
		DELETE_OBJECT,
		UPGRADE_OBJECT,

		START_GAME,
		END_GAME,
		PAUSE_GAME,
		CONTINUE_GAME,

		SET_MAPSIZE,
		SET_MAPROW,

		CHECK_CONNECTION,
		CHECK_RESPONSE,

		SEND_SABOTAGE,
		SEND_END_SABOTAGE,
		SEND_SWITCH_STATE,

		SEND_STATISTIC
	};

	/**
	 * @brief Constructor.
	 * @param type
	 * @param action
	 * @param iTransObjectID
	 * @param iCoordX
	 * @param iCoordY
	 * @param stValue
	 */
	explicit CTransferObject(Type type = NORMAL, Action action = UNDEFINED, int iTransObjectID = -1, int iCoordX = -1, int iCoordY = -1, std::string stValue = "");
	
	/**
	 * @brief Default deconstructor.
	 */
	~CTransferObject();

	Type getType();
	void setType(Type type);

	Action getAction();
	void setAction(Action action);

	int getTransObjectID();
	void setTransObjectID(int iTransObjectID);
	
	int getCoordX();
	void setCoordX(int iCoordX);

	int getCoordY();
	void setCoordY(int iCoordY);

	std::string getValue();
	void setValue(std::string stValue);

	/**
	 * @brief A get function for the m_sValue member of TransferObject.
	 * @return std::vector<FieldTransfer>
	 */
	std::vector<FieldTransfer> getValueAsVector();
	
	/**
	 * @brief Encode the transfer object creating a new CMessage.
	 * @return the created message.
	 */
	CMessage toMessage();

	/**
	 * @brief Create a message with the given parameter as content.
	 * @param type
	 * @param action
	 * @param iTransObjectID
	 * @param iCoordX
	 * @param iCoordY
	 * @param stValue
	 * @return the created message.
	 */
	static CMessage createMessage(Type type = NORMAL, Action action = Action::UNDEFINED, int iTransObjectID = -1, int iCoordX = -1, int iCoordY = -1, std::string stValue = "");

	/**
	 * @brief Decode a message, creating a new CTransferObject.
	 * @param message the message to decode.
	 * @return the created transfer object.
	 */
	static CTransferObject fromMessage(CMessage& message);

private:
	Type m_type;
	Action m_action;
	int m_iTransObjectID;
	int m_iCoordX;
	int m_iCoordY;
	std::string m_stValue;
	// to be continued...
};

}