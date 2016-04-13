#include <ctime>

using namespace std;

#include "utils/logger.hpp"

Event::Event(EventID eventID, std::string sEventMsg) {
	this->EventID = EventID;
	this->sEventMsg = sEventMsg;
}

string sGetFormattedTime() {
	time_t tNow = time(0);
	string sTempTime = ctime(&tNow);

	tm *gmtm = gmtime(&tNow);

	string sTime;
	sTime.append("[");
	sTime.append(&gmtm.tm_hour);
	sTime.append(":");
	sTime.append(gmtm->tm_min)
	sTime.append(":") + gmtm->tm_sec + "]");
	return sTime;
}

LogWriter::LogWriter(string sFilePath) {
	this->ofFile.open(sFilePath.c_str() + LOG_NAME);
	this->logStatus = 1;
}

void LogWriter::writeLogEvent(string sTime, Event logEvent) {
	this->ofFile << sTime << " " << logEvent.EventID << " : " << logEvent.sEventMsg;
}
