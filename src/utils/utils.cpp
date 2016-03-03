#include "utils/utils.hpp"

using namespace std;

vector <char* > szParseString(char * _szString, char * _szDilimiter) {

	int _iIndex;
	int _iCurrVec = 0;

	char _szTmpBuf[1];
	char _szCurrStr[];
	vector <char[] > _szBuf;


	do {
		_szTmpBuf = _szString[_iIndex];
		if (strcmp(_szTmpBuf, _szDilimiter) == 0) {
			_szBuf.push_back(_szCurrStr);
			_iCurrVec++;
			memset(_szCurrStr, 0, sizeof _szCurrStr);
		}
			_szCurrStr += _szTmpBuf;
			_iIndex++;
	} while (_iIndex < strlen(_szString));
	return _szBuf;
}
