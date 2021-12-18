#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;
using namespace cv;

int main() {
    Mat src = imread("../1.png", IMREAD_GRAYSCALE);
    if (src.empty()) {
        cout << "empty src img" << endl;
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);
    waitKey(0);

    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;
    findContours(src, contours, hierachy, RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));
    for (size_t i = 0; i < hierachy.size(); i++) {
        cout << i << " : " << hierachy[i][0] << " " << hierachy[i][1] << hierachy[i][2] << hierachy[i][3] << endl;
    }


    Mat dst = Mat::zeros(src.size(), CV_8UC3);
    RNG rng(12345);
    //Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    //drawContours(dst, contours, -1, color, -1, 8, hierachy, 10, Point(0, 0));
    for (size_t i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(dst, contours, i, color, 2, 8, hierachy, 3, Point(0, 0));
        putText(dst, to_string(i), contours[i][0], FONT_HERSHEY_COMPLEX, 1.0, color, 1, 8);
    }
    imshow("dst", dst);
    waitKey(0);

    return 0;
}
