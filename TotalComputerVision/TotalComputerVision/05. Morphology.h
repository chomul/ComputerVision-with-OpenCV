#pragma once
#include <opencv2/opencv.hpp>

enum MorphologyType
{
	Erosion,
	Dilation,
	Opening,
	Closing
};

cv::Mat applyMorphology(const cv::Mat& binary_img, MorphologyType mType);