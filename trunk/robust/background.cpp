#include "background.h"
background::background(){}
background::background(int _width, int _height){
	width=_width;
	height=_height;
	content=new vector<blok>(width*height);
		   }
blok& background::operator()(int x, int y)
{
return content->at(x+y*width);
}
void background::insertAt(int x,int y, blok & blk){
	vector<blok>::iterator it;

	it = content->begin();
	for(int i=0;i<y*width+x;i++)
		++it;
	content->insert(it,blk);
}
Mat & background::devectorize(){
	Mat *tmp=new Mat(width*content->at(0).getSize(),height*content->at(0).getSize(),CV_8UC1);
	for(unsigned int a=0;a<content->size();a++)	
	for(int i=0;i<content->at(0).getSize();i++)
			for(int j=0;j<content->at(0).getSize();j++)
				tmp->at<cv::Vec2d>((j+a*content->at(0).getSize())%width,i+a*content->at(0).getSize())=content->at(a).devectorize().at<cv::Vec2d>(j,i);
return *tmp;
}
