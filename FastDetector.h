#ifndef _FASTDETECTOR_H_
#define _FASTDETECTOR_H_

#include <opencv2/core/core.hpp>

#include "helper.h"

#define THRESHOLD 17 // smallest difference in pixel intensity noticed as possible corner
#define ANGULAR_THRESHOLD 20 // maximum allowable difference in orientation of corner

class FastDetector {
    std::vector<cv::Point> detectedPoints;

    cv::Mat greyScale(const cv::Mat& image);
    int pixelAt(const cv::Mat& image, const int& x, const int& y);
    CircleData exploreCircle(const cv::Mat& image, const int x, const int y, const int r);
    int getOrientation(const CircleData& cd);
    bool crossCheck(const cv::Mat& image, const int x, const int y);
    bool defaultCheck(const cv::Mat& image, const int x, const int y);
    bool extendedCheck(const cv::Mat& image, const int x, const int y);
  public:
    FastDetector();
    void detect(const cv::Mat& image);
    void express(cv::Mat& image);
};

#endif
