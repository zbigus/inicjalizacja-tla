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

using namespace cv;
using namespace std;
class alpha
{
public:
	bool firstTime;
	double alphaParam;
	int height,width;
	Mat img;
	Mat last;
	Mat background;
public:
	alpha(double);
	void process(const cv::Mat &img_input, cv::Mat &img_output);
	void dump();
	int getWidth();
	int getHeight();
};