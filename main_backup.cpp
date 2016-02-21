#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
}
//Local files
#include "VisualUtils.h"
#include "errorList.h"

#define PORT "6425"
#define BACKLOG 0

using namespace cv;
using namespace std;
extern "C" {
void handler();
}
int sendall(int s, char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;

    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
}

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

vector <KeyPoint> blobDetect (Mat _mFrame, Scalar _sColor, Mat _mOutFrame);
int image(string LOCATION);
int camera();
float fGetAnglefromPixel ( int _iFrameWidth, int _iFOV, int _iX);

int main(int argc, char *argv[]) {	
	if (argc <= 1) 
		return camera();
    	else if (argc > 1) 
	   	return image(argv[1]);
    	else 
		cerr << "Error! Invalid Input!" << endl;
}


int camera() {
initModule_features2d();
	float angle;
    bool die = false;
	string filename("snapshot");
	string suffix(".png");
	int i_snap(0), iter(0);
    vector < vector <Point> > contours;
    vector<Rect > boundRect;
	vector <KeyPoint> keypoints;
	vector <Point> centers;	        
	Mat frame(Size(480, 360), CV_8UC3, Scalar(0));
    VideoCapture cap ("http://root:1425@10.14.25.17/mjpg/video.mjpg?dummy=video.mjpg");

    if (!cap.isOpened())
    	{
            cout <<"Cannot open the Axis Cam" << endl;
            return -1;
        }
		#ifdef SHOWCAMERA
        namedWindow("Output", CV_WINDOW_AUTOSIZE);
		#endif
        cout << "Camera opened Successfully" << endl;
		if(!fork()){
			handler();
		}
        while (die == false) {
            bool rSuccess = cap.read(frame);
            if (!rSuccess)
            {
                cout << "Cannot Read Frame" << endl;
                return -1;
            }
		#ifdef DEBUG
	    cout << "Frame Successfully Read" << endl;
		#endif            
#ifdef SHOWCAMERA
	    imshow("Output", frame);
#endif
            //Matrixes to be converted or modified
            Mat HSVMat(Size(480, 360), CV_8UC3, Scalar (0));
            Mat PostFrame(Size(480, 360), CV_8UC3, Scalar (0));
            Mat PostFrame2(Size(640, 400), CV_8UC3, Scalar (0));

            //Set up the images for processing
            frame.copyTo(PostFrame);
            frame.copyTo(HSVMat);
            cvtColor(HSVMat, HSVMat, CV_RGB2HSV);
		#ifdef DEBUG
		cout << "Mats Copied to" << endl;
		#endif
            //Define variables to be used in the thresholding process
	    Mat HSVFrame(Size(480, 360), CV_8UC3, Scalar (105, 200, 200));       
	    #ifdef GREEN
	    Mat HSVMin(Size(480, 360), CV_8UC3, Scalar (35, 200, 150));
            Mat HSVMax(Size(480, 360), CV_8UC3, Scalar (85, 255, 255));
            #endif
	    #ifdef BLUE
	    Mat HSVMin(Size(480, 360), CV_8UC3, Scalar (-15, 200, 100));
            Mat HSVMax(Size(480, 360), CV_8UC3, Scalar (15, 255, 255));
            #endif
	    #ifdef RED
	    Mat HSVMin(Size(480, 360), CV_8UC3, Scalar (105, 200, 150));
            Mat HSVMax(Size(480, 360), CV_8UC3, Scalar (135, 255, 255));
            #endif
	    Mat ThreshMat(Size(480, 360), CV_8U, Scalar(0));
	    
	    cvtColor(frame, HSVFrame, CV_RGB2HSV);

            //Begin the Processing
            Threshold(ThreshMat, HSVMin, HSVMax, HSVFrame);
            contours = edgeDetect(ThreshMat, Scalar(0, 255, 0), PostFrame);
            boundRect = ShowTargets(contours, PostFrame);
 		//imshow ("Output", PostFrame);
	    
		
	#ifdef DEBUG
	cout << "Processing Done" << endl;
	#ifdef SHOWCAMERA
	imshow ("THRESH", ThreshMat);	
	#endif
	#endif
	
	keypoints = blobDetect(ThreshMat, Scalar(185, 215, 255), PostFrame2);      
	PostFrame2 = getLeftRight(PostFrame, 0.5, 30, Scalar(0,255,0), 1, boundRect);
#ifdef SHOWCAMERA
imshow ("Output", PostFrame);
#endif
char k = cvWaitKey(5);
		if (k == 8) {
			std::ostringstream file;
			file << filename << i_snap << suffix;
			cv::imwrite(file.str(), frame);
			i_snap++;
		}
		if (iter >= 100000000)
			break;
		iter++;

            }
   return 0;     

    
}

