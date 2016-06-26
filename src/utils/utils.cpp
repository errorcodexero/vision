#include "../../include/utils/utils.h"

using namespace std;

vector <char* > vszParseString( char* _szString, char* _szDilimiter) {

	int iCurrVec = 0;

	unsigned int uiIndex = 0;

	char* szTmpBuf = (char *) malloc(sizeof (char));
	char* szCurrStr = (char* ) malloc(sizeof _szString + 1);
	szCurrStr[0] = '\0';
	vector <char* > vszBuf_;


	do {
		szTmpBuf[0] = _szString[uiIndex];
		if (strcmp(szTmpBuf, _szDilimiter) == 0 || strcmp(szTmpBuf, (char* ) "\n") == 0) {
			vszBuf_.push_back(szCurrStr);
			iCurrVec++;
			memset(szCurrStr, 0, sizeof(&szCurrStr));
			uiIndex++;
		} else {
			szCurrStr[uiIndex] = szTmpBuf[0];
			uiIndex++;
		}
		//cout << "\n" << iCurrVec << "."<< szTmpBuf << "\n";
	} while (uiIndex <= strlen(_szString));
	return vszBuf_;
}

void exitWithError(std::string _strErrorMsg, int _iExitNumber) {
	cout << _strErrorMsg << "\n";
	exit(_iExitNumber);
}

char* szTruncateByDelimiter(char* _szBuf, char* _szDelimiter) {
	int index = 0;

	char* szBuf = (char *) malloc (sizeof _szBuf);
	char* szTmpBuf = (char *) malloc(sizeof (char));

	do {
		if (index > (int) sizeof _szBuf)
			return _szBuf;
		szTmpBuf[0] = _szBuf[index];
		if (strcmp(szTmpBuf, _szDelimiter) == 0)
			break;
		szBuf[index] = _szBuf[index];
		cout << szTmpBuf;
		index++;
	} while (strcmp(szTmpBuf, _szDelimiter) != 0);
	return szBuf;
}

bool bIsStringIP( char* _szString) {
	int value = 0;
	bool bIsLessThan256 = false;
	vector <char* > vszBuf_;
	vszBuf_ = vszParseString(_szString, (char *) ".");

	if (vszBuf_.size() == 3) {
		for (uint32 i = 0; i < vszBuf_.size(); i++) {
			if(sscanf("%d", vszBuf_[i], &value) < 1)
				break;
			if (value <= 256 && value >= 0)
				bIsLessThan256 = true;
			else {
				bIsLessThan256 = false;
				break;
			}
		}
		if (bIsLessThan256) {
			return true;
		} else {
			return false;
		}

	}

	return false;
}
