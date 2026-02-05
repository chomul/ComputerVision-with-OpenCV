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

    // 2. 5x5 가우시안 커널 (정수 근사값)
    cv::Mat gray_blur = cv::Mat::zeros(gray.size(), CV_8UC1);
    int kernel[5][5] = {
        { 1,  4,  7,  4, 1 },
        { 4, 16, 26, 16, 4 },
        { 7, 26, 41, 26, 7 },
        { 4, 16, 26, 16, 4 },
        { 1,  4,  7,  4, 1 }
    };

    for (int y = 2; y < gray.rows - 2; ++y) {
        for (int x = 2; x < gray.cols - 2; ++x) {
            float sum = 0.0f;

            // 5x5 컨볼루션
            for (int ky = -2; ky <= 2; ++ky) {
                for (int kx = -2; kx <= 2; ++kx) {
                    float pixel = (float)gray.at<uchar>(y + ky, x + kx);
                    int weight = kernel[ky + 2][kx + 2];
                    sum += pixel * weight;
                }
            }

            // 합계가 273이므로 나눠서 정규화 (Normalization)
            gray_blur.at<uchar>(y, x) = cv::saturate_cast<uchar>(sum / 273.0f);
        }
    }

    // 3. 소벨 커널 정의
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
    float Threshold = 100.f;

    for (int y = 1; y < gray_blur.rows - 1; ++y) {
        for (int x = 1; x < gray_blur.cols - 1; ++x) {
            float sumX = 0.0f; // 수직 검출
            float sumY = 0.0f; // 수평 검출

            // 각 픽셀별 커널 연산 진행
            for (int ky = -1; ky <= 1; ++ky) 
            {
                for (int kx = -1; kx <= 1; ++kx) 
                {
                    float pixel = (float)gray_blur.at<uchar>(y + ky, x + kx);
                    sumX += Gx[1 + ky][1 + kx] * pixel;
                    sumY += Gy[1 + ky][1 + kx] * pixel;
                }
            }

            // 보통 sqrt(sumX*sumX + sumY*sumY) -> abs(sumX) + abs(sumY)로 간략화
            float mag = std::abs(sumX) + std::abs(sumY);

            dst.at<uchar>(y, x) = cv::saturate_cast<uchar>(mag) < Threshold ? 0 : cv::saturate_cast<uchar>(mag);
        }
    }
    return dst;
}
