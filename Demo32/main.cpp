#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
Mat src, gray_src;
int thresh = 130;
int max_count = 255;
const char *output_title = "HarrisCornerDetection Result";

void Harris_Demo(int, void *);

int main(int argc, char **argv) {

    src = imread("../home.jpg");
    if (src.empty()) {
        printf("could not load image...\n");
        return -1;
    }
    namedWindow("input image", WINDOW_AUTOSIZE);
    imshow("input image", src);

    namedWindow(output_title, WINDOW_AUTOSIZE);
    cvtColor(src, gray_src, COLOR_BGR2GRAY);
    createTrackbar("Threshold:", output_title, &thresh, max_count, Harris_Demo);
    Harris_Demo(0, 0);

    waitKey(0);
    return 0;
}

void Harris_Demo(int, void *) {
    Mat dst, norm_dst, normScaleDst;
    dst = Mat::zeros(gray_src.size(), CV_32FC1);

    int blockSize = 2;
    int ksize = 3;
    double k = 0.04;
    cornerHarris(gray_src, dst, blockSize, ksize, k, BORDER_DEFAULT);
    normalize(dst, norm_dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(norm_dst, normScaleDst);

    Mat resultImg = src.clone();
    for (int row = 0; row < resultImg.rows; row++) {
        uchar *currentRow = normScaleDst.ptr(row);
        for (int col = 0; col < resultImg.cols; col++) {
            int value = (int) *currentRow;
            if (value > thresh) {
                circle(resultImg, Point(col, row), 2, Scalar(0, 0, 255), 2, 8, 0);
            }
            currentRow++;
        }
    }

    imshow(output_title, resultImg);
}