#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <fstream>
using namespace std;

using namespace cv;

int main(int argc, char** argv )
{
    ifstream fin("../matrix.txt");
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

    cv::imwrite("noob_ion_pit_jayega.jpg",final_image);
    cv::imshow("Display", final_image);
    cv::waitKey(10000);

    // if ( argc != 2 )
    // {
    //     printf("usage: DisplayImage.out <Image_Path>\n");
    //     return -1;
    // }

    // Mat image;
    // image = imread( argv[1], 1 );

    // if ( !image.data )
    // {
    //     printf("No image data \n");
    //     return -1;
    // }
    // namedWindow("Display Image", WINDOW_AUTOSIZE );
    // imshow("Display Image", image);

    // waitKey(0);

    return 0;
}