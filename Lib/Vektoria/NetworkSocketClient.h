#pragma once
#include <queue>
#include "NetworkSocketBase.h"
#define PACKET_SIZE 3350
//-------------------------------------------------------------
// CNetworkSocketClient: Klasse für Netzwerk-Aufgaben ( Client-Seite )
//
//-------------------------------------------------------------

namespace Vektoria
{

class CNetworkSocketClient : public CNetworkSocketBase
{

public:
	CNetworkSocketClient();
	~CNetworkSocketClient();

	void Connect(char czIp[], int iPort);
	void CreateReceiveThread();

	// Methoden aus CNetworkSocketBase-Klasse
	//------------------------------------------------------
	int Send(char czData[], SOCKET socket);
	void SendAll(char czData[]);
	void SendAllOthers(char czData[], SOCKET socket);
	//------------------------------------------------------

	int GetAddress();
	static void ProcessGameCommand(CNetworkPackage* package, SOCKET* socket, CNetworkTransfer* transfer, void* params);
	int Receive(char czData[]);
	void WinsockInit();
	
	DWORD WINAPI ReceiveThread(CNetworkTransfer* pTransfer);
	static DWORD WINAPI StartReceiveThread(void* pParameter);
	static string GetCommand();

	SOCKET m_socket;
	int m_iAddress;

	static string m_stCommand;
	
};

}