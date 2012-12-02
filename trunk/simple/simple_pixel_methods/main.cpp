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
#include "movingMean.h"
using namespace cv;
using namespace std;


Mat color;
Mat gray;
Mat bg;
VideoCapture vcap;
int movie_width;
int movie_height;
bool init=true;
int size = 12;
int method =0;
double alphaparam =0.95;


int main(int argc, const char** argv) {
	int method = 0;
	string str_null("null");
	string str_m0("0");

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

	if (argc > 2 ) {
		cout << argv[2] << endl;
		if(str_m0.compare(argv[2]) == 0){
			method=0;
			if (argc > 3 ) {
				double inputalpha = strtod(argv[3], NULL);
				if(inputalpha>0 && inputalpha<1)
					alphaparam = inputalpha;
			}
		}else{
			method=1;
		}
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
		//cachedMethods cached;
		alpha alphaMethod = alpha(alphaparam);
		movingMean meanbg = movingMean();
		while (1) {
			klatka++;
			vcap >> img;
			if( img.empty() )
				break;
			cvtColor(img, gray, CV_BGR2GRAY);

			if( fgimg.empty() )
				fgimg.create(img.size(), img.type());

			//cached.processMean(gray,bg);
			switch(method){
			case 0:
				alphaMethod.process(gray,bg);
				break;
			case 1:
				meanbg.process(gray,bg);
				break;
			}		

			imshow("window 1 - obraz z kamery", img);
			imshow("window 2 - szary obraz", gray);
			imshow("window 3 - tlo", bg);
			imshow("window 4 - roznica", abs(gray-bg));


			char k = (char)waitKey(10);
			if(k=='q')break;
			if(method==0 && (k=='='||k=='+')){
				alphaMethod.setAplha(alphaMethod.getAplha()+0.01);
				cout << "alpha: " << alphaMethod.getAplha() << endl;
			}
			if(method==0 && (k=='-'||k=='_')){
				alphaMethod.setAplha(alphaMethod.getAplha()-0.01);
				cout << "alpha: " << alphaMethod.getAplha() << endl;
			}

			if(k=='m'){
				method++;
				method=method%2;
				cout << method <<endl;
				if(method==0){
					cout << "Alpha" <<endl;
				}
				if(method==1){
					cout << "Srednia" <<endl;
				}
			}

			if(k=='s')
			{
				Mat save_img;
				img.convertTo(save_img,CV_8U);
				Mat save_gray;
				img.convertTo(save_gray,CV_8U);
				Mat save_bg;
				img.convertTo(save_bg,CV_8U);
				stringstream filename_img;
				filename_img << "image_" << klatka << ".png";
				cout << filename_img.str() <<endl;
				imwrite( filename_img.str(), save_img );
				stringstream filename_gray;
				filename_gray << "image_" << klatka << ".png";
				cout << filename_gray.str() <<endl;
				imwrite( filename_gray.str(), save_gray );
				stringstream filename_bg;
				filename_bg << "image_" << klatka << ".png";
				cout << filename_bg.str() <<endl;
				imwrite( filename_bg.str(), save_bg );

			}
		}

	char wynik_char=(char) waitKey(10);
	system("PAUSE");	
	clock_t after = clock();

	cout << endl << "czas[ms]" << after - before << endl;
	return 0;

	return 0;
}
