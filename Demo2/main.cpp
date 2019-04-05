#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(){
    Mat src=imread("/Users/xinshichao/PersonalWork/C++Demo/Pictures/p1.jpeg",IMREAD_UNCHANGED);
    //Mat src=imread("/Users/xinshichao/PersonalWork/C++Demo/Pictures/p1.jpeg",IMREAD_GRAYSCALE);
    //Mat src=imread("/Users/xinshichao/PersonalWork/C++Demo/Pictures/p1.jpeg",IMREAD_COLOR);
    if(src.empty()){
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow("src",WINDOW_AUTOSIZE);
    //namedWindow("src",WINDOW_NORMAL);
    imshow("src",src);

    Mat src_gray;
    cvtColor(src,src_gray,COLOR_BGR2GRAY);
    namedWindow("src_gray",WINDOW_AUTOSIZE);
    imshow("src_gray",src_gray);

    imwrite("/Users/xinshichao/PersonalWork/C++Demo/Pictures/p2.jpeg",src_gray);

    waitKey(0);
    return 0;
}