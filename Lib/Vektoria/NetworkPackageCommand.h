#pragma once
#include "NetworkPackage.h"

namespace Vektoria
{

class CNetworkPackageCommand :	public CNetworkPackage
{
	string command;
	int x;
	int y;
public:
	CNetworkPackageCommand();
	CNetworkPackageCommand(string serialisedString); 
	CNetworkPackageCommand(string command, int x, int y);
	CNetworkPackageCommand(string command, int x, int y, int timeToLive);
	~CNetworkPackageCommand(void);
	string GetCommand();
	int GetType();
	int GetX();
	int GetY();
	string ToString();
	string Serialise();
	CNetworkPackageCommand* GenerateObject(string serialisedString);
};

}