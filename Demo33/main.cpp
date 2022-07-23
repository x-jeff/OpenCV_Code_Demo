#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int num_corners = 25;
int max_corners = 200;
const char* output_title = "ShiTomasi Detector";
void ShiTomasi_Demo(int, void*);
Mat src, gray_src;
RNG rng(12345);
int main(int argc, char** argv) {
    src = imread("../../Demo32/home.jpg");
    if (src.empty()) {
        printf("could not load image...\n");
        return -1;
    }
    namedWindow("input image", WINDOW_AUTOSIZE);
    imshow("input image", src);

    cvtColor(src, gray_src, COLOR_BGR2GRAY);
    namedWindow(output_title, WINDOW_AUTOSIZE);
    createTrackbar("Num Corners:", output_title, &num_corners, max_corners, ShiTomasi_Demo);
    ShiTomasi_Demo(0, 0);

    waitKey(0);
    return 0;
}

void ShiTomasi_Demo(int, void*) {
    if (num_corners < 5) {
        num_corners = 5;
    }
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarris = false;
    double k = 0.04;
    Mat resultImg = gray_src.clone();
    cvtColor(resultImg, resultImg, COLOR_GRAY2BGR);
    goodFeaturesToTrack(gray_src, corners, num_corners, qualityLevel, minDistance, Mat(), blockSize, useHarris, k);
    printf("Number of Detected Corners:  %d\n", corners.size());

    for (size_t t = 0; t < corners.size(); t++) {
        circle(resultImg, corners[t], 2, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8, 0);
    }
    imshow(output_title, resultImg);
}