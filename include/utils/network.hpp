#include <mutex>
#include <atomic>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdarg.h>
}
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
/**
 *	A List of all socket statuses
 */
#define SOCK_CLOSED -1

#include "utils/utils.hpp"

int sendAll(int _iS, char* _szBuf, int* _iLen);

void sigChildHandler(int s);

void *getInAddr(struct sockaddr *sa);

char* szSockToString(struct sockaddr_in sa);

class Socket {

public:

	Socket(char* _szPort, int _iSockType, bool bIsServer, char* _szDelimiter);
	virtual ~Socket();

	int iGetSockStatus();

	bool bClose();
	bool bRestart(char* _szPort, int _iSockType, bool bIsServer);

protected:

	int iSockfd;
	int iNumBytes;
	int iRV;
	int iYes;

	char* szDelimiter;
	char* szBuf;
	const char* szPORT;

	struct addrinfo aiHints;
	struct addrinfo* aiServInfo;
	struct addrinfo* aiP;

private:
	int iSockStatus;
};

class TCPServer : public Socket {

public:

	TCPServer(char* _szPort, int _iMaxBacklog, int _iMaxClients);
	virtual ~TCPServer();

	void tryRecieve();

	void sendToAll(char* _szBuf);
	void sendTo(char* _szBuf, int _iSock); //Use the Map located below to find IPs

	void acceptClients(uint32 _iMoreClients);

	void kickAddr(char* szIP);
	void kickAll();

	char* getBuffer();

	std::vector<char* > vszIPs;
	std::map<char*, int> mIPs;

protected:

private:

	int iMaxBacklog;
	int iMaxClients;
	int iNewfd;
	int iFDMax;

	fd_set fdMaster;
	fd_set fdReadfds;

	char sClientIP[INET6_ADDRSTRLEN];
	char* szInBuf;
	char* szOutBuf;

	socklen_t slAddrLen, slSinSize;

	struct sigaction sa;

	struct sockaddr_storage saCliAddr;

};

class TCPClient : Socket {

public:

	TCPClient(char* _szIP, char* _szPort);
	virtual ~TCPClient();

	bool bRecieve();
	bool bSend(char* _szBuf);

	bool bChangeServer(char* _szIP);

protected:

private:

	char* _szIP;
};

class UDPServer : Socket {

public:

	UDPServer(char* _szPort) :
		Socket(_szPort, SOCK_DGRAM, true, (char *) '\n') {};
	~UDPServer();

	bool bListen();
protected:

private:

};

class UDPClient : Socket {

public:

	UDPClient(char* _szIP, char* _szPort) :
		Socket(_szPort, SOCK_DGRAM, false, (char *) '\n') {};
	~UDPClient();

	bool bSay(char* _szBuf);
protected:

private:

};
