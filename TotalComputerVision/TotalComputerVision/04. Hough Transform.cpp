#include "04. Hough Transform.h"

cv::Mat detectHoughLines(const cv::Mat& src)
{
    cv::Mat gray, edge;
    // 1. 전처리 
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);
    cv::Canny(gray, edge, 50, 150); // OpenCV의 캐니 에지 검출기 

    // 2. 허프 선 검출 (확률적 방식)
    std::vector<cv::Vec4i> lines;
    // 파라미터: 이미지, 결과벡터, 거리해상도(1), 각도해상도(CV_PI/180), 임계값(표수), 최소선길이, 최대간격
    cv::HoughLinesP(edge, lines, 1, CV_PI / 180, 30, 100, 5);

    // 3. 결과 그리기
    cv::Mat result = src.clone();
    for (size_t i = 0; i < lines.size(); i++) 
    {
        cv::Vec4i l = lines[i];
        cv::line(result, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
    }

    return result;
}

cv::Mat detectHoughCircles(const cv::Mat& src)
{
    cv::Mat gray, result;
    result = src.clone();

    // 1. 그레이스케일 및 블러 (노이즈 제거)
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);

    // 2. 허프 원 검출
    std::vector<cv::Vec3f> circles;
    // 파라미터: 이미지, 결과, 방법, dp(해상도비율), 최소거리, 캐니임계값, 중심투표임계값, 최소반지름, 최대반지름
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 8, 100, 35, 0, 0);

    // 3. 찾은 원 그리기
    for (size_t i = 0; i < circles.size(); i++) 
    {
        cv::Vec3f c = circles[i];
        cv::Point center(cv::saturate_cast<int>(c[0]), cv::saturate_cast<int>(c[1]));
        int radius = cv::saturate_cast<int>(c[2]);

        // 원 중심 그리기
        cv::circle(result, center, 3, cv::Scalar(0, 255, 0), -1, cv::LINE_AA);
        // 원 둘레 그리기
        cv::circle(result, center, radius, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
    }

    return result;
}
