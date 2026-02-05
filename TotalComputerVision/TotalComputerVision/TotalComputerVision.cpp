#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "03. Edge & Corner Detection.h"

int main()
{
    cv::Mat image = cv::imread("Images/input.jpg");
    if (image.empty()) {
        std::cerr << "이미지를 찾을 수 없음" << std::endl;
        return -1;
    }

    // 시간 측정
    auto start = std::chrono::steady_clock::now();

    cv::Mat edge = detectSobelEdge(image);
    cv::namedWindow("edge", cv::WINDOW_NORMAL);
    cv::imshow("edge", edge);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time in seconds : " << elapsed_seconds.count() << std::endl;

    cv::waitKey(0);
    return 0;
}

