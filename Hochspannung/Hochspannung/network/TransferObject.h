#pragma once

#include <string>
#include <vector>

namespace Network {

struct FieldTransfer {
	int iObjectID = -99;
	int iPlayerID = -99;
	int iFieldLevel = -99;
	int iFieldType = -99;
};

class CTransferObject {
public:
	enum Type {
		NORMAL,
		REQUEST,
		APPROVAL,
		REFUSAL
	};

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
		SEND_SWITCH_STATE,

		SEND_STATISTIC
	};

	explicit CTransferObject(Type type = NORMAL, Action action = UNDEFINED, int iTransObjectID = -1, int iCoordX = -1, int iCoordY = -1, std::string stValue = "");
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

	void encode();
	void decode();

	char* getData();
	int getDataLength();

private:
	Type m_type;
	Action m_action;
	int m_iTransObjectID;
	int m_iCoordX;
	int m_iCoordY;
	std::string m_stValue;
	// to be continued...

	char m_acData[256];
	int m_iLength;
};

}