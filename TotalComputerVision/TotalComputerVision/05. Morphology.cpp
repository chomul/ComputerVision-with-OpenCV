#include "05. Morphology.h"

cv::Mat applyMorphology(const cv::Mat& binary_img, MorphologyType mType)
{
    cv::Mat dst;

    // 구조 요소(Kernel) 생성: 3x3 사각형 모양
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    switch (mType)
    {
    case Erosion:
        cv::erode(binary_img, dst, element);
        break;
    case Dilation:
        cv::dilate(binary_img, dst, element);
        break;
    case Opening:
        cv::morphologyEx(binary_img, dst, cv::MORPH_OPEN, element);
        break;
    case Closing:
        cv::morphologyEx(binary_img, dst, cv::MORPH_CLOSE, element);
        break;
    default:
        break;
    }

    return dst;
}