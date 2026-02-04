#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "02. Linear Filtering.h"

int main()
{
    cv::Mat image = cv::imread("Images/input.jpg");
    if (image.empty()) {
        std::cerr << "이미지를 찾을 수 없네, 경로를 확인하게!" << std::endl;
        return -1;
    }

    cv::namedWindow("Original", cv::WINDOW_NORMAL);
    cv::imshow("Original", image);

    cv::Mat filter = applyBoxFilter(image);
    cv::namedWindow("filter", cv::WINDOW_NORMAL);
    cv::imshow("filter", filter);

    cv::waitKey(0);
    return 0;
}

