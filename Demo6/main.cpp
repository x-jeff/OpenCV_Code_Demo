#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc,char**argv)
{
    Mat src1, src2, dst;
    src1 = imread("..//6x1.jpeg");
    src2 = imread("..//6x2.jpeg");
    namedWindow("src1", WINDOW_AUTOSIZE);
    namedWindow("src2", WINDOW_AUTOSIZE);
    imshow("src1", src1);
    imshow("src2", src2);

    if (src1.rows == src2.rows&&src1.cols == src2.cols&&src1.type() == src2.type()){//先判定两幅图像的大小和类型是否相同
        addWeighted(src1, 0.5, src2, 0.5, 0, dst, -1);
        namedWindow("dst", WINDOW_AUTOSIZE);
        imshow("dst", dst);
    }
    else{
        printf("size is not same...\n");
        return -1;
    }

    //直接两幅图像的像素值相加：add(src1,src2,dst,Mat());//Mat()为mask,这里为空mask
    //直接两幅图像的像素值相乘：multiply(src1, src2, dst);

    waitKey(0);
    return 0;
}