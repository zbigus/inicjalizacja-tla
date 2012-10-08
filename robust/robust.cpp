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
#include "blok.h"
using namespace cv;
using namespace std;

//typedef deque<Mat> Matqueue;

Mat color;
Mat gray;
VideoCapture vcap;
int movie_width;
int movie_height;
//Matqueue** history;



/*Matqueue** createHistory(int height, int width) {
	Matqueue** History = new Matqueue *[height];
	for (int i = 0; i < height; i++)
		History[i] = new Matqueue[width];
	return History;
}*/

int main(int argc, const char** argv) {

	string str_null("null");
	Mat** tmp;

	int size = 10;
	clock_t before = clock();
	int x = 0, y = 0;

	if (argc < 2 || str_null.compare(argv[1]) == 0) {
		vcap.open(0);
		cout << "zrodlo obrazu: kamera wideo" << endl;
	} else {
		stringstream ss;
		ss<<argv[1];

		string filename;
		ss>>filename;
		vcap.open(filename);
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
	cvNamedWindow("inicjalizacja-tla", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("kawalek", CV_WINDOW_AUTOSIZE);
	for(int i=0;i<1000;i++) { //na razie ograniczanmy ilosc przechwyconych ramek
		vcap >> color;
		if (color.empty()) {
			cout << "ERROR: pusta ramka...\n";
			break;
		}
		
				cvtColor(color, gray, CV_BGR2GRAY);
		imshow("inicjalizacja-tla", gray);
		tmp = grid_cut(gray, size);
		// cout << x <<","<<y<<endl;
		blok blk(tmp[y][x],size);
		blk.dump();
		system("PAUSE");
		if(blk.getSize())
		{
		Mat kawalek2=blk.devectorize();
		cout<<kawalek2;
		imshow("kawalek", tmp[y][x]);
		imshow("kawalek2", kawalek2);
		}

		char c = (char) waitKey(10);
		if (c == 27)
			break;
		switch (c) {
		case 'a':
			if (x > 0)
				x--;
			break;
		case 'd':
			if (x + 1 < (movie_width / size))
				x++;
			break;
		case 'w':
			if (y > 0)
				y--;
			break;
		case 's':
			if (y + 1 < (movie_height / size))
				y++;
			break;
		default:
			break;
		}
	}
	cvDestroyWindow("mywindow");
	clock_t after = clock();

	cout << endl << "czas[ms]" << after - before << endl;
	return 0;

	return 0;
}
