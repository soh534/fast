#include "Circle.h"

#include <vector>
#include <opencv2/core/core.hpp>

/****************************************************************************************/
// look-up tables for quick computation
std::vector<cv::Point> getCircle(int x0, int y0, int r)
{
    if (r==1) {
        std::vector<cv::Point> points = {
            cv::Point(x0,y0-1), // pt 1
            cv::Point(x0+1,y0-1), // pt 2
            cv::Point(x0+1,y0), // pt 3
            cv::Point(x0+1,y0+1), // pt 4
            cv::Point(x0,y0+1), // pt 5 
            cv::Point(x0-1,y0+1), // pt 6
            cv::Point(x0-1,y0), // pt 7
            cv::Point(x0-1,y0+1) // pt 8
        };
        return points;
    } else if (r==2) {
        std::vector<cv::Point> points = {
            cv::Point(x0,y0-2), // pt 1
            cv::Point(x0+1,y0-2), // pt 2
            cv::Point(x0+2,y0-1), // pt 3
            cv::Point(x0+2,y0), // pt 4
            cv::Point(x0+2,y0+1), // pt 5 
            cv::Point(x0+1,y0+2), // pt 6
            cv::Point(x0,y0+2), // pt 7
            cv::Point(x0-1,y0+2), // pt 8
            cv::Point(x0-2,y0+1), // pt 9
            cv::Point(x0-2,y0), // pt 10
            cv::Point(x0-2,y0-1), // pt 11
            cv::Point(x0-1,y0-2) // pt 12           
        };
        return points;
    } else if (r==3) {
        std::vector<cv::Point> points = {
            cv::Point(x0,y0-3), // pt 1
            cv::Point(x0+1,y0-3), // pt 2
            cv::Point(x0+2,y0-2), // pt 3
            cv::Point(x0+3,y0-1), // pt 4
            cv::Point(x0+3,y0), // pt 5 
            cv::Point(x0+3,y0+1), // pt 6
            cv::Point(x0+2,y0+2), // pt 7
            cv::Point(x0+1,y0+3), // pt 8
            cv::Point(x0,y0+3), // pt 9
            cv::Point(x0-1,y0+3), // pt 10
            cv::Point(x0-2,y0+2), // pt 11
            cv::Point(x0-3,y0+1), // pt 12           
            cv::Point(x0-3,y0), // pt 13
            cv::Point(x0-3,y0-1), // pt 14
            cv::Point(x0-2,y0-2), // pt 15
            cv::Point(x0-1,y0-3) // pt 16            
        };
        return points;
    } else if (r==4) {
        std::vector<cv::Point> points = {
            cv::Point(x0,y0-4), // pt 1
            cv::Point(x0+1,y0-4), // pt 2
            cv::Point(x0+2,y0-3), // pt 3
            cv::Point(x0+3,y0-2), // pt 4
            cv::Point(x0+4,y0-1), // pt 5 
            cv::Point(x0+4,y0), // pt 6
            cv::Point(x0+4,y0+1), // pt 7
            cv::Point(x0+3,y0+2), // pt 8
            cv::Point(x0+2,y0+3), // pt 9
            cv::Point(x0+1,y0+4), // pt 10
            cv::Point(x0,y0+4), // pt 11
            cv::Point(x0-1,y0+4), // pt 12
            cv::Point(x0-2,y0+3), // pt 13
            cv::Point(x0-3,y0+2), // pt 14
            cv::Point(x0-4,y0+1), // pt 15
            cv::Point(x0-4,y0), // pt 16
            cv::Point(x0-4,y0-1), // pt 17
            cv::Point(x0-3,y0-2), // pt 18
            cv::Point(x0-2,y0-3), // pt 19
            cv::Point(x0-1,y0-4) // pt 20
        };
        return points;
    } else {
        assert(false);
    }
}

int getAngle(int ptIdx, int radius)
{
    ptIdx++;
    if (radius==1) {
    } else if (radius==2) {
        switch(ptIdx) {
        case 1:
            return 0;
        case 2:
            return 30;
        case 3:
            return 60;
        case 4:
            return 90;
        case 5:
            return 120;
        case 6:
            return 150;
        case 7:
            return 180;
        case 8:
            return 210;
        case 9:
            return 240;
        case 10:
            return 270;
        case 11:
            return 300;
        case 12:
            return 330;
        }
    } else if (radius==3) {
        switch(ptIdx) {
        case 1:
            return 0;
        case 2:
            return 22;
        case 3:
            return 45;
        case 4:
            return 77;
        case 5:
            return 90;
        case 6:
            return 112;
        case 7:
            return 135;
        case 8:
            return 158;
        case 9:
            return 180;
        case 10:
            return 202;
        case 11:
            return 225;
        case 12:
            return 247;
        case 13:
            return 270;
        case 14:
            return 292;
        case 15:
            return 315;
        case 16:
            return 337;
        }
    } else if (radius==4) {
        switch(ptIdx) {
        case 1:
            return 0;
        case 2:
            return 18;
        case 3:
            return 36;
        case 4:
            return 54;
        case 5:
            return 72;
        case 6:
            return 90;
        case 7:
            return 108;
        case 8:
            return 126;
        case 9:
            return 144;
        case 10:
            return 162;
        case 11:
            return 180;
        case 12:
            return 198;
        case 13:
            return 216;
        case 14:
            return 234;
        case 15:
            return 252;
        case 16:
            return 270;
        case 17:
            return 288;
        case 18:
            return 306;
        case 19:
            return 324;
        case 20:
            return 342;
        }
    } else {
        assert(false);
    }
    return -1;
}
