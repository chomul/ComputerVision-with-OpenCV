#include "07. Labeling.h"

void labelingPractice(const cv::Mat& src)
{
    cv::Mat gray, binary;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 1. 오츠의 이진화 (THRESH_OTSU를 더하면 임계값을 자동 설정)
    double otsu_thresh = cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    std::cout << "Detected Otsu Threshold: " << otsu_thresh << std::endl;

    // 2. 라벨링 수행
    cv::Mat labels, stats, centroids;
    // stats: [x, y, width, height, area] 
    int num_labels = cv::connectedComponentsWithStats(binary, labels, stats, centroids);

    cv::Mat result = src.clone();

    // 0번 라벨은 보통 '배경'. 그래서 1번부터 시작
    for (int i = 1; i < num_labels; i++) 
    {
        int* p = stats.ptr<int>(i);
        int x = p[cv::ConnectedComponentsTypes::CC_STAT_LEFT];
        int y = p[cv::ConnectedComponentsTypes::CC_STAT_TOP];
        int width = p[cv::ConnectedComponentsTypes::CC_STAT_WIDTH];
        int height = p[cv::ConnectedComponentsTypes::CC_STAT_HEIGHT];
        int area = p[cv::ConnectedComponentsTypes::CC_STAT_AREA];

        // 너무 작은 노이즈 제거
        if (area < 50) continue;

        // 3. 바운딩 박스 그리기
        cv::rectangle(result, cv::Rect(x, y, width, height), cv::Scalar(255, 0, 0), 2);

        // 객체 번호 써넣기
        cv::putText(result, std::to_string(i), cv::Point(x, y - 5),
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
    }

    cv::imshow("Labeling Result", result);

}
