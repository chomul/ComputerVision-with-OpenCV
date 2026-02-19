#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "06. Contour Detection & Features.h"

int main()
{
    
    cv::Mat image = cv::imread("Images/BinaryImage.jpg");
    if (image.empty()) 
    {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }

    // cv::namedWindow("Original", cv::WINDOW_NORMAL);
    cv::imshow("Original", image);

	analyzeContours(image); 
    
    cv::waitKey(0);
    return 0;
}

