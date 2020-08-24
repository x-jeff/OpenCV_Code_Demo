#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
Mat src, dst, src_gray;
int threshold_value = 127;
int threshold_max = 255;
int type_value = 2;
int type_max = 4;
const char *output_title = "binary image";

void threshold_demo(int, void *);

int main(int argc, char **argv) {
    src = imread("../../Demo1/p1.jpeg");
    if (!src.data) {
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow(output_title, WINDOW_AUTOSIZE);
    createTrackbar("threshold", output_title, &threshold_value, threshold_max, threshold_demo);
    createTrackbar("type", output_title, &type_value, type_max, threshold_demo);
    threshold_demo(0, 0);
    waitKey(0);
    return 0;
}

void threshold_demo(int, void *) {
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    threshold(src, dst, threshold_value, threshold_max, type_value);
    //threshold(src_gray, dst, threshold_value, threshold_max, type_value);
    //threshold(src_gray, dst, 0,255, THRESH_OTSU | type_value);
    //threshold(src_gray, dst, 0,255,type_value | THRESH_OTSU);
    imshow(output_title, dst);
}