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
class background{
private:
	std::vector<blok>* content;
	int width, height;
	int nrfilled;
	int **filltable;
public:
	background();
	background(int,int);
	Mat & devectorize();
	blok & operator()(int, int);
	void insertAt(int, int,blok&);
	void rep(int, int,blok&);
	void insertBlack(int, int,blok&);
	void reserve(int);
	void setWidth(int);
	void setHeight(int);
	bool isComplete();
	void allocate();
	int isFilled(int x,int y);
	int getFilled();
};