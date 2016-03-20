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

#include "vision/image.hpp"
#include "utils/logger.cpp"
#include "utils/math.hpp"
#include "utils/network.hpp"

int main (int argc, char* argv[]) {
	Server server((char*) "6425", SOCK_STREAM, 0, 1, false);
	if(!server.bBroadcast((char*) "Hello\n") && !server.bBroadcast((char*) "World\n")) {
		cout << "ERROR" << endl;
		server.~Server();
	}
	else
		cout << "Success!" << endl;
	server.~Server();
}
