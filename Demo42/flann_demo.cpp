#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, char** argv) {
    Mat img1 = imread("box.png", IMREAD_GRAYSCALE);
    Mat img2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);
    if (!img1.data || !img2.data) {
        return -1;
    }
    imshow("object image", img1);
    imshow("object in scene", img2);

    // surf featurs extraction
    int minHessian = 400;
    Ptr<SURF> detector = SURF::create(minHessian);
    vector<KeyPoint> keypoints_obj;
    vector<KeyPoint> keypoints_scene;
    Mat descriptor_obj, descriptor_scene;
    detector->detectAndCompute(img1, Mat(), keypoints_obj, descriptor_obj);
    detector->detectAndCompute(img2, Mat(), keypoints_scene, descriptor_scene);

    // matching
    FlannBasedMatcher matcher;
    vector<DMatch> matches;
    matcher.match(descriptor_obj, descriptor_scene, matches);

    // find good matched points
    double minDist = 1000;
    double maxDist = 0;
    for (int i = 0; i < descriptor_obj.rows; i++) {
        double dist = matches[i].distance;
        if (dist > maxDist) {
            maxDist = dist;
        }
        if (dist < minDist) {
            minDist = dist;
        }
    }
    printf("max distance : %f\n", maxDist);
    printf("min distance : %f\n", minDist);
    vector<DMatch> goodMatches;
    for (int i = 0; i < descriptor_obj.rows; i++) {
        double dist = matches[i].distance;
        if (dist < max(3 * minDist, 0.02)) {
            goodMatches.push_back(matches[i]);
        }
    }
    
    Mat matchesImg;
    drawMatches(img1, keypoints_obj, img2, keypoints_scene, goodMatches, matchesImg, Scalar::all(-1),
        Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS
    );
    imshow("Flann Matching Result", matchesImg);

    waitKey(0);
    return 0;
}
