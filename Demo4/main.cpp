#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
    Mat src;
    src=imread("../../Demo1/p1.jpeg");
    if(!src.data)
    {
        cout<<"can not find the image...\n"<<endl;
        return -1;
    }

    Mat dst;//先定义一张新的图像
    dst=Mat(src.size(), src.type());//和src图像相同的大小和类型
    dst = Scalar(127, 0, 255);//每个像素点的RGB都是(127，0，255)

    Mat dst2,dst3;
    dst2 = src.clone();//克隆一张一模一样的图片，属于完全复制
    src.copyTo(dst3);//也是克隆，等同于src.clone()，属于完全复制

    const uchar* p = dst3.ptr<uchar>(0);//第一行首个像素点的像素值
    const auto i = dst3.ptr<uchar>(0)[0];
    const int* q = dst3.ptr<int>(0);
    printf("the fist row pixel is %d \n", *p);
    printf("the fist pixel is %d \n", i);//*p=i=94
    cout << *q << endl;//*q=1515541342

    int col = dst3.cols;
    int row = dst3.rows;
    printf("the col is %d , the row is %d \n", col, row);

    Mat M(100, 100, src.type(), Scalar(21, 13, 43));//另一种图像定义方式
    //cout << "M= " << endl << M << endl;
    cout <<src.type() << endl;

    Mat dst4(src);//属于部分复制
    Mat dst5 = dst4;

    Mat L;
    L.create(src.size(), src.type());//L.create不能赋值，需要用下条语句进行赋值操作
    L = Scalar(0, 0, 0);//可以使用多维数组进行赋值

    Mat dst6 = Mat::eye(2,3, src.type());//对角线上每个像素点的第一个通道赋值为1，其余均为0
    /*[1,0,0,0,0,0,0,0,0
       0,0,0,1,0,0,0,0,0]*/
    cout << "dst6= " << endl << dst6 << endl;

    namedWindow("output",WINDOW_AUTOSIZE);
    imshow("output",dst3);
    waitKey(0);
    return 0;
}