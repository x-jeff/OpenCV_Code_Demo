#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat img1 = imread("../../Demo42/box.png", IMREAD_GRAYSCALE);
	Mat img2 = imread("../../Demo42/box_in_scene.png", IMREAD_GRAYSCALE);
	if (img1.empty() || img2.empty()) {
		printf("could not load images...\n");
		return -1;
	}
	imshow("box image", img1);
	imshow("scene image", img2);

	
	//extract akaze features
	Ptr<AKAZE> detector = AKAZE::create();
	vector<KeyPoint> keypoints_obj;
	vector<KeyPoint> keypoints_scene;
	Mat descriptor_obj, descriptor_scene;
	double t1 = getTickCount();
	detector->detectAndCompute(img1, Mat(), keypoints_obj, descriptor_obj);
	detector->detectAndCompute(img2, Mat(), keypoints_scene, descriptor_scene);
	double t2 = getTickCount();
	double tkaze = 1000 * (t2 - t1) / getTickFrequency();
	printf("AKAZE Time consume(ms) : %f\n", tkaze);
	
	//matching
	FlannBasedMatcher matcher(new flann::LshIndexParams(20, 10, 2));
	//FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptor_obj, descriptor_scene, matches);
	
	//draw matches(key points)
	Mat akazeMatchesImg;
	drawMatches(img1, keypoints_obj, img2, keypoints_scene, matches, akazeMatchesImg);
	imshow("akaze match result", akazeMatchesImg);
	/*
	vector<DMatch> goodMatches;
	double minDist = 100000, maxDist = 0;
	for (int i = 0; i < descriptor_obj.rows; i++) {
		double dist = matches[i].distance;
		if (dist < minDist) {
			minDist = dist;
		}
		if (dist > maxDist) {
			maxDist = dist;
		}
	}
	printf("min distance : %f", minDist);

	for (int i = 0; i < descriptor_obj.rows; i++) {
		double dist = matches[i].distance;
		if (dist < max( 1.5*minDist, 0.02)) {
			goodMatches.push_back(matches[i]);
		}
	}

	drawMatches(img1, keypoints_obj, img2, keypoints_scene, goodMatches, akazeMatchesImg, Scalar::all(-1), 
		Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("good match result", akazeMatchesImg);
	*/
	waitKey(0);
	return 0;
}