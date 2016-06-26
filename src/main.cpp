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

#include "../include/utils/math/math.hpp"
#include "../include/utils/math/statistics.h"
#include "../include/utils/network.h"
#include "vision/image.hpp"
#include "utils/logger.cpp"

int main (int argc, char* argv[]) {
	net::tcp_server server((char *) "6425", 0, 2);
	while (true) {
		server.accept_clients(2);
		server.send_to_all((char *) "Hello World\n");
		for (unsigned int i = 0; i < server.ip_list.size(); i++)
		server.kick_all();
	}
}
