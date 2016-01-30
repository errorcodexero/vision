/*
 * VisualUtils.h
 *
 *  Created on: Jan 23, 2016
 *      Author: nick
 */
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <pthread.h>
using namespace cv;
using namespace std;



#ifndef VISUALUTILS_H_
#define VISUALUTILS_H_
template <class T>
int approx(T input, T range) {
 if (input <= (input + range) && input >= (input - range))
     return 0;
 else {
     if (!(input <= (input + range)) && input >= (input - range))
         return -1;
     if (input <= (input + range) && !(input >= (input - range)))
         return 1;

 }
}
template <class T>
int approx(Point input, T range) {
 if (input.x <= (input + range) && input.x >= (input - range) && input.y >= (input - range) && input.y >= (input - range))
     return true;
 else
     if (!(input.x <= (input + range) && input.x >= (input - range) && input.y >= (input - range) && input.y >= (input - range)))
         return -1;
     if (input.x <= (input + range) && !(input.x >= (input - range)) && input.y >= (input - range) && input.y >= (input - range))
         return 1;
     if (!(input.y <= (input + range) && input.y >= (input - range) && input.x >= (input - range) && input.x >= (input - range)))
         return -2;
     if (input.y <= (input + range) && !(input.y >= (input - range)) && input.x >= (input - range) && input.x >= (input - range))
         return 2;
 }

int getProxToPoint(cv::Point loc, Mat Frame) {
    Size imgSize = Frame.size();
    return abs(loc.x - ((imgSize.width / 2)));

}

void getLeftRight(Mat & Frame, double scale, Scalar color, int thickness, string text, vector< cv::Rect > boundRects);

bool drawReticle (cv::Mat & InFrame, int Size, Point Loc, Scalar Color) {
Point MinX (((Loc.x - 18 * (Size) - 12)), Loc.y);
Point MaxX (((Loc.x + 18 * (Size) + 12)), Loc.y);
Point MinY (Loc.x, ((Loc.y - (18 * Size)) - 12));
Point MaxY (Loc.x, ((Loc.y + (18 * Size)) + 12));

cv::circle(InFrame, Loc, (36 * (Size / 2)), Color, Size, 8, 0);
cv::circle(InFrame, Loc, (36 * Size), Color, Size, 8, 0);

cv::line(InFrame, MinX, MaxX, Color, Size, 8, 0);
cv::line(InFrame, MinY, MaxY, Color, Size, 8, 0);
return true;
}

/*template <class T>
T operator^(T number, T power) {
	T val;
	T currPower = number;
	for (auto i = 0; i <= power; i++) {
		currPower *= number;
	}
	val = currPower;
	return val;

}*/

vector<vector<Point> > edgeDetect(Mat input, Scalar color, Mat & output) {
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
findContours( input, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
int idx = 0;
if (idx > hierarchy.size())
{
for ( ; idx >= 0; idx = hierarchy[idx][0]) {

	drawContours( output, contours, idx, color, CV_FILLED, 8, hierarchy);
	}
}
return contours;
}

vector <Rect > ShowTargets(vector <vector < Point> > contours, Mat Frame) {
vector<vector <Point > > contours_poly( contours.size());
vector<Rect > boundRect( contours.size());
vector <Point2f>center(contours.size());
vector <float> radius(contours.size());
for (int i = 0; i < contours.size(); i++) {
approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true);
boundRect[i] = boundingRect( Mat (contours_poly[i]));
}
for (int i = 0; i < contours.size(); i++) {
Scalar color (255, 0, 0);
rectangle (Frame, boundRect[i].tl(),boundRect[i].br(), color, 2, 8, 0);
Point p1 = boundRect[i].tl();
Point p2 = boundRect[i].br();
Point center = Point(((p1.x + p2.x)/2), ((p1.y + p2.y)/2));
drawReticle(Frame, 2, center, Scalar(0,0,255));
}
return boundRect;
}
void Threshold(Mat & ThreshMat, Mat HSVMin, Mat HSVMax, Mat Frame) {
	inRange(Frame, HSVMin, HSVMax, ThreshMat);
}

void inline getLeftRight(Mat & Frame, double scale, Scalar color, int thickness, vector <Rect > boundRects) {
   bool isWithinMargin = false;
   cv::Point point;
   int dist;

    for (int i; i <= boundRects.size(); i++) {
        cv::Point p1 = boundRects[i].tl();
        cv::Point p2 = boundRects[i].br();

        cv::Point center = Point(((p1.x + p2.x)/2), ((p1.y + p2.y)/2));
        dist = getProxToPoint(center, Frame);
        if (approx(dist, 10) == 0) {
            isWithinMargin = true;
        }
        else if (approx(dist, 10) == 1) {
            point = cv::Point((p1.x +10), (p1.y +10));
            isWithinMargin = false;
             putText(Frame, "Left", point, FONT_HERSHEY_SIMPLEX, scale, color, thickness, 8, false);

    }
        else if (approx(dist, 10) == -1) {
            point = cv::Point((p1.x +10), (p1.y +10));
            isWithinMargin = false;
             putText(Frame, "Right", point, FONT_HERSHEY_SIMPLEX, scale, color, thickness, 8, false);;


    }
        if (isWithinMargin) {
            point = Point((p1.x + 10), (p1.y + 10));
             putText(Frame, "Centered", point, FONT_HERSHEY_SIMPLEX, scale, color, thickness, 8, false);
        }

}
}


#endif /* VISUALUTILS_H_ */
