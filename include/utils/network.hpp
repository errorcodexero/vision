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
#include <fcntl.h>
#include <ctype.h>
#include <stdarg.h>
}

#include "utils/utils.hpp"

void *getInAddr(struct sockaddr *sa);
/** \brief A Simple client class for any networking needs
 *
 *
 *	Create an instance of the Client class to open a socket on a given port, with either TCP or UDP, and be able to act as a talker or a client
 */
class Client {
public:
	Client(char* _szIP, char* _szPort, int _iSockType);
	virtual ~Client();

	bool bRecv();	//TCP
	bool bSendTo(char* _szBuf); //UDP
protected:


private:

	int iSockfd;
	int iNumBytes;
	int iRV;
	int iSockType;

	const char* szPORT;
	char* szIP;
	char* szBuf;
	char szS[INET6_ADDRSTRLEN];

	struct addrinfo aiHints, *aiServInfo, *aiP;

};

class Server {
public:

	Server(char* _szPort, int _iSockType, int _iBacklog, unsigned int _iMaxClients);
	virtual ~Server();

	bool bBroadcast(char* _szBuf); //Only use if your using TCP sockets
	bool bRecvFrom(); //Only use if your using UDP sockets


protected:


private:

	int iSockfd;
	int iNewfd;
	int iYes = 1;
	int iRV;
	int iSockType;
	int iBacklog;
	int iNumBytes;

	uint32 iMaxClients;

	char szS[INET6_ADDRSTRLEN];
	char* szBuf;

	const char* szPORT;

	struct addrinfo aiHints, *aiServInfo, *aiP;

	socklen_t slAddrLen, slSinSize;

	struct sigaction sa;

	struct sockaddr_storage saCliAddr;

};
