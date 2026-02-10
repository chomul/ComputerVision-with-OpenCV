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

    cv::Mat gray_blur = cv::Mat::zeros(gray.size(), CV_8UC1);
    gray_blur = applySeparableGaussian(gray);

    dst = computeSeparableSobelX(gray_blur);
    return dst;
}

cv::Mat applySeparableGaussian(const cv::Mat& gray) {
    cv::Mat temp = cv::Mat::zeros(gray.size(), CV_32FC1); // 중간 결과 (정밀도를 위해 float)
    cv::Mat dst = cv::Mat::zeros(gray.size(), CV_8UC1);

    // 1D 가우시안 커널 (1-4-6-4-1) -> 합은 16
    float k[5] = { 1 / 16.f, 4 / 16.f, 6 / 16.f, 4 / 16.f, 1 / 16.f };

    // Pass 1: 가로 방향 연산
    for (int y = 0; y < gray.rows; ++y) {
        for (int x = 2; x < gray.cols - 2; ++x) {
            float sum = 0;
            for (int i = -2; i <= 2; ++i)
                sum += gray.at<uchar>(y, x + i) * k[i + 2];
            temp.at<float>(y, x) = sum;
        }
    }

    // Pass 2: 세로 방향 연산 (temp 이미지 이용)
    for (int y = 2; y < gray.rows - 2; ++y) {
        for (int x = 0; x < gray.cols; ++x) {
            float sum = 0;
            for (int i = -2; i <= 2; ++i)
                sum += temp.at<float>(y + i, x) * k[i + 2];
            dst.at<uchar>(y, x) = cv::saturate_cast<uchar>(sum);
        }
    }
    return dst;
}

// Gx 계산 예시 
cv::Mat computeSeparableSobelX(const cv::Mat& gray_blur) {
    cv::Mat temp = cv::Mat::zeros(gray_blur.size(), CV_32FC1);
    cv::Mat gradX = cv::Mat::zeros(gray_blur.size(), CV_32FC1);

    // 1D 커널 정의
    float diffK[3] = { -1, 0, 1 }; // 미분 (가로)
    float smoothK[3] = { 1, 2, 1 }; // 스무딩 (세로)

    // Pass 1: 가로 방향 미분 적용
    for (int y = 0; y < gray_blur.rows; ++y) {
        for (int x = 1; x < gray_blur.cols - 1; ++x) {
            float sum = 0;
            for (int i = -1; i <= 1; ++i)
                sum += gray_blur.at<uchar>(y, x + i) * diffK[i + 1];
            temp.at<float>(y, x) = sum ;
        }
    }

    // Pass 2: 세로 방향 스무딩 적용
    for (int y = 1; y < gray_blur.rows - 1; ++y) {
        for (int x = 0; x < gray_blur.cols; ++x) {
            float sum = 0;
            for (int i = -1; i <= 1; ++i)
                sum += temp.at<float>(y + i, x) * smoothK[i + 1];
            gradX.at<float>(y, x) = sum > 40 ? sum : 0;
        }
    }
    return gradX;
}