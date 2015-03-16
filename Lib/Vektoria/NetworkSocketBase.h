#pragma once

//#include <Winsock2.h> 
//#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <stdio.h>
#include "NetworkTransfer.h"

using namespace std;

namespace Vektoria
{

class CNetworkSocketBase
{
	
public:
	CNetworkTransfer* transfer;
	CNetworkSocketBase(void);
	~CNetworkSocketBase();
	virtual int Send(char czData[], SOCKET socket) = 0;
	virtual void SendAll(char czData[]) = 0;
	virtual void SendAllOthers(char czData[], SOCKET socket) = 0;
	void SetTransferObject(CNetworkTransfer* transfer);
	CNetworkTransfer * GetTransferObject();
};

}