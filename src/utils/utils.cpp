#include "utils/utils.hpp"

using namespace std;

vector <char* > vszParseString( char* _szString, char* _szDilimiter) {

	int iCurrVec = 0;

	unsigned int uiIndex = 0;

	char szTmpBuf[1];
	char* szCurrStr = (char *) malloc ( sizeof _szString * sizeof (char ) );
	vector <char* > vszBuf_;


	do {
		szTmpBuf[0] = _szString[uiIndex];
		if (&szTmpBuf[0] == _szDilimiter || szTmpBuf[0] == '\n') {
			vszBuf_.push_back(szCurrStr);
			iCurrVec++;
			memset(szCurrStr, 0, sizeof(&szCurrStr));
			uiIndex++;
		} else {
			szCurrStr[uiIndex] = szTmpBuf[0];
			uiIndex++;
		}
	} while (uiIndex < strlen(_szString));
	return vszBuf_;
}

void exitWithError(std::string _strErrorMsg, int _iExitNumber) {
	cout << _strErrorMsg << "\n";
	exit(_iExitNumber);
}

char* szTruncateByDelimiter(char* _szBuf, char* _szDilimiter) {
	int index = 0;

	char* szBuf = new char[sizeof _szBuf];
	char cTmpBuf;

	do {
		cTmpBuf = _szBuf[index];
		if (&cTmpBuf == _szDilimiter)
			break;
		szBuf[index] = _szBuf[index];
	} while (&cTmpBuf != _szDilimiter);
	return szBuf;
}

bool bIsStringIP( char* _szString) {
	int value = 0;
	bool bIsLessThan256 = false;
	vector <char* > vszBuf_;
	vszBuf_ = vszParseString(_szString, (char *) ".");

	if (vszBuf_.size() >= 5) {
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
