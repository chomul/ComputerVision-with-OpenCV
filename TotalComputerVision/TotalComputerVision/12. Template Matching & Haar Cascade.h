#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

void runTemplateMatching(const cv::Mat& src, const cv::Mat& templ);

void detectFaceHaar(const cv::Mat& src);