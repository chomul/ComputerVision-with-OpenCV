#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>

cv::Mat translateImage(const cv::Mat& src, float tx, float ty)
{
    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());

    for (int y = 0; y < src.rows; ++y)
    {
        for (int x = 0; x < src.cols; ++x)
        {
            int newX = static_cast<int>(x + tx);
            int newY = static_cast<int>(y + ty);

            if (newX >= 0 && newX < dst.cols && newY >= 0 && newY < dst.rows)
                dst.at<cv::Vec3b>(newY, newX) = src.at<cv::Vec3b>(y, x);
        }
    }
    return dst;
}

cv::Mat rotateImage(const cv::Mat& src, double angle_degree) {
    double angle_rad = angle_degree * CV_PI / 180.0;
    double cos_a = std::cos(angle_rad);
    double sin_a = std::sin(angle_rad);

    cv::Mat dst = cv::Mat::zeros(src.size(), src.type());
    float centerX = src.cols / 2.0f;
    float centerY = src.rows / 2.0f;

    for (int y_dst = 0; y_dst < dst.rows; ++y_dst) {
        for (int x_dst = 0; x_dst < dst.cols; ++x_dst) {
            float tx = x_dst - centerX;
            float ty = y_dst - centerY;

            float x_src = tx * cos_a + ty * sin_a + centerX;
            float y_src = ty * cos_a - tx * sin_a + centerY;

            if (x_src >= 0 && x_src < dst.cols && y_src >= 0 && y_src < dst.rows) {
                dst.at<cv::Vec3b>(y_dst, x_dst) = src.at<cv::Vec3b>((int)y_src, (int)x_src);
            }
        }
    }
    return dst;
}

void Fun01()
{
    cv::Mat image = cv::imread("Images/input.jpg");
    if (image.empty()) {
        std::cerr << "이미지를 찾을 수 없네, 경로를 확인하게!" << std::endl;
        return;
    }

    cv::namedWindow("Original", cv::WINDOW_NORMAL);
    cv::imshow("Original", image);

    cv::Mat translated = translateImage(image, 50.0f, 30.0f);
    cv::namedWindow("Translated", cv::WINDOW_NORMAL);
    cv::imshow("Translated", translated);

    cv::Mat rotation = rotateImage(image, 90);
    cv::namedWindow("Rotation", cv::WINDOW_NORMAL);
    cv::imshow("Rotation", rotation);
    cv::waitKey(0);

    return;
}

