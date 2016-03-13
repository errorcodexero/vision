#ifndef _UTILS_H_
#define _UTILS_H_

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

std::vector <char* > vszParseString(char * _szString, char * _szDilimiter);

bool bIsStringIP(char * _szString);


//Declare some more types
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef unsigned long long qword;

typedef short BYTE;
typedef long WORD;
typedef long long DWORD;

typedef unsigned short uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

typedef short int8;
typedef int int16;
typedef long int32;


//Done with types
#endif /* _UTILS_H_*/
