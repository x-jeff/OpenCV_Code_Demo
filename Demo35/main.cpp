#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int max_corners = 20;
int max_count = 50;
Mat src, gray_src;
const char* output_title = "SubPixel Result";
void SubPixel_Demo(int, void*);
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
    createTrackbar("Corners:", output_title, &max_corners, max_count, SubPixel_Demo);
    SubPixel_Demo(0, 0);

    waitKey(0);
    return 0;
}

void SubPixel_Demo(int, void*) {
    if (max_corners < 5) {
        max_corners = 5;
    }
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    double k = 0.04;
    goodFeaturesToTrack(gray_src, corners, max_corners, qualityLevel, minDistance, Mat(), blockSize, false, k);
    cout << "number of corners: " << corners.size() << endl;
    Mat resultImg = src.clone();
    for (size_t t = 0; t < corners.size(); t++) {
        circle(resultImg, corners[t], 2, Scalar(0, 0, 255), 2, 8, 0);
    }
    imshow(output_title, resultImg);
    Size winSize = Size(5, 5);
    Size zerozone = Size(-1, -1);
    TermCriteria tc = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);
    cornerSubPix(gray_src, corners, winSize, zerozone, tc);

    for (size_t t = 0; t < corners.size(); t++) {
        cout << (t + 1) << " .point[x, y] = " << corners[t].x << " , " << corners[t].y << endl;
    }
    return;
}
