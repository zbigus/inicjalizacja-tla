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
#include "background.h"
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
background bg(0,0);
bool init=true;
double T1=0.8;
double T2=100;
int size = 24;
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
	cvNamedWindow("inicjalizacja-tla", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("kawalek", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("kolor", CV_WINDOW_AUTOSIZE);
	int klatka=0;
	while (1) {
		klatka++;
		if(klatka==15)
			break;
		vcap >> color;
		if (color.empty()) {
			cout << "ERROR: pusta ramka...\n";
			break;
		} //na razie ograniczanmy ilosc przechwyconych ramek
   		//cout<<nrramki<<endl;
		//nrramki++;
		//if(nrramki%100!=0)
		//{continue;}
	//	system("Pause");
				cvtColor(color, gray, CV_BGR2GRAY);
				if(init)
				{
					::grid_height = (int) gray.rows / size;
					::grid_width = (int) gray.cols / size;
					grd.setHeight(grid_height);
					grd.setWidth(grid_width);
					grd.reserve(grid_height*grid_width);
					bg.setHeight(grid_height);
					bg.setWidth(grid_width);
					bg.reserve(grid_height*grid_width);
					cout<<grd.getWidth()<<" "<<grd.getHeight();
					system("PAUSE");
					init=false;
				}
				
		imshow("kolor",color);
		imshow("inicjalizacja-tla", gray);
		char cc = (char) waitKey(10);
		tmp = grid_cut(gray, size);
		for(int i=0;i<::grid_width;i++)
			for (int j=0;j<::grid_height;j++)
			{	
				bool flaga=false;
				vector<blok> wektor=grd(j,i);
				vector<blok>::iterator it;
				blok b=blok(tmp[j][i],size);
				//imshow("kawalek",b.devectorize());
				//char kawalek_char=(char) waitKey(10);
				for(it=grd(j,i).begin();it!=grd(j,i).end();it++)
				{
					//cout<<i<<","<<j<<"przed sim";
					//system("PAUSE");
					if(it->similar(b,T1,T2))
					{
						flaga=true;
						it->update(b);
						//cout<<"similar!";
						cout<<it->getWeight();
						
					}

				}
				if(flaga==false){
					blok c(tmp[j][i],size);
					grd.insertAt(i,j,(blok(tmp[j][i],size)));
				}
			}
		// cout << x <<","<<y<<endl;*/
		//blok blk(tmp[y][x],size);
	/*	if(blk.getSize())
		{
		Mat kawalek2=blk.devectorize();
		cout<<kawalek2;
		imshow("kawalek", tmp[y][x]);
		imshow("kawalek2", kawalek2);
		}*/
		/*
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
		
		//if (cc == 27)
			//break;
		
	}

	grd.fix();
	for(int i=0;i<::grid_width;i++)
	{	
		cout<<endl;
		for (int j=0;j<::grid_height;j++)
		{
			cout<<grd(j,i).size()<<","<<grd(j,i).at(0).getWeight()<<" ";
			Mat tmp=grd(j,i).at(0).devectorize();
			cvNamedWindow("test");
			imshow("test",tmp);
			char cdd=(char) waitKey(10);
			//system("PAUSE");
			bg.insertAt(j,i,grd(j,i).at(0)); //testowe,moze krzaczyc
		}
	}
	cvNamedWindow("wynik");
	imshow("wynik",bg.devectorize()); //jeszcze nie dziala
	system("PAUSE");	
	clock_t after = clock();

	cout << endl << "czas[ms]" << after - before << endl;
	return 0;

	return 0;
}
