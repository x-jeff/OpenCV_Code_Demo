#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    char input_win[] = "input image";
    char watershed_win[] = "watershed segmentation demo";
    Mat src = imread("../cards.png");
    if (src.empty()) {
        printf("could not load image...\n");
        return -1;
    }
    namedWindow(input_win, WINDOW_AUTOSIZE);
    imshow(input_win, src);
    //waitKey(0);

    //change background
    /*
    Mat mask;
    inRange(src, Scalar(255, 255, 255), Scalar(255, 255, 255), mask);
    src.setTo(Scalar(0, 0, 0), mask);
    */
    for (int row = 0; row < src.rows; row++) {
        for (int col = 0; col < src.cols; col++) {
            if (src.at<Vec3b>(row, col) == Vec3b(255, 255, 255)) {
                src.at<Vec3b>(row, col)[0] = 0;
                src.at<Vec3b>(row, col)[1] = 0;
                src.at<Vec3b>(row, col)[2] = 0;
            }
        }
    }
    namedWindow("black background", WINDOW_AUTOSIZE);
    imshow("black background", src);
    //waitKey(0);

    //sharpen
    Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
    Mat imgLaplacian;
    Mat sharpenImg;
    filter2D(src, imgLaplacian, CV_32F, kernel);
    src.convertTo(sharpenImg, CV_32F);
    Mat resultImg = sharpenImg - imgLaplacian;
    resultImg.convertTo(resultImg, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
    imshow("sharpen image", resultImg);
    //waitKey(0);

    //convert to binary
    Mat binaryImg;
    cvtColor(resultImg, binaryImg, COLOR_BGR2GRAY);
    threshold(binaryImg, binaryImg, 40, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("binary image", binaryImg);
    //waitKey(0);

    Mat distImg;
    distanceTransform(binaryImg, distImg, DIST_L2, 3);
    normalize(distImg, distImg, 0, 1, NORM_MINMAX);
    imshow("distance result", distImg);
    //waitKey(0);

    //binary again
    threshold(distImg, distImg, .4, 1, THRESH_BINARY);
    //imshow("distance binary image", distImg);
    //waitKey(0);
    Mat k1 = Mat::ones(3, 3, CV_8U);
    dilate(distImg, distImg, k1);
    //erode(distImg, distImg, k1);
    imshow("distance binary image", distImg);
    //waitKey(0);

    //markers
    Mat dist_8u;
    distImg.convertTo(dist_8u, CV_8U);
    vector<vector<Point>> contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    //create markers
    Mat markers = Mat::zeros(src.size(), CV_32S);
    for (size_t i = 0; i < contours.size(); i++) {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
    }
    //draw the background markers
    circle(markers, Point(5, 5), 3, Scalar(255), -1);
    Mat markers8u;
    markers.convertTo(markers8u, CV_8U, 10);
    imshow("markers", markers8u);
    //waitKey(0);

    //perform watershed
    watershed(src, markers);
    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);
    imshow("watershed image", mark);

    //generate random color
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++) {
        int r = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int b = theRNG().uniform(0, 256);
        colors.push_back(Vec3b((uchar) b, (uchar) g, (uchar) r));
    }

    //fill with color and display final result
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
    for (int row = 0; row < markers.rows; row++) {
        for (int col = 0; col < markers.cols; col++) {
            int index = markers.at<int>(row, col);
            if (index > 0 && index <= static_cast<int>(contours.size())) {
                dst.at<Vec3b>(row, col) = colors[index - 1];
            }
        }
    }
    imshow("Final Result", dst);

    waitKey(0);
    return 0;
}