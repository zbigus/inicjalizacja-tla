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
class blok
{
private:
	std::vector<unsigned int> content;
	double weight;
	int size;
public:
	void dump();
	blok(Mat , int );
	//blok(Mat** input_block, int _size);
	int operator()(int, int);
	Mat& devectorize();
	int getSize();
};