#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "05. Morphology.h"

int main()
{
    cv::Mat image = cv::imread("Images/Circle.jpg");
    if (image.empty()) {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }

    cv::namedWindow("Original", cv::WINDOW_NORMAL);
    cv::imshow("Original", image);

    cv::Mat Morphology = applyMorphology(image, MorphologyType::Erosion);
    cv::namedWindow("Morphology", cv::WINDOW_NORMAL);
    cv::imshow("Morphology", Morphology);

    cv::waitKey(0);
    return 0;
}

