#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    Mat src, dst;
    src = imread("../circle.jpeg");
    if (!src.data) {
        printf("could not load image...\n");
        return -1;
    }
    char INPUT_TITLE[] = "input image";
    char OUTPUT_TITLE[] = "hough circle demo";
    namedWindow(INPUT_TITLE, WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_TITLE, WINDOW_AUTOSIZE);
    imshow(INPUT_TITLE, src);

    Mat moutput;
    medianBlur(src, moutput, 3);//此处也可以尝试高斯模糊
    cvtColor(moutput, moutput, COLOR_BGR2GRAY);

    vector<Vec3f> pcircles;
    HoughCircles(moutput, pcircles, HOUGH_GRADIENT, 1, 10, 100, 30, 5, 50);
    src.copyTo(dst);
    for (size_t i = 0; i < pcircles.size(); i++) {
        Vec3f cc = pcircles[i];
        circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(0, 0, 255), 2, LINE_AA);
        circle(dst, Point(cc[0], cc[1]), 1, Scalar(198, 23, 155), 2, LINE_AA);//顺便标注下圆心的位置
    }
    imshow(OUTPUT_TITLE, dst);

    waitKey(0);
    return 0;
}