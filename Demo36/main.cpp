#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, char** argv) {
    Mat src = imread("../../Demo32/home.jpg", IMREAD_GRAYSCALE);
    if (src.empty()) {
        printf("could not load image...\n");
        return -1;
    }
    namedWindow("input image", WINDOW_AUTOSIZE);
    imshow("input image", src);

    int numFeatures = 400;
    Ptr<SIFT> detector = SIFT::create(numFeatures);
    vector<KeyPoint> keypoints;
    detector->detect(src, keypoints, Mat());
    printf("Total KeyPoints : %d\n", keypoints.size());

    Mat keypoint_img;
    drawKeypoints(src, keypoints, keypoint_img, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    namedWindow("SIFT KeyPoints", WINDOW_AUTOSIZE);
    imshow("SIFT KeyPoints", keypoint_img);

    waitKey(0);
    return 0;
}
