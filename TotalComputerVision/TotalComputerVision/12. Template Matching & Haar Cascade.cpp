#include "12. Template Matching & Haar Cascade.h"

void runTemplateMatching(const cv::Mat& src, const cv::Mat& templ)
{
    cv::Mat graySrc, grayTempl;

    if (src.channels() > 1) cv::cvtColor(src, graySrc, cv::COLOR_BGR2GRAY);
    else graySrc = src;

    if (templ.channels() > 1) cv::cvtColor(templ, grayTempl, cv::COLOR_BGR2GRAY);
    else grayTempl = templ;

    cv::Mat result;
    // 1. 매칭 수행 (TM_CCOEFF_NORMED가 가장 결과가 정확한 편)
    cv::matchTemplate(graySrc, grayTempl, result, cv::TM_CCOEFF_NORMED);

    // 2. 결과 그리기 (maxLoc이 가장 닮은 곳의 왼쪽 위 좌표)
    cv::Mat display = src.clone();
    float threshold = 0.8f;
    int cnt = 0;
    for (int y = 0; y < result.rows; y++) 
    {
        for (int x = 0; x < result.cols; x++) 
        {
            if (result.at<float>(y, x) >= threshold) 
            {
                cv::rectangle(display, cv::Rect(x, y, templ.cols, templ.rows),
                    cv::Scalar(0, 0, 255), 2);
            }
        }
    }

    cv::namedWindow("Template Matching", cv::WINDOW_NORMAL);
    cv::imshow("Template Matching", display);
}

void detectFaceHaar(const cv::Mat& src)
{
    // 1. 분류기 객체 생성
    cv::CascadeClassifier face_cascade;

    // 2. 학습된 XML 데이터 로드
    if (!face_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml")) 
    {
        std::cout << "XML 파일을 찾을 수 없음" << std::endl;
        return;
    }

    // 3. 전처리 (그레이스케일 변환 및 히스토그램 평활화)
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray, gray);

    // 4. 얼굴 검출 실행
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces,
        1.1,      // Scale Factor: 이미지를 10%씩 줄여가며 찾음
        3,        // Min Neighbors: 최소 3번 중복 검출되어야 인정
        0,        // Flags (기본값 0)
        cv::Size(30, 30)); // 최소 얼굴 크기

    // 5. 결과 시각화
    cv::Mat display = src.clone();
    for (size_t i = 0; i < faces.size(); i++) {
        cv::rectangle(display, faces[i], cv::Scalar(255, 0, 0), 2);
    }

    cv::namedWindow("Haar Cascade Face Detection", cv::WINDOW_NORMAL);
    cv::imshow("Haar Cascade Face Detection", display);
}
