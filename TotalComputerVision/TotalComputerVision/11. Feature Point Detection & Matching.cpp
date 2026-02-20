#include "11. Feature Point Detection & Matching.h"

void matchFeatures(const cv::Mat& img1, const cv::Mat& img2)
{
    // 1. ORB 객체 생성
    cv::Ptr<cv::ORB> orb = cv::ORB::create();

    // 2. 특징점(Keypoints)과 기술자(Descriptors) 추출
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;

    orb->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
    orb->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);

    // 3. 매칭 (Brute-Force Matcher 사용)
    // ORB는 이진 기술자를 쓰므로 NORM_HAMMING 거리 계산
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    // 4. 좋은 매칭점만 선별 (거리가 짧은 상위 50개)
    std::sort(matches.begin(), matches.end());
    std::vector<cv::DMatch> good_matches(matches.begin(), matches.begin() + 30);

    // 5. 결과 그리기
    cv::Mat res;
    cv::drawMatches(img1, keypoints1, img2, keypoints2, good_matches, res);

    cv::namedWindow("Feature Matching", cv::WINDOW_NORMAL);
    cv::imshow("Feature Matching", res);
}