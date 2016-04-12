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
#include "utils/math/math.hpp"
#include "utils/math/statistics.hpp"
#include "utils/network.hpp"

int main (int argc, char* argv[]) {
	TCPServer server((char *) "6425", 0, 2);
	while (1) {
		server.acceptClients(1);
		server.sendToAll((char *) "Hello World\n");
		for (unsigned int i = 0; i < server.vszIPs.size(); i++)
			//cout << server.vszIPs[i] << "\n";
		server.kickAll();
	//server.~TCPServer();
	}
}
