#include "09. Perspective Transform.h"

void deskewImage(const cv::Mat& src)
{
    // 1. 원본 이미지에서 네 모서리 좌표 
    // 실제로는 6주차 Contour로 찾거나 클릭 이벤트 사용
    std::vector<cv::Point2f> srcPoints(4);

    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 1. 전처리 (노이즈 제거 후 이진화)
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);
    // 흰색 배경 반전 처리 및 자동 처리
    cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

    cv::imshow("Binary", binary);

    // 2. 윤곽선 찾기
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    // RETR_EXTERNAL: 가장 바깥쪽 라인만 찾음
    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat result = src.clone();

    for (size_t i = 0; i < contours.size(); i++)
    {
        // 3. 모멘트를 이용한 특징 추출
        cv::Moments m = cv::moments(contours[i]);
        double area = m.m00; // 면적
        int cx = 0, cy = 0; // 무게중심 좌표

        // 너무 작은 노이즈는 무시
        if (area > 100)
        {
            // 무게중심 계산
            cx = static_cast<int>(m.m10 / m.m00);
            cy = static_cast<int>(m.m01 / m.m00);

            // 4. 윤곽선 그리기 및 중심점 표시
            cv::drawContours(result, contours, (int)i, cv::Scalar(0, 255, 0), 2);
            cv::circle(result, cv::Point(cx, cy), 5, cv::Scalar(255, 0, 0), -1);

            std::cout << "Contour #" << i << " Area: " << area << std::endl;

            cv::putText(result, std::to_string(i), cv::Point(cx, cy - 5),
                cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);

            std::vector<cv::Point> approx;
            // epsilon: 근사 정밀도 (둘레 길이에 비례하게 설정하는 것이 팁!)
            double epsilon = 0.02 * cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], approx, epsilon, true);

            // 근사화된 점이 4개라면 사각형으로 간주
            if (approx.size() == 4)
            {
                for (int j = 0; j < 4; j++)
                {
                    cv::circle(result, approx[j], 8, cv::Scalar(255, 0, 255), -1);                    
                }
                SetPointOrder(cv::Point(cx, cy), approx, srcPoints);
            }
        }
    }
    cv::imshow("Contour Analysis", result);

    // 2. 결과 이미지에서의 좌표 (임시)
    float w = 300.0f, h = 400.0f;
    std::vector<cv::Point> shapes;
    shapes.emplace_back(cv::Point2f(w, 0));
    shapes.emplace_back(cv::Point2f(0, 0));
    shapes.emplace_back(cv::Point2f(0, h));
    shapes.emplace_back(cv::Point2f(w, h));
    std::vector<cv::Point2f> dstPoints;
    // srcPoints의 순서에 맞게 dstPoints도 순서대로 넣어야 함
    SetPointOrder(cv::Point2f(w / 2, h / 2), shapes, dstPoints);

    // 3. 변환 행렬(3x3) 구하기
    cv::Mat matrix = cv::getPerspectiveTransform(srcPoints, dstPoints);

    // 4. 이미지 비틀기 실행
    // cv::Mat result;
    cv::warpPerspective(src, result, matrix, cv::Size(w, h));

    cv::namedWindow("Deskewed Image", cv::WINDOW_NORMAL);
    cv::imshow("Deskewed Image", result);

    return;
}

void SetPointOrder(const cv::Point& center, const std::vector<cv::Point>& dots, std::vector<cv::Point2f>& PointVector)
{
    std::vector<cv::Point2f> TempVector(4);
    // 좌상 (0,0) 시작

    for (cv::Point dot : dots)
    {
        if (dot.x < center.x && dot.y < center.y)             // 좌상
            TempVector[0] = dot;
        else if (dot.x >= center.x && dot.y < center.y)       // 우상
            TempVector[1] = dot;
        else if (dot.x < center.x && dot.y >= center.y)       // 좌하
            TempVector[2] = dot;
        else if (dot.x >= center.x && dot.y >= center.y)      // 우하
            TempVector[3] = dot;
        else
        {
            printf("Error Value");
            return;
        }
    }    
        
    PointVector = TempVector;

    return;
}
