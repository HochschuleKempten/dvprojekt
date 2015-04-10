#pragma once

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

	CTransferObject();
	CTransferObject(Action action, int iTransObjectID, int iCoordX, int iCoordY);
	~CTransferObject();

	Action getAction();
	void setAction(Action action);

	int getTransObjectID();
	void setTransObjectID(int iTransObjectID);
	
	int getCoordX();
	void setCoordX(int iCoordX);

	int getCoordY();
	void setCoordY(int iCoordY);

private:
	Action m_Action;
	int m_iTransObjectID;
	int m_iCoordX;
	int m_iCoordY;
	// to be continued...

};

