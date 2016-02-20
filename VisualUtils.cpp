#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <pthread.h>

#include "VisualUtils.h"

//BGR
static const cv::Scalar sRED(0,0,255);
static const cv::Scalar sGREEN(0,255,0);
static const cv::Scalar sBLUE(255, 0, 0);

using namespace std;
using namespace cv;

template <class T>
int approx(T input, T target, T range) {
	if (input <= (target + range) && input >= (target - range))
		return 0;
 	else {
		if (!(input <= (target + range)) && input >= (target - range))
			return -1; //-1
		if (input <= (input + range) && !(input >= (target - range)))
			return 1; //1
	}
	return 0;
}

void drawReticle (cv::Mat & inframe, int size, Point loc, Scalar color) {
	Point minX (((loc.x - 18 * (size) - 12)), loc.y);
	Point maxX (((loc.x + 18 * (size) + 12)), loc.y);
	Point minY (loc.x, ((loc.y - (18 * size)) - 12));
	Point maxY (loc.x, ((loc.y + (18 * size)) + 12));

	cv::circle(inframe, loc, (36 * (size / 2)), color, size, 8, 0);
	if (size <= 1) 	
	cv::circle(inframe, loc, (36 * size), color, size, 8, 0);

	cv::line(inframe, minX, maxX, color, size, 8, 0);
	cv::line(inframe, minY, maxY, color, size, 8, 0);
}

