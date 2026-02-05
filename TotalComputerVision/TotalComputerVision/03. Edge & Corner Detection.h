#pragma once

#include <opencv2/opencv.hpp>

cv::Mat detectSobelEdge(const cv::Mat& src);
cv::Mat applySeparableGaussian(const cv::Mat& gray);
cv::Mat computeSeparableSobelX(const cv::Mat& gray_blur);