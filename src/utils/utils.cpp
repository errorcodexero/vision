#include "utils/utils.hpp"

using namespace std;

vector <char* > vszParseString(char* _szString, char* _szDilimiter) {

	int iCurrVec = 0;

	unsigned int uiIndex;

	char szTmpBuf[1];
	char* szCurrStr;
	vector <char* > vszBuf;


	do {
		szTmpBuf[0] = _szString[uiIndex];
		if (strcmp(szTmpBuf, _szDilimiter) == 0) {
			vszBuf.push_back(szCurrStr);
			iCurrVec++;
			memset(szCurrStr, 0, sizeof(&szCurrStr));
		} else {
			szCurrStr[uiIndex] = szTmpBuf[0];
			uiIndex++;
		}
	} while (uiIndex < strlen(_szString));
	return vszBuf;
}

void exitWithError(std::string _strErrorMsg, int _iExitNumber) {
	cout << _strErrorMsg << "\n";
	exit(_iExitNumber);
}

char* szTruncateByDelimiter(char* _szBuf, char* _szDilimiter) {
	int index = 0;

	char* szBuf = new char[sizeof _szBuf];
	char cTmpBuf[1];

	do {
		cTmpBuf[0] = _szBuf[index];
		if (cTmpBuf == _szDilimiter)
			break;
		szBuf[index] = _szBuf[index];
	} while (cTmpBuf != _szDilimiter);
	return szBuf;
}

bool bIsStringIP( char* _szString) {
	vector <char* > vszBuf;
	vszBuf = vszParseString(_szString, (char *) ".");

	if (vszBuf.size() != 4)
		return true;

	return false;
}