int image(string LOCATION) {
	if (LOCATION.size() == 0) {
		cerr << "ERROR! NO LOCATION PROVIDED!" << endl;
		exit (1);		
	}	
     	initModule_features2d();
        bool finishedLoop = false;
        int i_snap(0);
        bool die = false;
        string filename("snapshot");
        string suffix(".png");
        vector < vector <Point> > contours;
        vector<Rect > boundRect;
        Mat frame(Size(640, 400), CV_8UC3, Scalar(0));
        //namedWindow("Output", CV_WINDOW_AUTOSIZE);

        try {
            frame = imread(LOCATION, CV_LOAD_IMAGE_COLOR);
            //imshow("Output", frame);
            //throw ERROR_IMG_LOAD;
        }
        catch (int e) {
            cerr << "Error! Code ID: " << e << " Cannot Open Picture" << endl;
            cout << "Choose New File or Quit? Y/n: ";
            string YorN;
            cin >> YorN;
            cout << endl;
            if (YorN == "Y" || YorN == "y") {

            cout << "New Location: ";
            cin >> LOCATION;
            //frame = imread(LOCATION/*, CV_LOAD_IMAGE_COLOR*/);
            }
            else {
                cout << "Exiting" << endl;
                exit(30);
            }

        }
        //Eliminate file extensions
        LOCATION.pop_back();
        LOCATION.pop_back();
        LOCATION.pop_back();
        LOCATION.pop_back();

        LOCATION += "_Proc";
        LOCATION += ".png";


        //cout << "TEST" << endl;
        while (die == false) {
            //cout << "TEST" << endl;

            Mat HSVMat(Size(640, 400), CV_8UC3, Scalar (0));
            Mat PostFrame(Size(640, 400), CV_8UC3, Scalar (0));
            frame.copyTo(PostFrame);
            frame.copyTo(HSVMat);

            //cvtColor(frame, HSVMat, CV_RGB2HSV);
	
            Mat HSVMin(Size(640, 400), CV_8UC3, Scalar (0, 230, 0));
            Mat HSVMax(Size(640, 400), CV_8UC3, Scalar (255, 255, 255));
            Mat ThreshMat(Size(640, 400), CV_8U, Scalar(0));
            Mat PostFrame2(Size(640, 400), CV_8UC3, Scalar (0));
            Threshold(ThreshMat, HSVMin, HSVMax, HSVMat);
            contours = edgeDetect(ThreshMat, Scalar(0, 255, 0), PostFrame);
            boundRect = ShowTargets(contours, PostFrame);
		#ifdef DEBUG
		for (unsigned int i = 0; i < boundRect.size(); i++) {
			cout << "(Top Left) " <<  i << ") "<<boundRect[i].tl().x << "," << boundRect[i].tl().y << endl;
			cout <<  "(Bottom Right) "<< i << ") "<<boundRect[i].br().x << "," << boundRect[i].br().y << endl;	
		}
		#endif
    	    PostFrame2 = getLeftRight(PostFrame, 0.5, 20, Scalar(0,255,0), 1, boundRect);
	    if (!finishedLoop){
            imwrite(LOCATION, PostFrame);
            finishedLoop = true;
		}
		cout << boundRect.size() << " RECTANGLES DETECTED" << endl;
            imshow ("Post", PostFrame);
            char k = cvWaitKey(5);
            if (k == 8) {
                std::ostringstream file;
                file << filename << i_snap << suffix;
                cv::imwrite(file.str(), frame);
                i_snap++;
            }


        }
	return 0;
              
}



