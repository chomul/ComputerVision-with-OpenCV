#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

void enhanceContrast(const cv::Mat& src);

void applyCLAHE(const cv::Mat& src);