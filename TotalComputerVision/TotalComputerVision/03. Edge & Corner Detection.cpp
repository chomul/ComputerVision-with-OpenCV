#include "03. Edge & Corner Detection.h"

cv::Mat detectSobelEdge(const cv::Mat& src)
{
    // 1. 그레이스케일 변환
    cv::Mat gray;
    if (src.channels() == 3)
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    else
        gray = src.clone();

    cv::Mat dst = cv::Mat::zeros(gray.size(), CV_8UC1);

    // 2. 소벨 커널 정의
    float Gx[3][3] = // 수직 에지 검출
    { 
        {-1, 0, 1}, 
        {-2, 0, 2}, 
        {-1, 0, 1} 
    };
    float Gy[3][3] = // 수평 에지 검출
    { 
        {-1, -2, -1}, 
        {0, 0, 0}, 
        {1, 2, 1} 
    };

    for (int y = 1; y < gray.rows - 1; ++y) {
        for (int x = 1; x < gray.cols - 1; ++x) {
            float sumX = 0.0f; // 수직 검출
            float sumY = 0.0f; // 수평 검출

            // 각 픽셀별 커널 연산 진행
            for (int ky = -1; ky <= 1; ++ky) 
            {
                for (int kx = -1; kx <= 1; ++kx) 
                {
                    float pixel = (float)gray.at<uchar>(y + ky, x + kx);
                    sumX += Gx[1 + ky][1 + kx] * pixel;
                    sumY += Gy[1 + ky][1 + kx] * pixel;
                }
            }

            // 보통 sqrt(sumX*sumX + sumY*sumY) -> abs(sumX) + abs(sumY)로 간략화
            float mag = std::abs(sumX) + std::abs(sumY);

            dst.at<uchar>(y, x) = cv::saturate_cast<uchar>(mag);
        }
    }
    return dst;
}
