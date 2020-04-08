#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;
using namespace std;
char winTile[] = "output";
int main(int argc, char** argv){
    Mat src,src1,dst,dst1;
    src = imread("p3.png", -1);
    if (!src.data){
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);

//    Mat kernel = getStructuringElement(MORPH_RECT, Size(70, 70), Point(-1, -1));
//    morphologyEx(src, dst, MORPH_OPEN, kernel);
//    namedWindow("open", WINDOW_AUTOSIZE);
//    imshow("open", dst);

//    src1 = imread("p3.png", -1);
//    Mat kernel1 = getStructuringElement(MORPH_RECT, Size(50, 50), Point(-1, -1));
//    morphologyEx(src1, dst1, MORPH_CLOSE, kernel1);
//    namedWindow("close", WINDOW_AUTOSIZE);
//    imshow("src",src1);
//    imshow("close", dst1);

//    Mat src2, dst2;
//    src2 = imread("p1.png", -1);
//    Mat kernel2 = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
//    morphologyEx(src2, dst2, MORPH_GRADIENT, kernel2);
//    namedWindow("gradient", WINDOW_AUTOSIZE);
//    imshow("src",src2);
//    imshow("gradient", dst2);

//    Mat dst3;
//    Mat kernel3 = getStructuringElement(MORPH_RECT, Size(70, 70), Point(-1, -1));
//    morphologyEx(src, dst3, MORPH_TOPHAT, kernel3);
//    namedWindow("tophat", WINDOW_AUTOSIZE);
//    imshow("tophat", dst3);


    Mat kernel = getStructuringElement(MORPH_RECT, Size(50, 50), Point(-1, -1));
    morphologyEx(src, dst, MORPH_BLACKHAT, kernel);
    namedWindow("blackhat", WINDOW_AUTOSIZE);
    imshow("blackhat", dst);
    waitKey(0);
    return 0;
}