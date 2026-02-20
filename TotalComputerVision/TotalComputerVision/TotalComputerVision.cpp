#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "11. Feature Point Detection & Matching.h"

int main()
{
    
    cv::Mat image = cv::imread("Images/input.jpg");
    if (image.empty()) 
    {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }
    cv::Mat image_rotate = cv::imread("Images/input_ro.jpg");
    if (image.empty()) 
    {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }

    //cv::namedWindow("Original", cv::WINDOW_NORMAL);
    //cv::imshow("Original", image);

	matchFeatures(image, image_rotate); 
    
    cv::waitKey(0);
    return 0;
}

