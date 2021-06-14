#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    Mat src, src_gray, dst, edge_output;
    src = imread("../../Demo1/p1.jpeg");
    if (!src.data) {
        printf("could not load image...\n");
        return -1;
    }

    char INPUT_TITLE[] = "input image";
    char OUTPUT_TITLE[] = "hough-line-detection";
    namedWindow(INPUT_TITLE, WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_TITLE, WINDOW_AUTOSIZE);
    imshow(INPUT_TITLE, src);

    // extract edge
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);
    Canny(src_gray, edge_output, 150, 200);
    cvtColor(edge_output, dst, COLOR_GRAY2BGR);
    imshow("edge image", edge_output);

    /*
    vector<Vec2f> lines;
    //HoughLines无法限定直线的长度，除非自行添加限制，否则会显示整条直线
    HoughLines(edge_output, lines, 1, CV_PI / 180, 100, 0, 0);
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        //经过点pt1和点pt2的直线，过点(x0,y0)，且垂直于位置向量rho
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(dst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
    }
    */

    vector<Vec4f> plines;
    HoughLinesP(edge_output, plines, 1, CV_PI / 180.0, 10, 5, 0);
    Scalar color = Scalar(0, 0, 255);
    for (size_t i = 0; i < plines.size(); i++) {
        Vec4f hline = plines[i];
        line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, LINE_AA);
    }

    imshow(OUTPUT_TITLE, dst);
    waitKey(0);
    return 0;
}