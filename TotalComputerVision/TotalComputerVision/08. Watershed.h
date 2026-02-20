#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

void performWatershed(const cv::Mat& src)
{
	// 0. 전처리 : 그레이스케일 변환 + 이진화
    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    // 경계전을 먹어버려서 수동으로 대체
    // cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::threshold(gray, binary, 100, 255, cv::THRESH_BINARY);

    cv::imshow("Gray", gray);
	cv::imshow("Initial Binary Image", binary);

    // 1. 노이즈 제거 (모폴로지 열기)
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(binary, binary, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), 2);

	cv::imshow("Binary Image", binary);

    // 2. 확실한 배경 확보 (팽창)
    cv::Mat sure_bg;
    cv::dilate(binary, sure_bg, kernel, cv::Point(-1, -1), 3);

    // 3. 확실한 전경 확보 (거리 변환 활용)
    cv::Mat dist_transform;
    cv::distanceTransform(binary, dist_transform, cv::DIST_L2, 3);

    cv::Mat sure_fg;
    // 거리값의 70% 이상인 곳만 확실한 전경(객체의 중심)으로 인정
    double maxVal;
    cv::minMaxLoc(dist_transform, 0, &maxVal);
    cv::threshold(dist_transform, sure_fg, 0.7 * maxVal, 255, cv::THRESH_BINARY);
    sure_fg.convertTo(sure_fg, CV_8U);

    // 4. 마커 생성
    cv::Mat markers;
    int num_labels = cv::connectedComponents(sure_fg, markers);

    // 워터셰드 함수는 배경을 1로, 모르는 영역을 0
    markers = markers + 1;
    // 확실히 배경인 곳과 전경인 곳을 뺀 '경계 미확정 지역'을 0 변경
    cv::Mat unknown = sure_bg - sure_fg;
    for (int y = 0; y < markers.rows; y++) 
    {
        for (int x = 0; x < markers.cols; x++) 
        {
            if (unknown.at<uchar>(y, x) == 255) markers.at<int>(y, x) = 0;
        }
    }

    // 5. 워터셰드 실행
    cv::watershed(src, markers);

    // 6. 결과 시각화 (경계선을 빨간색)
    cv::Mat result = src.clone();
    for (int y = 0; y < markers.rows; y++) 
    {
        for (int x = 0; x < markers.cols; x++) 
        {
            if (markers.at<int>(y, x) == -1) // -1이 워터셰드가 찾은 경계선
                result.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 255);
        }
    }

    cv::imshow("Watershed Result", result);
}