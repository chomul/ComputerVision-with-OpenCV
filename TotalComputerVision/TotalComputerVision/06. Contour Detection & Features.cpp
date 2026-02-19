#include "06. Contour Detection & Features.h"

void analyzeContours(const cv::Mat& src)
{
    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 1. 전처리 (노이즈 제거 후 이진화)
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY);

    // 2. 윤곽선 찾기
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    // RETR_EXTERNAL: 가장 바깥쪽 라인만 찾음
    cv::findContours(binary, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat result = src.clone();

    for (size_t i = 0; i < contours.size(); i++) 
    {
        // 3. 모멘트를 이용한 특징 추출
        cv::Moments m = cv::moments(contours[i]);
        double area = m.m00; // 면적

        // 너무 작은 노이즈는 무시
        if (area > 100) {
            // 무게중심 계산
            int cx = static_cast<int>(m.m10 / m.m00);
            int cy = static_cast<int>(m.m01 / m.m00);

            // 4. 윤곽선 그리기 및 중심점 표시
            cv::drawContours(result, contours, (int)i, cv::Scalar(0, 255, 0), 2);
            cv::circle(result, cv::Point(cx, cy), 5, cv::Scalar(255, 0, 0), -1);

            std::cout << "Contour #" << i << " Area: " << area << std::endl;
        }
    }
    cv::imshow("Contour Analysis", result);
}
