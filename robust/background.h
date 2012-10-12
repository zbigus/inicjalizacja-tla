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
public:
	background();
	background(int,int);
	Mat & devectorize();
	blok & operator()(int, int);
	void insertAt(int, int,blok&);

};