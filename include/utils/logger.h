#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_
/*
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/gpu/gpu.hpp>

#define LOG_NAME "vision.log"

std::string sGetFormattedTime();

enum EventID { CRASH, HANG, SOCKET_DISCONNET, SOCKET_CONNECT, SOCKET_HANG, SOCKET_RECIEVE, SOCKET_SEND, OTHER};

class Event {
public:

	Event(EventID EventID, std::string sEventMsg);
	~Event();
	EventID EventID;
	std::string sEventMsg;

protected:



private:



};*/

class LogWriter {

	LogWriter(std::string sFilePath = "");
	~LogWriter();
public:

	void writeLogEvent(std::string sTime, Event logEvent);

	int iGetLogStatus();

private:

	int logStatus;
	std::ofstream ofFile;

protected:


};

class LogReader {

	LogReader(std::string sFilePath);
	~LogReader();
public:

	void readLogEvent(std::string sTime);

	int iGetLogStatus();

private:

	int logStatus;
	std::ifstream ifFile;

protected:

};

#endif /*_LOGGER_HPP_*/
