#pragma once
#include "LField.h"
#include "IVPlayingField.h"
#include "LMaster.h"

//todo:  Methoden fuer abreissen und Upgrade
class LPlayingField
{

private:
	LMaster* lMaster;
	IVPlayingField* vPlayingField;
	LField * fieldArray;
	const int fieldLength = 3; //todo temporäre Lösung, überlegen, wer Größe vorgibt

public:
	LPlayingField(LMaster* lMaster);  
	~LPlayingField();

	void initVPlayingField();
	LField * getField(const int i, const int j);
	int getFieldLength();
};
