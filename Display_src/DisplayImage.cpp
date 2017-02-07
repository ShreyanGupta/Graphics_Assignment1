#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <fstream>
using namespace std;

using namespace cv;

int main(int argc, char** argv)
{
    ifstream fin((string)argv[1]);
    int x, y;
    fin >> x >> y;
    cv::Mat final_image(x, y, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int i=0; i<x; ++i){
        for(int j=0; j<y; ++j){
            int r, g, b;
            fin >> r >> g >> b;
            cv::Vec3b color(r, g, b);
            final_image.at<cv::Vec3b>(cv::Point(i,j)) = color;
        }
    }

    cv::imwrite("image.jpg",final_image);
    cv::imshow("Display Image", final_image);
    cv::waitKey(5000);

    return 0;
}