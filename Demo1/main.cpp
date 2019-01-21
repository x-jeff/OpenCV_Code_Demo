#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() {
    Mat p1=imread("/Users/xinshichao/PersonalWork/C++Demo/Pictures/p1.jpeg");
    if(!p1.data){
        printf("could not find the image...\n");
    }
    namedWindow("output",WINDOW_AUTOSIZE);
    imshow("output",p1);
    waitKey(0);
    return 0;
}