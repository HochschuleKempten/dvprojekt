#pragma once

#include <string>

namespace Network {

enum Action {
	UNDEFINED,

	SET_OBJECT,
	DELETE_OBJECT,
	UPGRADE_OBJECT,

	START_GAME,
	END_GAME,
	PAUSE_GAME,
	CONTINUE_GAME,

	SET_MAPSIZE
};

class CTransferObject {
public:

	CTransferObject(Action action = UNDEFINED, int iTransObjectID = -1, int iCoordX = -1, int iCoordY = -1, std::string stValue = "");

	~CTransferObject();

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

private:
	Action m_Action;
	int m_iTransObjectID;
	int m_iCoordX;
	int m_iCoordY;
	std::string m_stValue;
	// to be continued...

};

}