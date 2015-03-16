#pragma once

#include "NetworkSocketBase.h"

#define PACKET_SIZE 256
#define MAX_CLIENTS 2

namespace Vektoria
{

class CNetworkSocketServer :   public CNetworkSocketBase
{

private:
        SOCKET m_serverSocket;
        SOCKET m_clients[MAX_CLIENTS];
		

        char m_szMsgBuf[PACKET_SIZE];

        int m_iConnectedClients;
		int m_iClientIp[MAX_CLIENTS];

public:
	
        CNetworkSocketServer(void);
        ~CNetworkSocketServer(void);

        void WinsockInit(void);
        void InitServer(int iPort);

        void Listen(void);

        int Send(char czData[], SOCKET socket);
        void SendAll(char czData[]);
        void SendAllOthers(char czData[], SOCKET socket);

        int Receive(SOCKET socket, char czData[]); 
		int ActiveConnections();

		int GetClientIP(int iClientNr);
};

}