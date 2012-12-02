#include "movingMean.h"

movingMean::movingMean() : firstTime(true), enableWeight(true), enableThreshold(true), threshold(15), showOutput(true), showBackground(false)
{
  std::cout << "movingMean()" << std::endl;
}

movingMean::~movingMean()
{
  std::cout << "~movingMean()" << std::endl;
}

void movingMean::process(const cv::Mat &img_input, cv::Mat &img_output)
{

  if(img_input.empty())
    return;

  if(firstTime){
	  licznik=0;
	  
  }
  firstTime = false;
  switch(licznik){
  case 18:
	  img_input_prev_18.copyTo(img_input_prev_19);
  case 17:
	  img_input_prev_17.copyTo(img_input_prev_18);
  case 16:
	  img_input_prev_16.copyTo(img_input_prev_17);
  case 15:
	  img_input_prev_15.copyTo(img_input_prev_16);
  case 14:
	  img_input_prev_14.copyTo(img_input_prev_15);
  case 13:
	  img_input_prev_13.copyTo(img_input_prev_14);
  case 12:
	  img_input_prev_12.copyTo(img_input_prev_13);
  case 11:
	  img_input_prev_11.copyTo(img_input_prev_12);
  case 10:
	  img_input_prev_10.copyTo(img_input_prev_11);
  case 9:
	  img_input_prev_9.copyTo(img_input_prev_10);
  case 8:
	  img_input_prev_8.copyTo(img_input_prev_9);
  case 7:
	  img_input_prev_7.copyTo(img_input_prev_8);
  case 6:
	  img_input_prev_6.copyTo(img_input_prev_7);
  case 5:
	  img_input_prev_5.copyTo(img_input_prev_6);
  case 4:
	  img_input_prev_4.copyTo(img_input_prev_5);
  case 3:
	  img_input_prev_3.copyTo(img_input_prev_4);
  case 2:
	  img_input_prev_2.copyTo(img_input_prev_3);
  case 1:
	  img_input_prev_1.copyTo(img_input_prev_2);
  case 0:
	  img_input.copyTo(img_input_prev_1);
  }
    licznik++;
	
  if(licznik < 20){
	  img_input.copyTo(img_output);
	  return;
  }

  cv::Mat img_input_f(img_input.size(), CV_32F);
  img_input.convertTo(img_input_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_1_f(img_input.size(), CV_32F);
  img_input_prev_1.convertTo(img_input_prev_1_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_2_f(img_input.size(), CV_32F);
  img_input_prev_2.convertTo(img_input_prev_2_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_3_f(img_input.size(), CV_32F);
  img_input_prev_3.convertTo(img_input_prev_3_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_4_f(img_input.size(), CV_32F);
  img_input_prev_4.convertTo(img_input_prev_4_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_5_f(img_input.size(), CV_32F);
  img_input_prev_5.convertTo(img_input_prev_5_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_6_f(img_input.size(), CV_32F);
  img_input_prev_6.convertTo(img_input_prev_6_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_7_f(img_input.size(), CV_32F);
  img_input_prev_7.convertTo(img_input_prev_7_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_8_f(img_input.size(), CV_32F);
  img_input_prev_8.convertTo(img_input_prev_8_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_9_f(img_input.size(), CV_32F);
  img_input_prev_9.convertTo(img_input_prev_9_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_10_f(img_input.size(), CV_32F);
  img_input_prev_10.convertTo(img_input_prev_10_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_11_f(img_input.size(), CV_32F);
  img_input_prev_11.convertTo(img_input_prev_11_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_12_f(img_input.size(), CV_32F);
  img_input_prev_12.convertTo(img_input_prev_12_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_13_f(img_input.size(), CV_32F);
  img_input_prev_13.convertTo(img_input_prev_13_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_14_f(img_input.size(), CV_32F);
  img_input_prev_14.convertTo(img_input_prev_14_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_15_f(img_input.size(), CV_32F);
  img_input_prev_15.convertTo(img_input_prev_15_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_16_f(img_input.size(), CV_32F);
  img_input_prev_16.convertTo(img_input_prev_16_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_17_f(img_input.size(), CV_32F);
  img_input_prev_17.convertTo(img_input_prev_17_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_18_f(img_input.size(), CV_32F);
  img_input_prev_18.convertTo(img_input_prev_18_f, CV_32F, 1./255.);

  cv::Mat img_input_prev_19_f(img_input.size(), CV_32F);
  img_input_prev_19.convertTo(img_input_prev_19_f, CV_32F, 1./255.);


  cv::Mat img_background_f(img_input.size(), CV_32F);
  

  img_background_f = ((img_input_f) + (img_input_prev_1_f) + (img_input_prev_2_f) + 
	  (img_input_prev_3_f) + (img_input_prev_4_f) + (img_input_prev_5_f) + (img_input_prev_6_f) + 
	  (img_input_prev_7_f) + (img_input_prev_8_f) + (img_input_prev_9_f) + (img_input_prev_10_f) + 
	  (img_input_prev_11_f) + (img_input_prev_12_f) + (img_input_prev_13_f) + (img_input_prev_14_f) + 
	  (img_input_prev_15_f) + (img_input_prev_16_f) + (img_input_prev_17_f) + (img_input_prev_18_f) + 
	  (img_input_prev_19_f)) /20.0;

  cv::Mat img_background(img_background_f.size(), CV_8U);

  double minVal, maxVal;
  minVal = 0.; maxVal = 1.;
  img_background_f.convertTo(img_background, CV_8U, 255.0/(maxVal - minVal), -minVal);
  
  //cv::imshow("W Moving Mean BG Model", img_background);

  cv::Mat img_foreground;
  cv::absdiff(img_input, img_background, img_foreground);

  //cv::threshold(img_foreground, img_foreground, threshold, 255, cv::THRESH_BINARY);

  //cv::imshow("W Moving Mean FG Mask", img_foreground);

  img_foreground.copyTo(img_output);


  img_input_prev_19.copyTo(img_input_prev_20);
  img_input_prev_18.copyTo(img_input_prev_19);
  img_input_prev_17.copyTo(img_input_prev_18);
  img_input_prev_16.copyTo(img_input_prev_17);
  img_input_prev_15.copyTo(img_input_prev_16);
  img_input_prev_14.copyTo(img_input_prev_15);
  img_input_prev_13.copyTo(img_input_prev_14);
  img_input_prev_12.copyTo(img_input_prev_13);
  img_input_prev_11.copyTo(img_input_prev_12);
  img_input_prev_10.copyTo(img_input_prev_11);
  img_input_prev_9.copyTo(img_input_prev_10);
  img_input_prev_8.copyTo(img_input_prev_9);
  img_input_prev_7.copyTo(img_input_prev_8);
  img_input_prev_6.copyTo(img_input_prev_7);
  img_input_prev_5.copyTo(img_input_prev_6);
  img_input_prev_4.copyTo(img_input_prev_5);
  img_input_prev_3.copyTo(img_input_prev_4);
  img_input_prev_2.copyTo(img_input_prev_3);
  img_input_prev_1.copyTo(img_input_prev_2);
  img_input.copyTo(img_input_prev_1);

  firstTime = false;
}
