#include "alpha.h"

alpha::alpha(double param){ 
	alphaParam = param;
	firstTime = true;
}

int alpha::getWidth(){
	return width;
}
int alpha::getHeight(){
	return height;
}

void alpha::process(const cv::Mat &img_input, cv::Mat &img_output)
{
  if(img_input.empty())
    return;
  img = Mat(img_input);
  if(firstTime)
  {
    int width = img_input.size().width;
    int height = img_input.size().height;
	img.copyTo(background);
	//background = Scalar::all(0);
  }
  
  addWeighted(background, alphaParam, img, 1-alphaParam, 0.0, background);

  background.copyTo(img_output);
  firstTime = false;
}

double alpha::getAplha(){
	return alphaParam;
}

void alpha::setAplha(double al){
	if(al>0 && al <1){
		alphaParam = al;
	}
}
