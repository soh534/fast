#include "helper.h"

#include <cstdlib>
#include <iostream>

CircleData::CircleData(int dkBegin, int dkEnd,
                       int brBegin, int brEnd,
                       int numDk, int numBr)
{
    dkBeginAngle = dkBegin;
    dkEndAngle = dkEnd;
    brBeginAngle = brBegin;
    brEndAngle = brEnd;
    dkConsec = numDk;
    brConsec = numBr;
}

/* look-up tables for quick computation */
std::vector<cv::Point> getCircle(int x0, int y0, int rad)
{
    std::vector<cv::Point> points;
    switch (rad) {
    case 1:
        points.push_back(cv::Point(x0,y0-1)); // pt 1
        points.push_back(cv::Point(x0+1,y0-1)); // pt 2
        points.push_back(cv::Point(x0+1,y0)); // pt 3
        points.push_back(cv::Point(x0+1,y0+1)); // pt 4
        points.push_back(cv::Point(x0,y0+1)); // pt 5 
        points.push_back(cv::Point(x0-1,y0+1)); // pt 6
        points.push_back(cv::Point(x0-1,y0)); // pt 7
        points.push_back(cv::Point(x0-1,y0+1)); // pt 8
        return points;
    case 2:
        points.push_back(cv::Point(x0,y0-2)); // pt 1
        points.push_back(cv::Point(x0+1,y0-2)); // pt 2
        points.push_back(cv::Point(x0+2,y0-1)); // pt 3
        points.push_back(cv::Point(x0+2,y0)); // pt 4
        points.push_back(cv::Point(x0+2,y0+1)); // pt 5 
        points.push_back(cv::Point(x0+1,y0+2)); // pt 6
        points.push_back(cv::Point(x0,y0+2)); // pt 7
        points.push_back(cv::Point(x0-1,y0+2)); // pt 8
        points.push_back(cv::Point(x0-2,y0+1)); // pt 9
        points.push_back(cv::Point(x0-2,y0)); // pt 10
        points.push_back(cv::Point(x0-2,y0-1)); // pt 11
        points.push_back(cv::Point(x0-1,y0-2)); // pt 12           
        return points;
    case 3:
        points.push_back(cv::Point(x0,y0-3)); // pt 1
        points.push_back(cv::Point(x0+1,y0-3)); // pt 2
        points.push_back(cv::Point(x0+2,y0-2)); // pt 3
        points.push_back(cv::Point(x0+3,y0-1)); // pt 4
        points.push_back(cv::Point(x0+3,y0)); // pt 5 
        points.push_back(cv::Point(x0+3,y0+1)); // pt 6
        points.push_back(cv::Point(x0+2,y0+2)); // pt 7
        points.push_back(cv::Point(x0+1,y0+3)); // pt 8
        points.push_back(cv::Point(x0,y0+3)); // pt 9
        points.push_back(cv::Point(x0-1,y0+3)); // pt 10
        points.push_back(cv::Point(x0-2,y0+2)); // pt 11
        points.push_back(cv::Point(x0-3,y0+1)); // pt 12
        points.push_back(cv::Point(x0-3,y0)); // pt 13
        points.push_back(cv::Point(x0-3,y0-1)); // pt 14
        points.push_back(cv::Point(x0-2,y0-2)); // pt 15
        points.push_back(cv::Point(x0-1,y0-3)); // pt 16
        return points;
    case 4:
        points.push_back(cv::Point(x0,y0-4)); // pt 1
        points.push_back(cv::Point(x0+1,y0-4)); // pt 2
        points.push_back(cv::Point(x0+2,y0-3)); // pt 3
        points.push_back(cv::Point(x0+3,y0-2)); // pt 4
        points.push_back(cv::Point(x0+4,y0-1)); // pt 5 
        points.push_back(cv::Point(x0+4,y0)); // pt 6
        points.push_back(cv::Point(x0+4,y0+1)); // pt 7
        points.push_back(cv::Point(x0+3,y0+2)); // pt 8
        points.push_back(cv::Point(x0+2,y0+3)); // pt 9
        points.push_back(cv::Point(x0+1,y0+4)); // pt 10
        points.push_back(cv::Point(x0,y0+4)); // pt 11
        points.push_back(cv::Point(x0-1,y0+4)); // pt 12
        points.push_back(cv::Point(x0-2,y0+3)); // pt 13
        points.push_back(cv::Point(x0-3,y0+2)); // pt 14
        points.push_back(cv::Point(x0-4,y0+1)); // pt 15
        points.push_back(cv::Point(x0-4,y0)); // pt 16
        points.push_back(cv::Point(x0-4,y0-1)); // pt 17
        points.push_back(cv::Point(x0-3,y0-2)); // pt 18
        points.push_back(cv::Point(x0-2,y0-3)); // pt 19
        points.push_back(cv::Point(x0-1,y0-4)); // pt 20
        return points;
    default:
        std::cerr<<"fetching points of undeclared circle radius"<<std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int getAngle(int ptIdx, int radius)
{
    switch(radius) {
    case 2:
        switch(ptIdx) {
        case 0: return 0;
        case 1: return 30;
        case 2: return 60;
        case 3: return 90;
        case 4: return 120;
        case 5: return 150;
        case 6: return 180;
        case 7: return 210;
        case 8: return 240;
        case 9: return 270;
        case 10: return 300;
        case 11: return 330;
        default:
            std::cerr<<"fetching angle for invalid point on circle radius 2"<<std::endl;
            std::exit(EXIT_FAILURE);
        }
        break;
    case 3:
        switch(ptIdx) {
        case 0: return 0;
        case 1: return 22;
        case 2: return 45;
        case 3: return 77;
        case 4: return 90;
        case 5: return 112;
        case 6: return 135;
        case 7: return 158;
        case 8: return 180;
        case 9: return 202;
        case 10: return 225;
        case 11: return 247;
        case 12: return 270;
        case 13: return 292;
        case 14: return 315;
        case 15: return 337;
        default:
            std::cerr<<"fetching angle for invalid point on circle radius 3"<<std::endl;
            std::exit(EXIT_FAILURE);
        }
        break;
    case 4:
        switch(ptIdx) {
        case 0: return 0;
        case 1: return 18;
        case 2: return 36;
        case 3: return 54;
        case 4: return 72;
        case 5: return 90;
        case 6: return 108;
        case 7: return 126;
        case 8: return 144;
        case 9: return 162;
        case 10: return 180;
        case 11: return 198;
        case 12: return 216;
        case 13: return 234;
        case 14: return 252;
        case 15: return 270;
        case 16: return 288;
        case 17: return 306;
        case 18: return 324;
        case 19: return 342;
        default:
            std::cerr<<"fetching angle for invalid point on circle radius 3"<<std::endl;
            std::exit(EXIT_FAILURE);
        }
        break;
    default:
        std::cerr<<"fetching angle for undeclared circle radius"<<std::endl;
        std::exit(EXIT_FAILURE);
    }

    return -1;
}
