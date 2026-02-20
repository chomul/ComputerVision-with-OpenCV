#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

void deskewImage(const cv::Mat& src);

// index -> 0 : аб╩С, 1 : ©Л╩С, 2 : абго, 3 : ©Лго
void SetPointOrder(const cv::Point& center, const std::vector<cv::Point>& dots, std::vector<cv::Point2f>& PointVector);