vector<vector<Point> > edgeDetect(Mat input, Scalar color, Mat & output) {
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours( input, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	
	//This does nothing. 0 isn't greater that 0...
	/*unsigned int idx = 0;
	if (idx > hierarchy.size()) {

		for ( ; idx >= 0; idx = hierarchy[idx][0]) {

			drawContours( output, contours, idx, color, CV_FILLED, 8, hierarchy);
		}
	}*/
	return contours;
}
cv::Point getMean(cv::Point pt1, cv::Point pt2) {
	return Point(((pt1.x + pt2.x)/2), ((pt1.y + pt2.y)/2));
}
vector < Rect> ShowTargets(const vector <vector < Point > > & contours, Mat frame) {
	vector< Rect > boundRect( contours.size());
	//vector< Point2f > center(contours.size());
	//vector< float > radius(contours.size());
	for (unsigned int i = 0; i < contours.size(); i++) {
		vector< Point > contours_poly( contours.size());
		//The Number 3 is used to denote the kernel size, or the size of the buffer area it will look at
		approxPolyDP( Mat(contours[i]), contours_poly, 3, true);
		boundRect[i] = boundingRect( Mat (contours_poly));
	}
	for (unsigned int i = 0; i < contours.size(); i++) {
		//8 is always 8 in this position in code, and 2 is thickness
		rectangle (frame, boundRect[i].tl(),boundRect[i].br(), sBLUE, 2, 8, 0);
		Point pt1 = boundRect[i].tl();
		Point pt2 = boundRect[i].br();
		cv::Point center = getMean(pt1, pt2);
		//drawReticle(frame, 2, center, sRED);
	}
	return boundRect;
}
void Threshold(Mat & threshMat, Mat HSVMin, Mat HSVMax, Mat frame) {
	inRange(frame, HSVMin, HSVMax, threshMat);
}
//Not a point, the midline distance, NOT ACTUALL PROX, IF NEGATIVE IT IS TO THE LEFT
/*int getProxToPoint (cv::Point pt1, Mat frame) {
	int midline = (frame.cols / 2);
	return (midline - pt1.x);
	

}*/
int getProxToPoint (cv::Point pt1, int midline) {
	//int midline = (frame.cols / 2);
	return (midline - pt1.x);
	

}



/*Mat getLeftRight(Mat frame, double scale, int range, Scalar color, int thickness, vector <Rect > boundRects) {
	cv::Point point;
	int dist;
	int const midline = (frame.cols / 2);
	
	for (unsigned int i = 0 ; i < boundRects.size(); i++) {
		
		cv::Point p1 = boundRects[i].tl();
		cv::Point p2 = boundRects[i].br();
		point = Point((p2.x-(int) (10*scale)), (p1.y-(int) (20*scale)));
		#ifdef DEBUG
		cout << "RECT " << i << endl;
		#endif
		cv::Point center = Point(((p1.x + p2.x)/2), ((p1.y + p2.y)/2));		
		#ifdef DEBUG		
		cout << "Midline is at " <<midline << endl;
		cout << "Center) "  << center.x << "," << center.y << endl;
		#endif
		dist = getProxToPoint(center, midline);
		auto display = [&](string asdf){ putText(frame, asdf, point, FONT_HERSHEY_SIMPLEX, scale, color, thickness, 8, false);};
		int iIsLeftRight = approx((midline-dist),midline, range);
		if (iIsLeftRight == 0) { 
			display("Centered");
			#ifdef DEBUG
			cout << "CENTERED" << endl;
			#endif
		} else if (iIsLeftRight == 1) {
			display("Left");
			#ifdef DEBUG
			cout << "LEFT" << endl;
			#endif
		} else if (iIsLeftRight == -1) {
			display("Right");
			#ifdef DEBUG
			cout << "RIGHT" << endl;
			#endif
    		}
		else {
			cout << "ERROR OUT OF BOUNDS" << endl;
		}	
		
	}
	return frame;
}*/

float fGetAnglefromPixel ( float _fMidLine, int _iFOV, float _fX) {
	cout << _fX << endl;	
	float _fRatioOfXToFrame = _fX/(_fMidLine);
	cout << _fRatioOfXToFrame << endl;
	float _fAngle = _fRatioOfXToFrame * (_iFOV/2);
	cout << _fAngle;	
	if (_fX < _fMidLine) {
		_fAngle = (((_iFOV/2) - _fAngle)* -1);
	}
	else {
		_fAngle = (_fAngle - (_iFOV/2));
	}
	cout << _fAngle << endl;
	return _fAngle;
}

Mat getLeftRight(Mat frame, double scale, int range, Scalar color, int thickness, vector <Rect > boundRects) {
	cv::Point point;
	int dist;
	int const midline = (frame.cols / 2);
string outtext;
	vector <Point> centers;
	for (unsigned int i = 0 ; i < boundRects.size(); i++) {
		
		cv::Point p1 = boundRects[i].tl();
		cv::Point p2 = boundRects[i].br();
		point = Point((p2.x-(int) (10*scale)), (p1.y-(int) (20*scale)));
		#ifdef DEBUG
		cout << "RECT " << i << endl;
		#endif
		cv::Point center = Point(((p1.x + p2.x)/2), ((p1.y + p2.y)/2));		
		#ifdef DEBUG		
		cout << "Midline is at " <<midline << endl;
		cout << "Center) "  << center.x << "," << center.y << endl;
		#endif
		dist = getProxToPoint(center, midline);
		auto display = [&](string asdf){ putText(frame, asdf, point, FONT_HERSHEY_SIMPLEX, scale, color, thickness, 8, false);};
		int iIsLeftRight = approx((midline-dist),midline, range);
		float angle = fGetAnglefromPixel( midline, 67, center.x);		
		if (iIsLeftRight == 0) {
			outtext = "Centered " + to_string(angle); 
			display(outtext);
			#ifdef DEBUG
			cout << "CENTERED " << angle << endl;
			#endif
		} else if (iIsLeftRight == 1) {
			outtext = "Left " + to_string(angle);
			display(outtext);
			#ifdef DEBUG
			cout << "LEFT " << angle << endl;
			#endif
		} else if (iIsLeftRight == -1) {
			outtext = "Right " + to_string(angle);
			display(outtext);
			#ifdef DEBUG
			cout << "RIGHT " << angle << endl;
			#endif
    		}
		else {
			cout << "ERROR OUT OF BOUNDS" << endl;
		}	
		
	}
	return frame;
}

