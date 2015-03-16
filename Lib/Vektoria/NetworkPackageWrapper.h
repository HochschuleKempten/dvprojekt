#pragma once
#include <iostream>
#include <string>
#include "NetworkPackage.h"


using namespace std;

// this wrapper should contain the network package + the method which would be called 
// if we did a request with an expected response. at the current state this class is useless 
// since we screwed the asynchronous request with response...

namespace Vektoria
{

class CNetworkTransfer;

class CNetworkPackageWrapper
{
	CNetworkPackage* package;
	
	
public:
	void (*resFunction)(CNetworkPackage * package, SOCKET* socket, CNetworkTransfer* transfer, void* params);
	void* callbackParams;
	CNetworkPackageWrapper(CNetworkPackage*, void (*resFunction)(CNetworkPackage * package, SOCKET* socket, CNetworkTransfer* transfer, void* params), void* callbackParams);
	~CNetworkPackageWrapper();
	CNetworkPackage* GetPackage();
};

}