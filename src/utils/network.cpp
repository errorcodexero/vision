#include "utils/network.hpp"

using namespace std;

void *getInAddr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);

}

int sendAll(int _iS, char* _szBuf, int* _iLen) {
	int iTotal = 0;
	int iBytesLeft = *_iLen;
	int iN;

	while (iTotal < *_iLen) {
		iN = send(_iS, _szBuf+iTotal, iBytesLeft, 0);
		if (iN == -1 ) { break; }
		iTotal += iN;
		iBytesLeft -=iN;
	}

	*_iLen = iTotal;

	return iN==-1?-1:0;
}

void sigChildHandler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}
