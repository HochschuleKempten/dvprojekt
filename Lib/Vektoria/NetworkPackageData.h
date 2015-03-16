#pragma once
#include "NetworkPackage.h"

#define MAX_ROW_DATA 6
#define MAX_COLUMN_DATA 2

//-------------------------------------------------------------
// CNetworkPackageData: Klasse für Interaktions-Übertragung
//-------------------------------------------------------------

namespace Vektoria
{

class CNetworkPackageData : public CNetworkPackage
{
public:
	CNetworkPackageData();
	CNetworkPackageData(int* piData);
	CNetworkPackageData(string serialisedString);
	~CNetworkPackageData();

	int GetType();
	int* GetData();
	string ToString();
	string Serialise();
	CNetworkPackage* GenerateObject(string serialisedString);

private:
	int m_aaiData[MAX_ROW_DATA][MAX_COLUMN_DATA];
};

}