#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/gpu/gpu.hpp>

template <class T >
T getMin( std::vector< T>);
template <class T >
T getMax( std::vector< T>);
template <class T>
int approx(T input, T target, T range);
#endif /*_MATH_HPP_*/
