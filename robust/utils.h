#ifndef ADD_H
#define ADD_H
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <iomanip>
#include <deque>
#include <math.h>
using namespace cv;
using namespace std;

Mat** grid_cut(Mat input_image, int size);
double cost(Mat C, Mat D,int size, double alpha, int weight);
Mat hadamardmat(int size);
Mat hadamard(Mat);
#endif