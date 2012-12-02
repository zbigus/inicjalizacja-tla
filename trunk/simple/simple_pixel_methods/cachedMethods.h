#pragma once

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <iostream>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <iomanip>
#include <deque>
#include <math.h>
#include <algorithm>
#include <numeric>
#include "background.h"

using namespace cv;
using namespace std;
class cachedMethods
{
public:
	bool firstTime;
	int cacheSize;
	int frameCount;
	int height,width;
	vector<Mat> grd;
	Mat img;
	vector<vector<vector<double>>> cache;
	Mat bg;
	Mat tmp;
	Mat zeromat;
public:
	cachedMethods(int);
	cachedMethods();
	void processMean(const cv::Mat &img_input, cv::Mat &img_output);
	void dump();
	int getWidth();
	int getHeight();
	void pushAt(int,int,double);
	unsigned int median(std::vector<unsigned int>);
	unsigned int mean(std::vector<unsigned int>);
};