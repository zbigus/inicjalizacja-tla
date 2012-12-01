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
#include "blok.h"
using namespace cv;
using namespace std;
class grid
{
public:
	std::vector<std::vector<blok>> content;
	int height,width;
public:
	void dump();
	grid(int , int );
	//blok(Mat** input_block, int _size);
	std::vector<blok>& operator()(int, int);
	void insertAt(int,int, blok&);
	int getWidth();
	int getHeight();
	void setHeight(int);
	void setWidth(int);
	void reserve(int);
	void fix();
};