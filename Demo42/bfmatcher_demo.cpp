#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, char** argv) {
    Mat img1 = imread("box.png", IMREAD_GRAYSCALE);
    Mat img2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);
    if (!img1.data || !img2.data) {
        return -1;
    }
    imshow("image1", img1);
    imshow("image2", img2);

    int minHessian = 400;
    Ptr<SURF> detector = SURF::create(minHessian);
    
    vector<KeyPoint> keypoints_1;
    vector<KeyPoint> keypoints_2;
    Mat descriptor_1, descriptor_2;
    detector->detectAndCompute(img1, Mat(), keypoints_1, descriptor_1);
    detector->detectAndCompute(img2, Mat(), keypoints_2, descriptor_2);

    BFMatcher matcher(NORM_L2);
    vector<DMatch> matches;
    matcher.match(descriptor_1, descriptor_2, matches);

    Mat matchesImg;
    drawMatches(img1, keypoints_1, img2, keypoints_2, matches, matchesImg);
    imshow("Descriptor Demo", matchesImg);

    waitKey(0);
    return 0;
}
