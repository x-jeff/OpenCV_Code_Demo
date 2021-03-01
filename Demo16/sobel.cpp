#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    Mat src, dst;
    src = imread("../../Demo1/p1.jpeg", IMREAD_UNCHANGED);
    if (src.empty()) {
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);

    GaussianBlur(src, dst, Size(3, 3), 0, 0);
    Mat dst_gray;
    cvtColor(dst, dst_gray, COLOR_BGR2GRAY);
    imshow("dst_gray", dst_gray);

    Mat xgrad, ygrad, xygrad1, xygrad;
    Sobel(dst_gray, xgrad, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    Sobel(dst_gray, ygrad, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(xgrad, xgrad);//对原图像的像素值直接取绝对值（因为原图像的像素值可能是负数，负数离0越远，也表示差距很大，不用绝对值的话就会损失一些信息）
    convertScaleAbs(ygrad, ygrad);
    imshow("xgrad", xgrad);
    imshow("ygrad", ygrad);

    //addWeighted(xgrad, 0.5, ygrad, 0.5, 0, xygrad1, -1);
    //imshow("addweighted_xygrad", xygrad1);

    //add(xgrad, ygrad, xygrad1);
    //imshow("add_xygrad", xygrad1);

    xygrad = Mat(xgrad.size(), xgrad.type());
    printf("type : %d\n", xgrad.type());//输出为0，就是CV_8U的类型
    int width = xgrad.cols;
    int height = ygrad.rows;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            xygrad.at<uchar>(row, col) = /*0.5**/
                    xgrad.at<uchar>(row, col) + /*0.5**/ygrad.at<uchar>(row, col);//因为是CV_8U类型的图像，所以这里是uchar
        }
    }//和add结果不一样//各自乘上权重之后，和addWeighted结果一样
    imshow("xygrad", xygrad);

    Mat Scharr_x_dst, Scharr_y_dst, Scharr_xy_dst;
    Scharr(dst_gray, Scharr_x_dst, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
    Scharr(dst_gray, Scharr_y_dst, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(Scharr_x_dst, Scharr_x_dst);
    convertScaleAbs(Scharr_y_dst, Scharr_y_dst);
    imshow("Scharr_x_dst", Scharr_x_dst);
    imshow("Scharr_y_dst", Scharr_y_dst);
    addWeighted(Scharr_x_dst, 0.5, Scharr_y_dst, 0.5, 0, Scharr_xy_dst, -1);
    imshow("Scharr_xy_dst", Scharr_xy_dst);


    waitKey(0);
    return 0;
}