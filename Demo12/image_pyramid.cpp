#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv){
    Mat src, dst1,dst2,dst3;
    src = imread("../../Demo1/p1.jpeg");
    //src = imread("C:/personal document/SegmentationAlgorithm/grabcut/GrabcutTest/record/frame1/c_Color.png");
    if (!src.data){
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);

    //上采样
    pyrUp(src, dst1, Size(src.cols * 2, src.rows * 2));
    imshow("dst1", dst1);
    //降采样
    pyrDown(src, dst2, Size(src.cols / 2, src.rows / 2));
    imshow("dst2", dst2);

    //DOG
    Mat src_gray, dst4,dog_img;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    GaussianBlur(src_gray, dst3, Size(3, 3), 0, 0);//sigma=0时，会根据Size()自动生成sigma
    GaussianBlur(dst3, dst4, Size(3, 3), 0,0);
    subtract(dst3, dst4, dog_img, Mat());
    normalize(dog_img, dog_img, 255, 0, NORM_MINMAX);//归一化显示，范围扩至0-255
    imshow("dog_img", dog_img);

    waitKey(0);
    return 0;
}