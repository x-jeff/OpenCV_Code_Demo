#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat src=imread("../../Demo1/p1.jpeg");
    if(src.empty())
    {
        cout<<"could not find the image..."<<endl;
        return -1;
    }
    namedWindow("src",WINDOW_AUTOSIZE);
    imshow("src",src);

    Mat resize_src;
    //resize(src,resize_src,Size(300,100));
    resize(src,resize_src,Size(0,0),0.3,0.1);
    imshow("resize_src",resize_src);

    waitKey(0);
    return 0;
}