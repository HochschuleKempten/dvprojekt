#pragma once
#include <map>
#include <iostream>
//#include <Winsock2.h> 
#include "NetworkPackage.h"
#include "NetworkPackageCommand.h"
#include "NetworkPackageKey.h"
#include "NetworkPackageWrapper.h"
#include "NetworkPackageData.h"

using namespace std;

namespace Vektoria
{

class CNetworkSocketBase;

class CNetworkTransfer
{
	
	CNetworkSocketBase* socket;
public:
	map<int,CNetworkPackageWrapper*> packages;

	CNetworkTransfer(void);
	~CNetworkTransfer(void);
	void Push(CNetworkPackage *package, SOCKET* socket = NULL);
	void PushAll(CNetworkPackage *package);
	void PushAllOthers(CNetworkPackage *package, SOCKET* socket);
	void Request(CNetworkPackage *package);
	void AddListener(CNetworkPackage * package, void (*resFunction)(CNetworkPackage * package, SOCKET* socket, CNetworkTransfer* transfer, void* params), void* callbackParams);
	void PrintActivePackages();
	void AddSocket(CNetworkSocketBase* socket);
	void DataReceived(char * szRecvBuf, SOCKET* socket);
};

}