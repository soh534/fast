#include "FastDetector.h"

#include <opencv2/core/core.hpp>

#include <vector>

#define DARKER 1
#define SIMILAR 2
#define BRIGHTER 3

FastDetector::FastDetector() {}

cv::Mat FastDetector::greyScale(cv::Mat image)
{
    // average out rgb pixel intensity
    for(int y=0; y<image.rows; y++) {
        cv::Vec3b* ptr = image.ptr<cv::Vec3b>(y);
        for(int x=0; x<image.cols; x++) {
            int avg = (ptr[x][0]+ptr[x][1]+ptr[x][2])*0.33;
            ptr[x] = cv::Vec3b(avg,avg,avg);
        }
    }
    return image;
}

int FastDetector::pixelAt(cv::Mat& image, int x, int y)
{
    // quick function to grab pixel intensity from coordinates
    int ret=-1;
    cv::Vec3b* ptr = image.ptr<cv::Vec3b>(y);
    ret = ptr[x][0];
    return ret;
}

CircleData FastDetector::exploreCircle(cv::Mat& image, int x, int y, int r)
{
    int centerPix = pixelAt(image,x,y);
    std::vector<cv::Point> circ = getCircle(x, y, r);
    int szCirc = (int)circ.size();

    int dkconsec=0, brconsec=0, consec=0;
    int angle_dkb=-1, angle_dke=-1;
    int angle_brb=-1, angle_bre=-1;
    int angle=-1;

    unsigned int intensity=0;

    // march around the circle and look for longest consecutive
    // brighter or darker pixels which signify a corner
    for(int i=0; i<2*szCirc; i++) {
        int cx = circ[i%szCirc].x;
        int cy = circ[i%szCirc].y;
        int piPix = pixelAt(image, cx, cy);
        if (centerPix > piPix + THRESHOLD) {
            if (i==0) {
                angle=getAngle(i%szCirc,r);
            } else if (intensity == DARKER) {
                consec++;
            } else {
                if (intensity == BRIGHTER && consec > brconsec) {
                    angle_bre = getAngle(i%szCirc,r);
                    angle_brb = angle;
                    brconsec = consec;
                }
                angle=getAngle(i%szCirc,r);
                consec=1;
            }
            intensity = DARKER;
        } else if (centerPix < piPix - THRESHOLD) {
            if (i==0) {
                angle=getAngle(i%szCirc,r);
            } else if (intensity == BRIGHTER) {
                consec++;
            } else {
                if (intensity == DARKER && consec > dkconsec) {
                    angle_dke = getAngle(i%szCirc,r);
                    angle_dkb = angle;
                    dkconsec = consec;
                }
                angle=getAngle(i%szCirc,r);
                consec=1;
            }
            intensity = BRIGHTER;
        } else {
            if (intensity == BRIGHTER) {
                if (consec > brconsec) {
                    angle_bre = getAngle(i%szCirc,r);
                    angle_brb = angle;
                    brconsec = consec;
                }
            } else if (intensity == DARKER) {
                if (consec > dkconsec) {
                    angle_dke = getAngle(i%szCirc,r);
                    angle_dkb = angle;
                    dkconsec = consec;
                }
            }
            intensity = SIMILAR;
        }
    }
    
    CircleData cd(angle_dkb, angle_dke, angle_brb, angle_bre, dkconsec, brconsec);
    return cd;
}

int FastDetector::getOrientation(CircleData cd)
{
    // determine which angle the consecutive darkness
    // or brightness is facing
    int orientation = -1;
    if (cd.dkConsec > cd.brConsec) {
        orientation = (cd.dkBeginAngle + cd.dkEndAngle) / 2;
    } else {
        orientation = (cd.brBeginAngle + cd.brEndAngle) / 2;
    }
    return orientation;
}

bool FastDetector::crossCheck(cv::Mat& image, int x, int y)
{
    // preliminary check for a corner to speed things up.
    // top, bottom, left, and right pixels must have 
    // atleast 3 brighter or darker intensity for there
    // to exist consecutive brightness or darkness
    int centerPix = pixelAt(image,x,y);
    int p1Pix = pixelAt(image,x,y-3);
    int p5Pix = pixelAt(image,x+3,y);
    int p9Pix = pixelAt(image,x,y+3);
    int p13Pix = pixelAt(image,x-3,y);

    int dkconsec=0, brconsec=0;
    if (centerPix > p1Pix + THRESHOLD) dkconsec++; // top point
    else if (centerPix < p1Pix - THRESHOLD) brconsec++;

    if (centerPix > p5Pix + THRESHOLD) dkconsec++; // right point
    else if (centerPix < p5Pix - THRESHOLD) brconsec++;

    if (centerPix > p9Pix + THRESHOLD) dkconsec++; // bottom point
    else if (centerPix < p9Pix - THRESHOLD) brconsec++;

    if (centerPix > p13Pix + THRESHOLD) dkconsec++; // left point
    else if (centerPix < p13Pix - THRESHOLD) brconsec++;

    if (dkconsec==3 || brconsec==3) return true;
    else return false;
}

bool FastDetector::defaultCheck(cv::Mat& image, int x, int y)
{
    // default FAST(features from accelerated segment test) algorithm
    CircleData cd = exploreCircle(image, x, y, 3);
    int dkconsec = cd.dkConsec;
    int brconsec = cd.brConsec;
    if (dkconsec>11 || brconsec>11) {
        return true;
    }
    return false;
}

bool FastDetector::extendedCheck(cv::Mat& image, int x, int y)
{
    // enhancement proposed in:
    // www.vision.cs.chubu.ac.jp/flabresearcharchive/bachelor/B12/Abstract/hasegawa.pdf

    // look at the orientations of corners
    // noise detected as corners tend to have
    // orientations not in similar directions
    // for circle cirumference of 2, 3, and 4
    CircleData cd2 = exploreCircle(image, x, y, 2);
    CircleData cd3 = exploreCircle(image, x, y, 3);
    CircleData cd4 = exploreCircle(image, x, y, 4);

    int orientation2 = getOrientation(cd2);
    int orientation3 = getOrientation(cd3);
    int orientation4 = getOrientation(cd4);

    int theta23 = abs(orientation2-orientation3);
    int theta34 = abs(orientation3-orientation4);

    if (theta23 < ANGULAR_THRESHOLD && theta34 < ANGULAR_THRESHOLD) {
        return true;
    } else {
        return false;
    }
}

void FastDetector::detect(cv::Mat image)
{
    // main caller - three detection levels
    image = greyScale(image);
    for(int y=5; y<image.rows-5; y++) {
        for(int x=5; x<image.cols-5; x++) {
            if (crossCheck(image,x,y)) {
                if (defaultCheck(image,x,y)) {
                    if (extendedCheck(image,x,y)) {
                        detectedPoints.push_back(cv::Point(x,y));
                    }
                }
            }
        }
    }
}

void FastDetector::express(cv::Mat& image)
{
    // mark the detected corner points
    int sz_detectedPoints = (int)detectedPoints.size();
    for(int i=0; i<sz_detectedPoints; i++) {
        circle(image, detectedPoints[i], 1, cv::Scalar(0,0,255), 1, 8, 0);
    }
}
