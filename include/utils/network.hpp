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
	Client();
	virtual ~Client();
	bool bConnect();	//Connects and receives data
protected:


private:

	int _iSockfd;
	int _iNumBytes;
	int _iRV;

	char _szPort[5];
	char _szBuf[512];
	char _szTmpBuf[1];

	struct addrinfo hints, *servinfo, *p;

};

class Server {
public:
	Server();
	virtual ~Server();

protected:


private:

	int _iSockfd;
	int _iNewfd;
	int _iYes = 1;
	int _iRV;

	char s[INET6_ADDRSTRLEN];
	char _szBuf[512]

};
