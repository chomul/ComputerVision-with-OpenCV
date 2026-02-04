#include "02. Linear Filtering.h"

cv::Mat applyBoxFilter(const cv::Mat& src) {
    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());

    // 1. 3x3 커널 정의 (모든 값이 1/9)
    float kernel[5][5];
    for (int i = 0; i < 5; ++i) 
        for (int j = 0; j < 5; ++j) 
            kernel[i][j] = 1.0f / 25.0f;


    // 2. 이미지 순회 (가장자리 1픽셀은 계산에서 제외)
    for (int y = 2; y < src.rows - 2; ++y) 
    {
        for (int x = 2; x < src.cols - 2; ++x) 
        {
            cv::Vec3f sum = { 0, 0, 0 }; // 색상별 합계 (Blue, Green, Red)

            // [실습 빈칸 1] 커널을 주변 3x3 영역에 적용하게
            for (int ky = -2; ky <= 2; ++ky) {
                for (int kx = -2; kx <= 2; ++kx) {
                    // src에서 (y+ky, x+kx) 위치의 픽셀을 가져와서
                    // kernel[ky+1][kx+1] 값을 곱한 뒤 sum에 누적하게!

                    sum += kernel[2 + ky][2 + kx] * (cv::Vec3f)src.at<cv::Vec3b>(y + ky, x + kx);                   
                }
            }

            // [실습 빈칸 2] 최종 sum을 dst에 대입하게 (Vec3b로 형변환 잊지 말게)
            dst.at<cv::Vec3b>(y, x)[0] = cv::saturate_cast<uchar>(sum[0]);
            dst.at<cv::Vec3b>(y, x)[1] = cv::saturate_cast<uchar>(sum[1]);
            dst.at<cv::Vec3b>(y, x)[2] = cv::saturate_cast<uchar>(sum[2]);
        }
    }
    return dst;
}