#include "opencv2/video/tracking.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <dos.h>
#include <iostream>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <iomanip>
#include <deque>
#include <math.h>
#include "alpha.h"
#include "cachedMethods.h"
using namespace cv;
using namespace std;

//typedef deque<Mat> Matqueue;

Mat color;
Mat gray;
Mat bg;
VideoCapture vcap;
int movie_width;
int movie_height;
int grid_width;
int grid_height;
bool init=true;
double T1=0.8;
double T2=10;
int size = 12;


int main(int argc, const char** argv) {
	int method = 0;
	string str_null("null");
	Mat** tmp;

	clock_t before = clock();
	int x = 0, y = 0;

	if (argc < 2 || str_null.compare(argv[1]) == 0) {
		vcap.open(0);
		cout << "zrodlo obrazu: kamera wideo" << endl;
	} else {
		//string filename = (LPCTSTR) argv[1];
		vcap.open(argv[1]);
		cout << "zrodlo obrazu: " << argv[1] << endl;
	}
	if (!vcap.isOpened()) {
		cout << "blad - nie mozna odczytac obrazu z podanego zrodla\n";
		return -1;
	}
	movie_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	movie_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "szerokosc filmu: " << movie_width << "px\twysokosc filmu: "
		<< movie_height << "px" << endl;

	int klatka=0;

		const string win1 = "window 1 - obraz z kamery";
		string win2 = "window2";
		string win3 = "window3";

		
		Mat img,fgmask, fgimg;
		cachedMethods cached;
		alpha alphaMethod = alpha(0.95);
		while (1) {
			klatka++;
			vcap >> img;
			if( img.empty() )
				break;
			cvtColor(img, gray, CV_BGR2GRAY);

			if( fgimg.empty() )
				fgimg.create(img.size(), img.type());

			cached.processMean(gray,bg);
			//alphaMethod.process(gray,bg);
			//img.copyTo(background, background);


			imshow("window 1 - obraz z kamery", img);
			imshow("window 2 - szary obraz", gray);
			imshow("window 3 - tlo", bg);
			imshow("window 4 - roznica", abs(gray-bg));


			char k = (char)waitKey(10);
			//cout << "img: " << img.size <<endl;
			//cout << "gray: " << img.size <<endl;
			//cout << "bg: " << img.size <<endl;
		}

	char wynik_char=(char) waitKey(10);
	system("PAUSE");	
	clock_t after = clock();

	cout << endl << "czas[ms]" << after - before << endl;
	return 0;

	return 0;
}
