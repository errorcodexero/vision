extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
}

#include "utils/utils.hpp"

class Client {
public:
	Client(char* _szIP[15], char* _szPort[6], int _iSockType);
	virtual ~Client();

	bool bConnect();	//Can be used regardless of UDP or TCP
protected:


private:

	int iSockfd;
	int iNumBytes;
	int iRV;
	int iSockType;

	const char szPORT[6];
	char szIP[16];
	char szBuf[512];
	char szTmpBuf[1];

	struct addrinfo aiHints, *aiServInfo, *aiP;

};

class Server {
public:

	Server(char _szPort[5], int _iSockType);
	virtual ~Server();

	bool bBroadcast(char* _szBuf); //Only use if your using TCP sockets
	bool bSend(char* _szBuf); //Only use if your using UDP sockets


protected:


private:

	int iSockfd;
	int iNewfd;
	int iYes = 1;
	int iRV;
	int iSockType;

	char szS[INET6_ADDRSTRLEN];
	const char szPORT[5];

	struct addrinfo aiHints, *aiServInfo, *aiP;

	struct sockaddr_storage saCliAddr;

};
