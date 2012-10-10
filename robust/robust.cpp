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
#include "grid.h"
using namespace cv;
using namespace std;

//typedef deque<Mat> Matqueue;

Mat color;
Mat gray;
VideoCapture vcap;
int movie_width;
int movie_height;
int grid_width;
int grid_height;
grid grd(0,0);
bool init=1;
double T1=0.8;
double T2=0.2;
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

	int size = 5;
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
	while(true) { //na razie ograniczanmy ilosc przechwyconych ramek
		vcap >> color;
		if (color.empty()) {
			cout << "pusta ramka...\n";
			break;
		}
		
				cvtColor(color, gray, CV_BGR2GRAY);
				if(init)
				{
					::grid_height = (int) gray.rows / size;
					::grid_width = (int) gray.cols / size;
					grd.setHeight(grid_height);
					grd.setWidth(grid_width);
					grd.reserve(grid_height*grid_width);
					cout<<grd.getWidth()<<" "<<grd.getHeight();
					system("PAUSE");
				}
				
		imshow("inicjalizacja-tla", gray);
		tmp = grid_cut(gray, size);
		for(int i=0;i<::grid_width;i++)
			for (int j=0;j<::grid_height;j++)
			{	
				bool flaga=false;
				std::vector<blok> wektor=grd(i,j);
				vector<blok>::iterator it;
				for(it=wektor.begin();it<wektor.end();it++)
				{
					if(it->similar(tmp[i][j],T1,T2))
					{
						flaga=true;

					}

				}
			}
		// cout << x <<","<<y<<endl;
/*		blok blk(tmp[y][x],size);
		if(blk.getSize())
		{
		Mat kawalek2=blk.devectorize();
		cout<<kawalek2;
		imshow("kawalek", tmp[y][x]);
		imshow("kawalek2", kawalek2);
		}
		grd.insertAt(2,3,blk);
		cout<<"size:"<<grd(3,2).at(0).getSize();
		if(grd(3,2).at(0).getSize())
			{
				blok blk4=grd(3,2).at(0);
				imshow("kawalek4",blk4.devectorize());
				cout<<"corr:";
				cout<<blk.corelation(blk4)<<endl;
				cout<<"mad:"<<blk.mad(blk4);
			}*/
/*		char c = (char) waitKey(10);
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
		}*/
	}
	cvDestroyWindow("mywindow");
	clock_t after = clock();

	cout << endl << "czas[ms]" << after - before << endl;
	return 0;

	return 0;
}
