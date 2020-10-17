#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    Mat src;
    src = imread("../../Demo1/p1.jpeg", IMREAD_UNCHANGED);
    if (!src.data) {
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);

    Mat robert1 = (Mat_<char>(2, 2) << 1, 0, 0, -1);
    Mat robert2 = (Mat_<char>(2, 2) << 0, 1, -1, 0);
    Mat robert1_dst, robert2_dst;
    filter2D(src, robert1_dst, -1, robert1, Point(-1, -1));
    filter2D(src, robert2_dst, -1, robert2, Point(-1, -1));
    imshow("robert1_dst", robert1_dst);
    imshow("robert2_dst", robert2_dst);

    Mat sobel1 = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Mat sobel2 = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    Mat sobel1_dst, sobel2_dst;
    filter2D(src, sobel1_dst, -1, sobel1, Point(-1, -1));
    filter2D(src, sobel2_dst, -1, sobel2, Point(-1, -1));
    imshow("sobel1_dst", sobel1_dst);
    imshow("sobel2_dst", sobel2_dst);

    Mat la = (Mat_<char>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
    Mat la_dst;
    filter2D(src, la_dst, -1, la, Point(-1, -1));
    imshow("la_dst", la_dst);
    waitKey(0);

    int c = 0;
    int index = 0;
    int ksize = 3;
    Mat dst;
    while (true) {
        c = waitKey(500);
        if ((char) c == 27) {//27代表的是键盘上的ESC
            break;
        }
        ksize = 4 + (index % 5) * 2 + 1;
        //Mat::ones默认是单通道的，像素值都是1。
        //对于单通道图，除数/ (float)(ksize,ksize)，第一个ksize不起作用，就相当于是每个像素值除以(float)ksize
        Mat kernel = Mat::ones(Size(ksize, ksize), CV_32F) / (float)(ksize,ksize);
        filter2D(src, dst, -1, kernel, Point(-1, -1));
        index++;
        imshow("dst", dst);
    }

    waitKey(0);
    return 0;
}