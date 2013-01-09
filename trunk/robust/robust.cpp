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
#include "utils.h"
#include "blok.h"
#include "grid.h"
#include "background.h"
#include "robust.h"
using namespace cv;
using namespace std;

int framesize; 
bool changedsomething;

//typedef deque<Mat> Matqueue;
string str_m0("1");
Mat color;
Mat gray;
Mat save_img;
VideoCapture vcap;
int movie_width;
int movie_height;
int grid_width;
int grid_height;
int ileklatek;
grid grd(0,0);
char filename[100];
background bg(0,0);
bool init=true;
double T1=0.8;
double T2=10;
int size = 16;
bool dctmethod=false;
stringstream filename_img;
//Matqueue** history;



/*Matqueue** createHistory(int height, int width) {
	Matqueue** History = new Matqueue *[height];
	for (int i = 0; i < height; i++)
		History[i] = new Matqueue[width];
	return History;
}*/

int main(int argc, const char** argv) {
	int method = 0;
	ileklatek=50;
	string str_null("null");
	Mat** tmp;
			if (argc > 2 ) {
				
				ileklatek=atoi(argv[2]);
				}
			if(argc>3){
				if(atoi(argv[3]) ==0)
					{
						dctmethod=false;
						method=1;
					}
				else if(atoi(argv[3]) ==1)
				{
					dctmethod=true;
					method=0;
				}
				else
				{
					dctmethod=false;
					method=0;
				}
			}
			if(argc>4){
					size=atoi(argv[4]);
			}
			if (argc > 5 ) {
				double inputT1 = strtod(argv[5], NULL);
				if(inputT1>0 && inputT1<1)
					T1 = inputT1;
			}if (argc > 6 ) {
				double inputT2 = strtod(argv[6], NULL);
				T2 = inputT2;
			}
		
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
	framesize=size;
	switch(method){


	case 0:
		//cvNamedWindow("inicjalizacja-tla", CV_WINDOW_AUTOSIZE);
		//cvNamedWindow("kawalek", CV_WINDOW_AUTOSIZE);
		//cvNamedWindow("kolor", CV_WINDOW_AUTOSIZE);
		while (1) {
			klatka++;
			if(ileklatek >1 && klatka==ileklatek)
				break;
			cout<<"Obrobka klatki nr: "<<klatka<<endl;
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
						bg.allocate();
						cout<<grd.getWidth()<<" "<<grd.getHeight();
						//system("PAUSE");
						init=false;
					}
				
			//imshow("kolor",color);
			//imshow("inicjalizacja-tla", gray);
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
							//cout<<it->getWeight();
						
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
		//ETAP 2 
		grd.fix();
		for(int i=0;i<::grid_height;i++)
		{	
			cout<<endl;
			for (int j=0;j<::grid_width;j++)
			{
				cout<<grd(i,j).size()<<","<<grd(i,j).at(0).getWeight()<<" ";
				Mat tmp=grd(i,j).at(0).devectorize();
				cvNamedWindow("test");
				imshow("test",tmp);
				char cdd=(char) waitKey(10);
				//system("PAUSE");
				if(grd(i,j).size()==1)
				{
					bg.insertAt(i,j,grd(i,j).at(0)); //testowe,moze krzaczyc
					cout<<bg.getFilled()<<endl;
				}
				else
				{
					Mat zeromat=Mat(size,size,CV_8UC1,Scalar(0));
					bg.insertBlack(i,j,blok(zeromat,size));
				}
			}
		}
		cvNamedWindow("wynik");
		imshow("wynik",bg.devectorize()); //jeszcze nie dziala
		waitKey(10);
//ETAP 3
		changedsomething=true;
		while(changedsomething && !bg.isComplete() ){
			changedsomething=false;
			for(int i=0;i<::grid_height-1;i++)
				for(int j=0;j<::grid_width-1;j++)
				{
					if(bg.isFilled(i,j)+bg.isFilled(i+1,j)+bg.isFilled(i,j+1)+bg.isFilled(i+1,j+1)==3){
					blok lewygora=bg(i,j);
					blok prawygora=bg(i+1,j);
					blok lewydol=bg(i,j+1);
					blok prawydol=bg(i+1,j+1);
					int nrzero;
					int a,b;
					if(!bg.isFilled(i,j))
					{
						nrzero=0;
						a=i;
						b=j;
					}
					else if(!bg.isFilled(i+1,j))
					{
						nrzero=1;
						a=i+1;
						b=j;
					}
					else if(!bg.isFilled(i,j+1))
					{
						nrzero=2;
						a=i;
						b=j+1;
					}
					else
					{
						nrzero=3;
						a=i+1;
						b=j+1;
					}
					int bloksize=size;
					Mat * superblok=new Mat(bloksize*2,bloksize*2,CV_8UC1,Scalar(0));
					Mat *C =new Mat(bloksize*2,bloksize*2,CV_32FC1,Scalar(0));
					Mat *D =new Mat(bloksize*2,bloksize*2,CV_32FC1,Scalar(0));
					if(nrzero!=0)
						lewygora.devectorize().copyTo((*superblok)(Rect(0, 0, bloksize, bloksize)));
					if(nrzero!=1)
						prawygora.devectorize().copyTo((*superblok)(Rect(bloksize, 0, bloksize, bloksize)));
					if(nrzero!=2)
						lewydol.devectorize().copyTo((*superblok)(Rect(0, bloksize, bloksize, bloksize)));
					if(nrzero!=3)
						prawydol.devectorize().copyTo((*superblok)(Rect(bloksize, bloksize, bloksize, bloksize)));
					Mat superblokf;
					superblok->convertTo(superblokf,CV_32FC1);
					if(dctmethod==true)
					cv::dct(superblokf,*C,0);
					else
					*C=hadamard(superblokf);
					int nrnajlepszegobloku=0;
					double kosztnajlepszegobloku=0;
					bool poczatekobliczen=true;
					Mat * superblok2;
					
					for(unsigned int ind=0;ind<grd(a,b).size();ind++)
					{
						blok tmp=grd(a,b).at(ind);
						if(tmp.mean()>128)
							superblok2=new Mat(bloksize*2,bloksize*2,CV_8UC1,Scalar(0));
						else
							superblok2=new Mat(bloksize*2,bloksize*2,CV_8UC1,Scalar(255));
						if(nrzero==0)
							tmp.devectorize().copyTo((*superblok2)(Rect(0, 0, bloksize, bloksize)));
						else if(nrzero==1)
							tmp.devectorize().copyTo((*superblok2)(Rect(size, 0, bloksize, bloksize)));
						else if(nrzero==2)
							tmp.devectorize().copyTo((*superblok2)(Rect(0, size, bloksize, bloksize)));
						else
							tmp.devectorize().copyTo((*superblok2)(Rect(size, size, bloksize, bloksize)));
						Mat superblok2f;
						superblok2->convertTo(superblok2f,CV_32FC1);
						if(dctmethod==true)
						cv::dct(superblok2f,*D,0);
						else
						*D=hadamard(superblok2f);
						double koszt=cost(*C,*D,bloksize,1,tmp.getWeight());
						if(poczatekobliczen==true || koszt<kosztnajlepszegobloku)
						{
							kosztnajlepszegobloku=koszt;
							nrnajlepszegobloku=ind;
							poczatekobliczen=false;
						}
					}
					bg.rep(a,b,grd(a,b).at(nrnajlepszegobloku));
					changedsomething=true;
					cout<<"Uzupe³niono "<<bg.getFilled()<<"\\"<<grd.getHeight()*grd.getWidth()<<endl;
					cvNamedWindow("wyniktest");
					imshow("wyniktest",bg.devectorize()); //jeszcze nie dziala
					waitKey(10);
					system("PAUSE");
				}
			}
		}
		cvNamedWindow("wynik2");
		imshow("wynik2",bg.devectorize());
		
		bg.devectorize().convertTo(save_img,CV_8U);
		_splitpath(argv[1],NULL,NULL,filename,NULL);
		filename_img << filename<<"_"<<(dctmethod==true?"dct_":"had_") << ileklatek<<"_"<< T1 << "_"<<T2 << ".png";
		cout << filename_img.str() <<endl;
		imwrite( filename_img.str(), save_img );
		break;

	case 1:

		namedWindow("kolor", CV_WINDOW_NORMAL);
		namedWindow("maska pierwszego planu", CV_WINDOW_NORMAL);
		namedWindow("pierwszy plan", CV_WINDOW_NORMAL);
		
		BackgroundSubtractorMOG2 bg_model;//(100, 3, 0.3, 5);

		Mat img,fgmask, fgimg;

		while (1) {
			klatka++;
			//if(klatka==100)
				//break;

			//nie dzia³a dla szarego obrazu
			vcap >> img;
			if( img.empty() )
				break;

			if( fgimg.empty() )
				fgimg.create(img.size(), img.type());

			//aktualizacja modelu
			bg_model(img, fgmask, -1);

			//zerowanie obrazka pierwszego planu
			fgimg = Scalar::all(0);
			img.copyTo(fgimg, fgmask);

			Mat bgimg;
			bg_model.getBackgroundImage(bgimg);

			imshow("kolor", img);
			imshow("maska pierwszego planu", fgmask);
			imshow("pierwszy plan", fgimg);
			if(!bgimg.empty())
				imshow("mean background image", bgimg );

			char k = (char)waitKey(10);

		}

		namedWindow("wynik", CV_WINDOW_NORMAL);
		Mat bgimg;
		bg_model.getBackgroundImage(bgimg);
		if(!bgimg.empty())
			imshow("wynik", bgimg );
		break;

	}

	char wynik_char=(char) waitKey(10);
	
	system("PAUSE");	
	clock_t after = clock();

	cout << endl << "czas[ms]" << after - before << endl;
	return 0;

	return 0;
}
