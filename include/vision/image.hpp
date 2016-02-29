#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

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


extern std::vector <float > fGetAngle(std::vector<cv::Rect >, float _fFOV, float _fMidLine);

extern void showLeftRight(cv::Mat & _mFrame, double _dScale );

#endif /*_IMAGE_HPP_*/
