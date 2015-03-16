#pragma once
#include "NetworkPackage.h"

namespace Vektoria
{

class CNetworkPackageKey :	public CNetworkPackage
{
	char key;

public:
	CNetworkPackageKey();
	CNetworkPackageKey(string serialisedString); 
	CNetworkPackageKey(char key);
	CNetworkPackageKey(char key, int timeToLive);
	~CNetworkPackageKey(void);
	char GetKey();
	int GetType();
	string ToString();
	string Serialise();
	CNetworkPackageKey* GenerateObject(string serialisedString);
};

}