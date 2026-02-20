#include "10. Histogram.h"

void enhanceContrast(const cv::Mat& src)
{
    cv::Mat dst;

    // 1. 그레이스케일인 경우
    if (src.channels() == 1)
    {
        cv::equalizeHist(src, dst);
    }
    // 2. 컬러 이미지인 경우 (밝기 정보만 평활화 -> 색이 안 깨짐)
    else
    {
        cv::Mat ycrcb;
        cv::cvtColor(src, ycrcb, cv::COLOR_BGR2YCrCb);

        // 채널 분리 (Y: 밝기, Cr/Cb: 색상)
        std::vector<cv::Mat> channels;
        cv::split(ycrcb, channels);

        // Y 채널(밝기)만 평활화
        cv::equalizeHist(channels[0], channels[0]);

        // 다시 합치기
        cv::merge(channels, ycrcb);
        cv::cvtColor(ycrcb, dst, cv::COLOR_YCrCb2BGR);
    }

    cv::namedWindow("Enhanced Contrast", cv::WINDOW_NORMAL);
	cv::imshow("Enhanced Contrast", dst);

    return;
}

void applyCLAHE(const cv::Mat& src)
{
    cv::Mat dst;

    // 1. 그레이스케일인 경우
    if (src.channels() == 1)
    {
        cv::equalizeHist(src, dst);
    }
    // 2. 컬러 이미지인 경우 (밝기 정보만 평활화 -> 색이 안 깨짐)
    else
    {
        cv::Mat ycrcb;
        cv::cvtColor(src, ycrcb, cv::COLOR_BGR2YCrCb);

        std::vector<cv::Mat> channels;
        cv::split(ycrcb, channels);

        // 2. CLAHE 객체 생성
        // clipLimit: 2.0, tileGridSize: 8x8
        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2.0, cv::Size(8, 8));

        // 3. 밝기(Y) 채널에만 CLAHE 적용
        clahe->apply(channels[0], channels[0]);

        // 4. 다시 합치기
        cv::merge(channels, ycrcb);
        cv::cvtColor(ycrcb, dst, cv::COLOR_YCrCb2BGR);
    }

	cv::namedWindow("CLAHE Result", cv::WINDOW_NORMAL);
	cv::imshow("CLAHE Result", dst);

    return;
}
