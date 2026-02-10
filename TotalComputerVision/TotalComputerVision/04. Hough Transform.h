#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat detectHoughLines(const cv::Mat& src);

cv::Mat detectHoughCircles(const cv::Mat& src);