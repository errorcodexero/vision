#ifndef VISUALUTILS_H_
#define VISUALUTILS_H_

#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>


template <class T>
int approx(T input, T target, T range);

void drawReticle (cv::Mat & InFrame, int Size, cv::Point Loc, cv::Scalar Color);

std::vector<std::vector<cv::Point> > edgeDetect(cv::Mat input, cv::Scalar color, cv::Mat & output);

std::vector <cv::Rect > ShowTargets(const std::vector <std::vector < cv::Point> > &contours, cv::Mat Frame);

void Threshold(cv::Mat & ThreshMat, cv::Mat HSVMin, cv::Mat HSVMax, cv::Mat Frame);

int getProxToPoint (cv::Point pt1, cv::Mat Frame);

cv::Point getMean(cv::Point pt1, cv::Point pt2);

float fGetAnglefromPixel ( float _fMidLine, int _iFOV, float _fX);

cv::Mat getLeftRight(cv::Mat Frame, double scale, int range, cv::Scalar color, int thickness, std::vector <cv::Rect > boundRects);

#endif /* VISUALUTILS_H_ */
