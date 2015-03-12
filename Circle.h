#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <vector>
#include <opencv2/core/core.hpp>

/****************************************************************************************/
// data structure for circumference around pixel
struct CircleData {
    int dkBeginAngle;
    int dkEndAngle;
    int brBeginAngle;
    int brEndAngle;
    int dkConsec;
    int brConsec;
    CircleData(int dkBegin, int dkEnd, int brBegin, int brEnd, int numDk, int numBr):
        dkBeginAngle(dkBegin),
        dkEndAngle(dkEnd),
        brBeginAngle(brBegin),
        brEndAngle(brEnd),
        dkConsec(numDk),
        brConsec(numBr) {}
};

/****************************************************************************************/
// look-up tables for quick computation
std::vector<cv::Point> getCircle(int x0, int y0, int r);
int getAngle(int ptIdx, int radius);

#endif
