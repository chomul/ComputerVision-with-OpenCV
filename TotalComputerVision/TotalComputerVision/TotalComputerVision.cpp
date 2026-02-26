#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "12. Template Matching & Haar Cascade.h"

int main()
{
    
    cv::Mat image = cv::imread("Images/Template.png");
    if (image.empty()) 
    {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }
    cv::Mat image_input = cv::imread("Images/TemplateInput.png");
    if (image.empty()) 
    {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }
    cv::Mat image_face = cv::imread("Images/face.jpg");
    if (image.empty())
    {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }


    //cv::namedWindow("Original", cv::WINDOW_NORMAL);
    //cv::imshow("Original", image);

    // runTemplateMatching(image_input, image);
    detectFaceHaar(image_face);
    
    cv::waitKey(0);
    return 0;
}

