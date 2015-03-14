#ifndef _FASTDETECTOR_H_
#define _FASTDETECTOR_H_

#include <opencv2/core/core.hpp>

#include "helper.h"

#define THRESHOLD 17 // smallest difference in pixel intensity noticed as possible corner
#define ANGULAR_THRESHOLD 20 // maximum allowable difference in orientation of corner

class FastDetector {
    std::vector<cv::Point> detectedPoints;

    cv::Mat greyScale(cv::Mat image);
    int pixelAt(cv::Mat& image, int x, int y);
    CircleData exploreCircle(cv::Mat& image, int x, int y, int r);
    int getOrientation(CircleData cd);
    bool crossCheck(cv::Mat& image, int x, int y);
    bool defaultCheck(cv::Mat& image, int x, int y);
    bool extendedCheck(cv::Mat& image, int x, int y);
  public:
    FastDetector();
    void detect(cv::Mat image);
    void express(cv::Mat& image);
};

#endif
