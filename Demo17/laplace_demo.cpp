#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
char output_title[] = "Laplace_Image";

int main(int argc, char **argv) {
    Mat src, dst;
    src = imread("../../Demo1/p1.jpeg");
    if (!src.data) {
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);

    Mat gray_src, l_dst;
    GaussianBlur(src, dst, Size(3, 3), 0, 0);
    cvtColor(dst, gray_src, COLOR_BGR2GRAY);
    Laplacian(gray_src, l_dst, CV_16S, 3);
    convertScaleAbs(l_dst, l_dst);

    //拉普拉斯算子得到的结果噪声还是很大，进一步处理：
    threshold(l_dst, l_dst, 0, 255, THRESH_OTSU | THRESH_BINARY);
    imshow(output_title, l_dst);


    waitKey(0);
    return 0;
}