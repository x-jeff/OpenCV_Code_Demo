#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

int main(int argc,char**argv)
{
    Mat src,dst;
    src = imread("/Users/xinshichao/PersonalWork/C++Demo/Pictures/p1.jpeg");
    if (!src.data)
    {
        printf("could not find image...\n");
        return -1;
    }

    //src.cols输出的是图像x轴的像素个数，即Width
    //src.rows输出的是图像y轴的像素个数，即Height
    //src.channels()输出的是每个像素点的通道个数，RGB图像通道个数为3
    /*cout << src.cols << '\n' << src.rows << '\n' << src.channels() << endl;*/

    //掩膜写法一：
    int cols = (src.cols-1)*src.channels();//注意理解src.cols-1
    int offsetx = src.channels();
    int rows = src.rows;

    /*Mat初始化*/
    /*Mat M(2,2,CV_8UC3,cv::Scalar::all(1))
    前两个参数是指矩阵的行数和列数(int rows,int cols)，或者(Size size)
    第三个参数是矩阵的数据类型(CV_8UC3 (3通道阵列，8 bit 无符号整数))
    第4个是对每个像素值赋初值，这个代码就是把每个通道的像素值都赋值1，如果是Scalar(255,0,0),就是将255，0，0分别赋予每个像素点的3个通道*/
    dst = Mat::zeros(src.size(), src.type());//初始化一张新的空图，和src的图像大小和图像类型都一样(zeros：全部赋值为0)(无zeros，程序也可以正常运行输出结果)

    for (int row = 1; row < (rows - 1); row++)//理解rows为什么要-1
    {
        const uchar* current = src.ptr<uchar>(row);
        const uchar* previous = src.ptr<uchar>(row-1);
        const uchar* next = src.ptr<uchar>(row+1);
        uchar* output = dst.ptr<uchar>(row);
        for (int col = offsetx; col < cols; col++)
        {
            //进行掩膜操作，并且保证像素范围在0~255之间
            output[col] = saturate_cast<uchar>(5 * current[col] - (current[col + offsetx] + current[col - offsetx] + previous[col] + next[col]));
        }
    }

    //掩膜方法二：
    double t = getTickCount();//开始计时

    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    //filter2D(src, dst, -1, kernel);
    filter2D(src, dst, src.depth(), kernel);//src.depth()表示和原图src的位图深度一样，等同于-1

    //getTickCount()为开始到这条语句的计时总次数
    //t为开始到方法二的计时总次数
    double timeconsume = (getTickCount() - t) / getTickFrequency();
    printf("time consume %.2f", timeconsume);//方法二所消耗的时间

    namedWindow("contrast image", WINDOW_AUTOSIZE);
    imshow("contrast image", dst);
    namedWindow("input image", WINDOW_AUTOSIZE);
    imshow("input image", src);
    waitKey(0);
    return 0;
}