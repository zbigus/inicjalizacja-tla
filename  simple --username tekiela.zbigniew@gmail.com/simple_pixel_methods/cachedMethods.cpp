#include "cachedMethods.h"

cachedMethods::cachedMethods(int param){ 
	cacheSize = 50;
	firstTime = true;
}

cachedMethods::cachedMethods(){ 
	cacheSize = 50;
	firstTime = true;
}

int cachedMethods::getWidth(){
	return width;
}

int cachedMethods::getHeight(){
	return height;
}



void cachedMethods::processMean(const cv::Mat &img_input, cv::Mat &img_output)
{
	
  if(img_input.empty())
    return;
  //img = Mat(img_input);
  img_input.copyTo(img);
  if(firstTime)
  {
	frameCount = 0;
	width = img_input.size().width;
	height = img_input.size().height;
	zeromat=Mat(height,width,CV_8UC1,Scalar(0));
	//grd.reserve(20);
	for(int i=0;i<cacheSize;i++)
		grd.push_back(zeromat);
  }
  

 /*vector<Mat>::iterator it= grd.begin();
  for(int i=0;i<frameCount%cacheSize;i++)
	  ++it;

  cout<<"";
  grd.erase(it);
  grd.insert(it,img);*/
  grd.erase(grd.begin());
  grd.push_back(img);
  
  frameCount++;
 
  
	  

  
  if(false && frameCount<cacheSize){
	  zeromat.copyTo(img_output);
  }
  else{
			tmp=Mat(height,width,CV_32F,Scalar(0));		
		  vector<Mat>::iterator it;
		  for(it=grd.begin();it!=grd.end();it++){
			  Mat tmp2=Mat(height,width,CV_32F,Scalar(0));
			  it->convertTo(tmp2,CV_32F,1./255.);
			  tmp+=tmp2;
		  }
  Mat tmp3=Mat(height,width,CV_8UC1,Scalar(0));
  tmp=tmp/cacheSize;
  tmp.convertTo(tmp3,CV_8UC1,255.0);
//		 bg=tmp/20;
  tmp3.copyTo(img_output);
  }
  firstTime = false;
}


unsigned int cachedMethods::mean(vector<unsigned int> vals)
{
  size_t size = vals.size();

  double total = std::accumulate(vals.begin(), vals.end(), 0);
  double mean = total / size;

  return (unsigned int)mean;
}

unsigned int cachedMethods::median(vector<unsigned int> vals)
{
  double median;
  size_t size = vals.size();

  sort(vals.begin(), vals.end());
  if(size>1){
	  if (size  % 2 == 0)
	  {
		  median = (vals[size / 2 - 1] + vals[size / 2]) / 2;
	  }
	  else 
	  {
		  median = vals[size / 2];
	  }
  }else{
	  median = vals[0];
  }

  return (unsigned int)median;
}



/*
deque<double> cachedMethods::At(int x,int y)
{
	vector<vector<deque<double>>>::iterator it;
	it = cache.begin();
	for(int i=0;i<y*width+x;i++)
		++it;
	return it;
	//content.insert ( it , y*width+x,blk );
}
*/