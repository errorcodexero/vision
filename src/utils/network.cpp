#include "utils/network.hpp"

using namespace std;

void *getInAddr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);

}

int sendAll(int _iS, char* _szBuf, int _iLen) {
	int iTotal = 0;
	int iBytesLeft = _iLen; //Bug Causes Segfault
	int iN;
	while (iTotal < _iLen) {
		iN = send(_iS, _szBuf+iTotal, iBytesLeft, 0);
		if (iN == -1 ) { break; }
		iTotal += iN;
		iBytesLeft -=iN;
	}

	_iLen = iTotal;

	return iN==-1?-1:0;
}

void sigChildHandler(int s) {
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

char* szSockToString(struct sockaddr_in sa) {
	char* szString = (char* ) malloc (sizeof (char) * 24);
	sprintf(szString, "%d.%d.%d.%d\n",
	  int(sa.sin_addr.s_addr&0xFF),
	  int((sa.sin_addr.s_addr&0xFF00)>>8),
	  int((sa.sin_addr.s_addr&0xFF0000)>>16),
	  int((sa.sin_addr.s_addr&0xFF000000)>>24));
	return szString;
}

Socket::Socket(char* _szPort, int _iSockType, bool _bIsServer, char* _szDelimiter) {
	int iTmp;
	sscanf(_szPort, "%d", &iTmp);
	//assert(sscanf(_szPort, "%d", &iTmp) < 1);
	cout << iTmp <<"\n";
	//assert(iTmp > 65535 || iTmp < 1);

	this->szPORT = _szPort;
	this->szBuf = '\0';
	this->iNumBytes = 0;
	this->szDelimiter = _szDelimiter;
	this->iYes = 1;

	//assert(_iSockType != SOCK_STREAM && _iSockType != SOCK_DGRAM);

	memset(&aiHints, 0, sizeof aiHints);
	aiHints.ai_family = AF_UNSPEC;
	aiHints.ai_socktype = _iSockType;
	if(_bIsServer)
		aiHints.ai_flags = AI_PASSIVE;

	if ((iRV = getaddrinfo(NULL, this->szPORT, &aiHints, &aiServInfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(iRV));
		exit(1);
	}
	if (_bIsServer) {
		for(this->aiP = this->aiServInfo; this->aiP != NULL; this->aiP = this->aiP->ai_next) {
			if ((this->iSockfd = socket(this->aiP->ai_family, this->aiP->ai_socktype, this->aiP->ai_protocol)) == -1) {
				perror("Server: Socket");
				continue;
			}

			if (setsockopt(this->iSockfd, SOL_SOCKET, SO_REUSEADDR, &this->iYes, sizeof(int)) == -1) {
				perror("setsockopt");
				exit(1);
			}

			if (bind(this->iSockfd, this->aiP->ai_addr, this->aiP->ai_addrlen) == -1) {
				close(this->iSockfd);
				perror("Server: Bind");
				continue;
			}

			break;
		}
	} else {

		for(this->aiP = this->aiServInfo; this->aiP != NULL; this->aiP = this->aiP->ai_next) {
			if ((this->iSockfd = socket(this->aiP->ai_family, this->aiP->ai_socktype,
					this->aiP->ai_protocol)) == -1) {
				perror("client: socket");
				continue;
			}
			if (_iSockType == SOCK_STREAM) {
				if (connect(this->iSockfd, this->aiP->ai_addr, this->aiP->ai_addrlen) == -1) {
					close(this->iSockfd);
					perror("client: connect");
					continue;
				}
			} else if (_iSockType == SOCK_DGRAM) {
				//Just so it finished
			} else {
				//Should never make it this far
			}
		}
	}
	if( this->aiP == NULL ) {

	}
	this->iSockStatus = this->iSockfd;
}

bool Socket::bClose() {
	return (close(this->iSockfd)) == 0 ? true : false;
}

bool Socket::bRestart(char* _szPort,int _iSockType, bool _bIsServer) {

	//int iTmp = 0;
	//sscanf(_szPort, "%d", &iTmp);
	//assert(sscanf( _szPort, "%d", &iTmp) < 1);
	//assert(iTmp > 65535 || iTmp < 1);

	this->szPORT = _szPort;
	this->szBuf = '\0';
	this->iNumBytes = 0;
	this->iYes = 1;
	memset(&aiHints, 0, sizeof aiHints);
	aiHints.ai_family = AF_UNSPEC;
	aiHints.ai_socktype = _iSockType;
	if(_bIsServer)
		aiHints.ai_flags = AI_PASSIVE;

	if ((iRV = getaddrinfo(NULL, this->szPORT, &aiHints, &aiServInfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(iRV));
		exit(1);
	}
	if (_bIsServer) {
		for(this->aiP = this->aiServInfo; this->aiP != NULL; this->aiP = this->aiP->ai_next) {
			if ((this->iSockfd = socket(this->aiP->ai_family, this->aiP->ai_socktype, this->aiP->ai_protocol)) == -1) {
				return false;
				continue;
			}

			if (setsockopt(this->iSockfd, SOL_SOCKET, SO_REUSEADDR, &this->iYes, sizeof(int)) == -1) {
				return false;
			}

			if (bind(this->iSockfd, this->aiP->ai_addr, this->aiP->ai_addrlen) == -1) {
				close(this->iSockfd);
				return false;
				continue;
			}

			break;
		}
	} else {

		for(this->aiP = this->aiServInfo; this->aiP != NULL; this->aiP = this->aiP->ai_next) {
			if ((this->iSockfd = socket(this->aiP->ai_family, this->aiP->ai_socktype,
					this->aiP->ai_protocol)) == -1) {
				return false;
				continue;
			}
			if (_iSockType == SOCK_STREAM) {
				if (connect(this->iSockfd, this->aiP->ai_addr, this->aiP->ai_addrlen) == -1) {
					close(this->iSockfd);
					perror("client: connect");
					continue;
				}
			} else if (_iSockType == SOCK_DGRAM) {
					//Just so it finished
			} else {
					//Should never make it this far
			}
		}

	}
	this->iSockStatus = this->iSockfd;
	return this->iSockStatus == 0 ? true : false;
}

Socket::~Socket() {
	if (this->iSockfd != -1)
		shutdown(this->iSockfd, 2);
}

TCPServer::TCPServer(char* _szPort, int _iMaxBacklog, int _iMaxClients) : Socket(_szPort, SOCK_STREAM, true, (char *) '\n') {
	this->iMaxBacklog = _iMaxBacklog;
	this->iMaxClients = _iMaxClients;
	this->szOutBuf = '\0';
	this->szInBuf = '\0';
	this->slSinSize = 0;
	this->iFDMax = this->iMaxClients;

	char* szIP;

	//clock_t start;
	//double duration;

	//start = clock();

	freeaddrinfo(this->aiServInfo);

	if (listen(this->iSockfd, this->iMaxClients) == -1) {

		perror("Listen");
		exit(1);
	}

	FD_SET(this->iSockfd, &fdMaster);

	this->iFDMax = this->iSockfd;
	this->fdReadfds = this->fdMaster;
	if(select(this->iFDMax+1, &this->fdReadfds, NULL, NULL, NULL) == -1) {
		perror("select");
		exit(4);
	}
	//this->iFDMax = this->iMaxClients;
	for (int i = 0; i <= this->iFDMax; i++) {
		if (FD_ISSET(i, &this->fdReadfds)) {
			if (i == this->iSockfd) {
				cout <<"Ping!\n";
				this->slAddrLen = sizeof this->saCliAddr;
				this->iNewfd = accept(this->iSockfd, (struct sockaddr *)&this->saCliAddr, &this->slAddrLen);
				cout << "Que?\n";
				printf("Server: new connection from %s on socket %d\n", inet_ntop(this->saCliAddr.ss_family, getInAddr((struct sockaddr *)&this->saCliAddr),this->sClientIP, INET6_ADDRSTRLEN), this->iNewfd);
				if (this->iNewfd == -1)
					perror("accept");
				else {
					cout << "Else\n";
					FD_SET(this->iNewfd, &this->fdMaster);
					if (this->iNewfd > this->iFDMax) {
						this->iFDMax = this->iNewfd;
					}
					szIP = (char *) inet_ntop(saCliAddr.ss_family, getInAddr((struct sockaddr*)&this->saCliAddr), this->sClientIP, INET_ADDRSTRLEN);
					this->vszIPs.push_back(szIP);
					this->mIPs[szIP] = i;
#ifdef DEBUG
					//printf("Server: new connection from % s on socket %d\n", inet_ntop(this->saCliAddr.ss_family, get_in_addr((struct sockaddr *)&this.saCliAddr),this->sClientIP, INET6_ADDRSTRLEN), this->iNewfd);
#endif
				}
			}
		}
	}
}




TCPServer::~TCPServer() {
	cout << "What double free?\n";
	this->~Socket();
	for (int i = 0; i <= this->iFDMax; i++) {
		if (FD_ISSET(i, &this->fdMaster)) {
			if (i != this->iNewfd && i != -1)
				shutdown(i, 2);
		}
	}

	if (this->iNewfd != -1)
			shutdown(this->iNewfd, 2);
}

void TCPServer::sendToAll(char* _szBuf) {

	this->szOutBuf = _szBuf;
	for (int i = 0; i <= this->iFDMax; i++) {
		if (FD_ISSET(i, &this->fdMaster)) {
			if(i != this->iSockfd) {
				if (sendAll(i, this->szOutBuf, (int) strlen(this->szOutBuf)) == -1) {
					perror("Server: Send");
				}
			}
		}
	}
}

void TCPServer::sendTo(char* _szBuf, int iSock) {
	//this->szOutBuf = _szBuf;
	sendAll(iSock, _szBuf, (int) strlen(_szBuf));
}

void TCPServer::tryRecieve() {
	char* szTmpBuf = '\0';
	for (int i = 0; i <= this->iFDMax; i++){
		do {
			if ((this->iNumBytes = recv(i, szTmpBuf, 1, 0)) == -1) {
				if (this->iNumBytes == 0) {
#ifdef DEBUG
					printf("selectserver: socket %d hung up\n", i);
#endif
				} else {
					perror("recv");
				}
				close(i); // bye!
				FD_CLR(i, &this->fdMaster); // remove from master set
			}
			sprintf(this->szInBuf, "%s%s", this->szInBuf, szTmpBuf);
		} while (strcmp(szTmpBuf, this->szDelimiter) != 0);
	}
}


void TCPServer::acceptClients(uint32 _iMoreClients) {
	//this->iFDMax += _iMoreClients;
	char* szIP;

	if (listen(this->iSockfd, this->iMaxClients) == -1) {

		perror("Listen");
		exit(1);
	}

	FD_SET(this->iSockfd, &fdMaster);

	this->iFDMax = this->iSockfd;
	this->fdReadfds = this->fdMaster;
	if(select(this->iFDMax+1, &this->fdReadfds, NULL, NULL, NULL) == -1) {
		perror("select");
		exit(4);
	}
	for (int i = 0; i <= this->iFDMax; i++) {
		if (FD_ISSET(i, &this->fdReadfds)) {
			if (i == this->iSockfd) {
				cout <<"Ping!\n";
				this->slAddrLen = sizeof this->saCliAddr;
				this->iNewfd = accept(this->iSockfd, (struct sockaddr *)&this->saCliAddr, &this->slAddrLen);
				cout << "Que?\n";
				printf("Server: new connection from %s on socket %d\n", inet_ntop(this->saCliAddr.ss_family, getInAddr((struct sockaddr *)&this->saCliAddr),this->sClientIP, INET6_ADDRSTRLEN), this->iNewfd);
				if (this->iNewfd == -1)
					perror("accept");
				else {
					cout << "Else\n";
					FD_SET(this->iNewfd, &this->fdMaster);
					if (this->iNewfd > this->iFDMax) {
						this->iFDMax = this->iNewfd;
					}
					szIP = (char *) inet_ntop(saCliAddr.ss_family, getInAddr((struct sockaddr*)&this->saCliAddr), this->sClientIP, INET_ADDRSTRLEN);
					this->vszIPs.push_back(szIP);
					this->mIPs[szIP] = i;
#ifdef DEBUG
					//printf("Server: new connection from % s on socket %d\n", inet_ntop(this->saCliAddr.ss_family, get_in_addr((struct sockaddr *)&this.saCliAddr),this->sClientIP, INET6_ADDRSTRLEN), this->iNewfd);
#endif
				}
			}
		}
	}
}

void TCPServer::kickAddr(char* _szIP) {
	int iSock = this->mIPs[_szIP];
	shutdown(iSock, 2);
}

void TCPServer::kickAll() {
	for (int i = 0; i <= this->iFDMax; i++) {
		shutdown(i, 2);
	}
}
