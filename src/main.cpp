#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <signal.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/gpu/gpu.hpp>

#include "vision/image.hpp"
#include "utils/logger.cpp"
#include "utils/math.hpp"
#include "utils/network.hpp"

int main (int argc, char* argv[]) {
	Client client((char* ) "127.0.0.1",(char*) "6425", SOCK_STREAM, (char*) "\n");
	client.bRecv();
	cout << client.szGetData();
	if(client.szGetData() == (char*) "Hello World!\n") {
		cout << "Success!" << endl;
		client.~Client();
	}
	else {
		cout << "ERROR" << endl;
		client.~Client();
	}

}
