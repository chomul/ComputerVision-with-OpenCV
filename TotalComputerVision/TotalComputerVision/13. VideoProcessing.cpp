#include "13. VideoProcessing.h"

void runVideoProcessing()
{   
    // 1. 비디오 캡처 객체 생성 (0번은 기본 웹캠, 파일 경로를 넣으면 동영상을 읽음)
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "카메라를 열 수 없음!" << std::endl;
        return;
    }

    cv::Mat frame;
    while (true)
    {
        // 2. 한 프레임씩 읽어오기
        cap >> frame;
        if (frame.empty()) break;

        // 3. 실시간 처리 
        // 간단하게 그레이스케일로만 변경
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // 4. 결과 
        cv::imshow("Real-time Video", gray);

        // 'ESC' 키를 누르면 종료 (30ms 대기)
        if (cv::waitKey(30) == 27) break;
    }

    cap.release(); // 자원 해제
    cv::destroyAllWindows();
}

void runVideoProcessingMOG2()
{
    // 1. 비디오 캡처 객체 생성 (0번은 기본 웹캠, 파일 경로를 넣으면 동영상을 읽음)
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "카메라를 열 수 없음!" << std::endl;
        return;
    }

    cv::Mat frame;
    cv::Mat fgMaskMOG2;
    cv::Ptr<cv::BackgroundSubtractor> pMOG2;
    pMOG2 = cv::createBackgroundSubtractorMOG2();
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    while (true)
    {
        // 2. 한 프레임씩 읽어오기
        cap >> frame;
        if (frame.empty()) break;

        pMOG2->apply(frame, fgMaskMOG2);
        cv::threshold(fgMaskMOG2, fgMaskMOG2, 250, 255, cv::THRESH_BINARY);
        cv::morphologyEx(fgMaskMOG2, fgMaskMOG2, cv::MORPH_OPEN, kernel);

        // 3. 실시간 처리 
        // 간단하게 그레이스케일로만 변경
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // 4. 결과 
        //cv::imshow("Real-time Video", gray);
        cv::imshow("MOG2 Video", fgMaskMOG2);

        // 'ESC' 키를 누르면 종료 (30ms 대기)
        if (cv::waitKey(30) == 27) break;
    }

    cap.release(); // 자원 해제
    cv::destroyAllWindows();
}