/*vector <KeyPoint> blobDetect (Mat & _mFrame, Scalar _sColor = Scalar(185, 218, 255), bool _bDrawPoints) {
	vector <KeyPoint> _vKeypoints;	
	SimpleBlobDetector _sbdDetector;
	_sbdDetector.detect(_mFrame, _vKeypoints);
	if (_bDrawPoints) {
		drawKeypoints( _mFrame, _vKeypoints, _mFrame, _sColor,DrawMatchesFlags::DRAW_RICH_KEYPOINTS );			
	}
	return _vKeypoints;
}*/
vector <KeyPoint> blobDetect (Mat _mFrame, Scalar _sColor, Mat _mOutFrame) {
	vector <KeyPoint> _vKeypoints;	
	SimpleBlobDetector _sbdDetector;

	_sbdDetector.detect(_mFrame, _vKeypoints);
	drawKeypoints( _mFrame, _vKeypoints, _mOutFrame, _sColor,DrawMatchesFlags::DRAW_RICH_KEYPOINTS );			
	return _vKeypoints;
}
extern "C" {
void handler() {

		int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
		struct addrinfo hints, *servinfo, *p;
		struct sockaddr_storage cli_addr; // connector's address information
		socklen_t sin_size;
		struct sigaction sa;
    	int yes=1;
    	char s[INET6_ADDRSTRLEN];
    	int rv;
    	char buf[256];
    	int numchars = 0;
    	int randint = 0;

    	memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;
    	hints.ai_socktype = SOCK_STREAM;
    	hints.ai_flags = AI_PASSIVE; // use my IP

    	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        	exit(1);
    	}

	    // loop through all the results and bind to the first we can
    	for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            	perror("server: socket");
            	continue;
        	}

        	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            	perror("setsockopt");
            	exit(1);
        	}

        	if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            	close(sockfd);
            	perror("server: bind");
            	continue;
        	}

        	break;
    	}

    	freeaddrinfo(servinfo); // all done with this structure

    	if (p == NULL)  {
        	fprintf(stderr, "server: failed to bind\n");
        	exit(1);
    	}

    	if (listen(sockfd, BACKLOG) == -1) {
        	perror("listen");
        	exit(1);
    	}

    	sa.sa_handler = sigchld_handler; // reap all dead processes
    	sigemptyset(&sa.sa_mask);
    	sa.sa_flags = SA_RESTART;
    	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        	perror("sigaction");
        	exit(1);
    	}

    	printf("server: waiting for connections...\n");

    	while(1) {  // main accept() loop
        	sin_size = sizeof cli_addr;
        	new_fd = accept(sockfd, (struct sockaddr *)&cli_addr, &sin_size);
        	if (new_fd == -1) {
            	perror("accept");
            	continue;
        	}

        	inet_ntop(cli_addr.ss_family,
            get_in_addr((struct sockaddr *)&cli_addr), s, sizeof s);
        	printf("server: got connection from %s\n", s);

        	if (!fork()) { // this is the child process
            	close(sockfd); // child doesn't need the listener
            	snprintf(buf, sizeof buf, "Communications Initialized\n");
            	//buf[strlen(buf)] = '\0';
            	numchars = (int ) strlen(buf);
            	int i = 0;
            	for (i = 0; i <= 100; i++ ) {
	            	//buf[sizeof buf] = '\0';
            		if (sendall(new_fd, buf, &numchars) == -1)
            			perror("send");

            		printf("Data is: %s", buf);
            		//strcpy(buf, "");
            		//memset(buf, 2, sizeof buf);
            		//randint = rand();
            		snprintf(buf, sizeof buf, "%d\n", i);
            		numchars = (int ) strlen(buf);
            	}
            	close(new_fd);
            	exit(0);
        	}
        	close(new_fd);  // parent doesn't need this
    	}
	}
}



