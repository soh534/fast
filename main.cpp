#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "FastDetector.h" // fast detector implementation

int main(int argc, char* argv[])
{
    if (argc!=2) {
        std::cout<<"Usage: ./fastdetector file.jpg"<<std::endl;
        return -1;
    }

    cv::Mat image_base, image_mark;
    image_base = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    image_mark = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if (!image_base.data) {
        std::cout<<"could not open or find image"<<std::endl;
        return -1;
    }
    
    FastDetector fd;
    fd.detect(image_mark);
    fd.express(image_base);

    cv::namedWindow("Processed window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Processed window", image_base);

    cv::waitKey(0);
    return 0;
}
