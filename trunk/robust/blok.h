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
	blok();
	//blok(Mat** input_block, int _size);
	int operator()(int, int);
	blok operator-(int);
	void operator+(blok &blk);
	void operator*(double);
	Mat& devectorize();
	int getSize();
	int getSqrtSize();
	double mean();
	double deviation();
	double corelation(blok &blk);
	double mad(blok &blk);
	boolean similar(blok &blk, double,double);
	void setWeight(double);
	double getWeight();
	void update(blok& );
};