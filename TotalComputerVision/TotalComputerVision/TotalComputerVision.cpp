#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "04. Hough Transform.h"

int main()
{
    cv::Mat image = cv::imread("Images/Circle.jpg");
    if (image.empty()) {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }

    /*
    cv::Mat HoughLines = detectHoughLines(image);
    cv::namedWindow("HoughLines", cv::WINDOW_NORMAL);
    cv::imshow("HoughLines", HoughLines);
    */

    cv::Mat CircleLines = detectHoughCircles(image);
    cv::namedWindow("CircleLines", cv::WINDOW_NORMAL);
    cv::imshow("CircleLines", CircleLines);

    cv::waitKey(0);
    return 0;
}

