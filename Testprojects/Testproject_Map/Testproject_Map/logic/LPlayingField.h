#pragma once
#include "LField.h"
#include "IVPlayingField.h"
#include "LMaster.h"
#include "Array2D.h"

//todo:  Methoden fuer abreissen und Upgrade
class LPlayingField
{

private:
	const int fieldLength = 3; //todo temporäre Lösung, überlegen, wer Größe vorgibt
	LMaster* lMaster;
	IVPlayingField* vPlayingField;
	Array2D<LField> fieldArray;

public:
	LPlayingField(LMaster* lMaster);  
	~LPlayingField();

	void initVPlayingField();
	LField* getField(const int i, const int j);
	int getFieldLength();
};
