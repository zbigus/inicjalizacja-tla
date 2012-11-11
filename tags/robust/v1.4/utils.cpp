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
#include "utils.h"
using namespace cv;
using namespace std;

Mat** grid_cut(Mat input_image, int size) {
	int height = (int) input_image.rows / size;
	int width = (int) input_image.cols / size;
	Mat** Container = new Mat *[height];
	for (int i = 0; i < height; i++)
		Container[i] = new Mat[width];
	Rect roi;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			roi = Rect(j * size, i * size, size, size);
			Mat tmp_mat = Mat(input_image, roi);
			Container[i][j] = tmp_mat;
		}
	}

	return Container;
}
double cost(Mat C, Mat D,int size, double alpha, int weight){
	float suma=0;
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			suma+=abs(C.at<float>(j,i)+D.at<float>(j,i));
	suma*=exp(-alpha*weight);
	return suma;
}