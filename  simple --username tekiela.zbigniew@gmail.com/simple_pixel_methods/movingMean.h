#pragma once

#include <iostream>
#include <cv.h>
#include <highgui.h>

class movingMean
{
private:
  bool firstTime;
  int licznik;
  cv::Mat img_input_prev_1;
  cv::Mat img_input_prev_2;
  cv::Mat img_input_prev_3;
  cv::Mat img_input_prev_4;
  cv::Mat img_input_prev_5;
  cv::Mat img_input_prev_6;
  cv::Mat img_input_prev_7;
  cv::Mat img_input_prev_8;
  cv::Mat img_input_prev_9;
  cv::Mat img_input_prev_10;
  cv::Mat img_input_prev_11;
  cv::Mat img_input_prev_12;
  cv::Mat img_input_prev_13;
  cv::Mat img_input_prev_14;
  cv::Mat img_input_prev_15;
  cv::Mat img_input_prev_16;
  cv::Mat img_input_prev_17;
  cv::Mat img_input_prev_18;
  cv::Mat img_input_prev_19;
  cv::Mat img_input_prev_20;
  bool enableWeight;
  bool enableThreshold;
  int threshold;
  bool showOutput;
  bool showBackground;

public:
  movingMean();
  ~movingMean();

  void process(const cv::Mat &img_input, cv::Mat &img_output);
};

