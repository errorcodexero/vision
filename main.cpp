#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <pthread.h>

//Local files
#include "./include/VisualUtils.h"
#include "./include/projectile.h"
#include "./include/launcher.h"
#include "./include/errorList.h"

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << i << ") " << argv[i] << endl;
        }
    if (argc < 1) {
        initModule_features2d();

        bool die(false);
        vector < vector <Point> > contours;
        Mat frame(Size(480, 360), CV_8UC3, Scalar(0));
        VideoCapture cap ("http://root:1425@10.14.25.17/mjpg/video.mjpg?dummy=video.mjpg");

        if (!cap.isOpened())
        {
            cout <<"Cannot open the Axis Cam" << endl;
            return -1;
        }
        namedWindow("Output", CV_WINDOW_AUTOSIZE);
        while (die == false) {
            bool rSuccess = cap.read(frame);
            if (!rSuccess)
            {
                cout << "Cannot Read Frame" << endl;
                return -1;
            }

            imshow("Output", frame);

            //Matrixes to be converted or modified
            Mat HSVMat(Size(480, 360), CV_8UC3, Scalar (0));
            Mat PostFrame(Size(480, 360), CV_8UC3, Scalar (0));

            //Set up the images for processing
            frame.copyTo(PostFrame);
            frame.copyTo(HSVMat);
            cvtColor(HSVMat, HSVMat, CV_RGB2HSV);

            //Define variables to be used in the thresholding process
            Mat HSVMin(Size(480, 360), CV_8UC3, Scalar (0, 230, 0));
            Mat HSVMax(Size(480, 360), CV_8UC3, Scalar (255, 255, 255));
            Mat ThreshMat(Size(480, 360), CV_8U, Scalar(0));

            //Begin the Processing
            Threshold(ThreshMat, HSVMin, HSVMax, frame);
            contours = edgeDetect(ThreshMat, Scalar(0, 255, 0), PostFrame);
            ShowTargets(contours, PostFrame);

            imshow ("Post", PostFrame);

            }
        return 0;

    }
    else if (argc >= 1) {
        initModule_features2d();

        int i_snap(0);
        bool die = false;
        string filename("snapshot");
        string suffix(".png");
        vector < vector <Point> > contours;
        vector<Rect > boundRect;
        string LOCATION;
        Mat frame(Size(640, 400), CV_8UC3, Scalar(0));
        namedWindow("Output", CV_WINDOW_AUTOSIZE);
        try {
            LOCATION = string(argv[1]);
            throw "Failed to Validate input";
        }
        catch (string e) {
            cout << e << endl;

        }

        try {
            frame = imread(LOCATION, CV_LOAD_IMAGE_COLOR);
            imshow("Output", frame);
            throw ERROR_IMG_LOAD;
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
            frame = imread(LOCATION, CV_LOAD_IMAGE_COLOR);
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

        while (die == false) {
            cout << frame.size() << endl;
            Mat HSVMat(Size(640, 400), CV_8UC3, Scalar (0));
            Mat PostFrame(Size(640, 400), CV_8UC3, Scalar (0));
            frame.copyTo(PostFrame);
            frame.copyTo(HSVMat);
            cvtColor(HSVMat, HSVMat, CV_RGB2HSV);

            Mat HSVMin(Size(640, 400), CV_8UC3, Scalar (0, 230, 0));
            Mat HSVMax(Size(640, 400), CV_8UC3, Scalar (255, 255, 255));
            Mat ThreshMat(Size(640, 400), CV_8U, Scalar(0));
            Threshold(frame, HSVMin, HSVMax, ThreshMat);
            contours = edgeDetect(ThreshMat, Scalar(0, 255, 0), PostFrame);
            boundRect = ShowTargets(contours, PostFrame);

            imshow ("Post", PostFrame);
            imwrite(LOCATION, PostFrame);
            char k = cvWaitKey(5);
            if (k == 8) {
                std::ostringstream file;
                file << filename << i_snap << suffix;
                cv::imwrite(file.str(), frame);
                i_snap++;
            }
        return 0;

        }
     }
    else {
        cerr << "Error! Invalid Input!" << endl;
    }
}
