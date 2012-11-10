#include "background.h"
background::background(){}
background::background(int _width, int _height){
	width=_width;
	height=_height;
	nrfilled=0;
	content=new vector<blok>(width*height);
		   }
blok& background::operator()(int x, int y)
{
return content->at(y+x*width);
}
void background::insertAt(int x,int y, blok & blk){
	vector<blok>::iterator it;

	it = content->begin();
	for(int i=0;i<x*width+y;i++)
		++it;
	content->insert(it,blk);
	nrfilled++;
	filltable[x][y]=true;
}
void background::insertBlack(int x,int y, blok & blk){
	vector<blok>::iterator it;

	it = content->begin();
	for(int i=0;i<x*width+y;i++)
		++it;
	content->insert(it,blk);
}
Mat & background::devectorize(){
	Mat *tmp=new Mat(height*content->at(0).getSqrtSize(),width*content->at(0).getSqrtSize(),CV_8UC1,Scalar(0));
	//cout<<content->at(0).getSize();
	//cout<<"POJ:"<<content->capacity();
	//cout<<width*height;
	//for(unsigned int a=0;a<width*height;a++)
	vector<blok>::iterator it=content->begin();
		int size=content->at(0).getSqrtSize();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			
			if(it->getSize())
			it->devectorize().copyTo((*tmp)(Rect(j*size, i*size, size, size)));
			it++;
			}
		
	}
		//for(int i=0;i<content->at(0).getSqrtSize();i++)
			//for(int j=0;j<content->at(0).getSqrtSize();j++)
				//tmp->at<uchar>(i+a/width*content->at(0).getSqrtSize(),j+a%width)=content->at(a).devectorize().at<uchar>(i,j);
return *tmp;
}
void background::reserve(int n){
	*content=vector<blok>(n);
}
void background::setWidth(int _width){
	width=_width;
}
void background::setHeight(int _height){
	height=_height;
}
bool background::isComplete(){
	if(width*height==nrfilled)
		return true;
	else return false;
}
void background::allocate(){
	filltable=new int*[height];
	for(int i=0;i<height;i++)
		filltable[i]=new int[width];
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			filltable[i][j]=0;
}
int background::isFilled(int x,int y){
	return filltable[x][y];
}