#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv){
    Mat src;

    //读入原始图像
    src = imread("p2.png");
    if (src.empty()){
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow("src",WINDOW_AUTOSIZE);
    imshow("src",src);

    //将原始图像转换为灰度图像
    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    imshow("src_gray",src_gray);

    //将灰度图像转换为二值图像
    Mat src_binary;
    adaptiveThreshold(~src_gray, src_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
    imshow("src_binary",src_binary);

    //定义矩形结构元素
    Mat kernel=getStructuringElement(MORPH_RECT,Size(3,3),Point(-1,-1));

    //开操作
    Mat temp,dst;
    //erode(src_binary, temp, kernel);
    //dilate(temp, dst, kernel);
    morphologyEx(src_binary, dst, MORPH_OPEN, kernel);
    imshow("dst",~dst);

    waitKey(0);
    return 0;
}