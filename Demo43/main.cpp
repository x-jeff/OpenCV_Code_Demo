#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, char** argv) {
    Mat img1 = imread("../../Demo42/box.png", IMREAD_GRAYSCALE);
    Mat img2 = imread("../../Demo42/box_in_scene.png", IMREAD_GRAYSCALE);
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

    vector<Point2f> obj;
    vector<Point2f> objInScene;
    for (size_t t = 0; t < goodMatches.size(); t++) {
        obj.push_back(keypoints_obj[goodMatches[t].queryIdx].pt);
        objInScene.push_back(keypoints_scene[goodMatches[t].trainIdx].pt);
    }
    Mat H = findHomography(obj, objInScene, RANSAC);

    vector<Point2f> obj_corners(4);
    vector<Point2f> scene_corners(4);
    obj_corners[0] = Point(0, 0);
    obj_corners[1] = Point(img1.cols, 0);
    obj_corners[2] = Point(img1.cols, img1.rows);
    obj_corners[3] = Point(0, img1.rows);
    perspectiveTransform(obj_corners, scene_corners, H);

    // draw line
    line(matchesImg, scene_corners[0] + Point2f(img1.cols, 0), scene_corners[1] + Point2f(img1.cols, 0), Scalar(0, 0, 255), 2, 8, 0);
    line(matchesImg, scene_corners[1] + Point2f(img1.cols, 0), scene_corners[2] + Point2f(img1.cols, 0), Scalar(0, 0, 255), 2, 8, 0);
    line(matchesImg, scene_corners[2] + Point2f(img1.cols, 0), scene_corners[3] + Point2f(img1.cols, 0), Scalar(0, 0, 255), 2, 8, 0);
    line(matchesImg, scene_corners[3] + Point2f(img1.cols, 0), scene_corners[0] + Point2f(img1.cols, 0), Scalar(0, 0, 255), 2, 8, 0);
    
    Mat dst;
    cvtColor(img2, dst, COLOR_GRAY2BGR);
    line(dst, scene_corners[0], scene_corners[1] , Scalar(0, 0, 255), 2, 8, 0);
    line(dst, scene_corners[1], scene_corners[2] , Scalar(0, 0, 255), 2, 8, 0);
    line(dst, scene_corners[2] , scene_corners[3] , Scalar(0, 0, 255), 2, 8, 0);
    line(dst, scene_corners[3] , scene_corners[0] , Scalar(0, 0, 255), 2, 8, 0);

    imshow("find known object demo", matchesImg);
    imshow("Draw object", dst);

    waitKey(0);
    return 0;
}
