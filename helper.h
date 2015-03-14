#ifndef _HELPER_H_
#define _HELPER_H_

#include <vector>
#include <opencv2/core/core.hpp>

/* data structure for circumference around pixel */
struct CircleData {
    int dkBeginAngle;
    int dkEndAngle;
    int brBeginAngle;
    int brEndAngle;
    int dkConsec;
    int brConsec;
    CircleData(int dkBegin, int dkEnd, int brBegin, int brEnd, int numDk, int numBr);
};

/* look-up tables for quick computation */
std::vector<cv::Point> getCircle(int x0, int y0, int rad);
int getAngle(int ptIdx, int radius);

#endif
