#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
    Mat src = imread("..//..//Demo1//p1.jpeg");
    if (!src.data)
    {
        printf("could not find...\n");
        return -1;
    }

    /*
    //单通道图像
    Mat dst;
    cvtColor(src, dst, COLOR_BGR2GRAY);//等同于CV_BGR2GRAY
    int height = dst.rows;
    int width = dst.cols;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int intensity = dst.at<uchar>(row, col);//得到每一点的像素值
            dst.at<uchar>(row, col) = 0;//255 - intensity;//改变每个点的像素值
        }
    }

    Scalar p1 = dst.at<uchar>(0, 0);//输出为[211,0,0,0]
    int p2 = dst.at<uchar>(0, 0);//输出为211
    cout << p1 <<'\n'<<p2<< endl;
    */

    /*
    Mat dst;
    cvtColor(src, dst, COLOR_BGR2GRAY);
    Mat dst2 = Mat::zeros(src.size(), src.type());
    int height_3 = src.rows;
    int width_3 = src.cols;
    int nc = src.channels();
    for (int row = 0; row < height_3; row++)
    {
        for (int col = 0; col < width_3; col++)
        {
            if (nc == 1)//如果是单通道
            {
                int intensity = src.at<uchar>(row, col);
                dst.at<uchar>(row, col) = 255 - intensity;
            }
            else if (nc == 3)//如果是三通道
            {
                int blue = src.at<Vec3b>(row, col)[0];
                int green = src.at<Vec3b>(row, col)[1];
                int red = src.at<Vec3b>(row, col)[2];
                dst2.at<Vec3b>(row, col)[0] = 255 - blue;
                dst2.at<Vec3b>(row, col)[1] = 255 - green;
                dst2.at<Vec3b>(row, col)[2] = 255 - red;
            }
            else
                return -1;
        }
    }
    Vec3b intensity_1 = src.at<Vec3b>(0, 0);//输出为[216,211,210]
    Scalar intensity_2 = src.at<Vec3b>(0, 0);//输出为[216,211,210,0]
    cout << intensity_1<<'\n'<<intensity_2 << endl;

    int blue = intensity_2.val[0];
    int green = intensity_2.val[1];
    int red = intensity_2.val[2];
    cout << blue <<'\n'<<green<<'\n'<<red<< endl;//和Vec3b一样

    bitwise_not(src, dst2);//位操作,非。一句即可代替上面的转化操作
    */


    //Rect r(0, 0, 500, 500);//切割感兴趣的部分。等同于  Mat smalling=src(Rect(0,0,500,500));
    //Mat smalling = src(r);

    /*
    Mat smalling = src(Rect(0, 0, 500, 500));
    */

    Mat img;
    img=Scalar(0);

    namedWindow("output", WINDOW_AUTOSIZE);
    imshow("output", img);
    waitKey(0);
    return 0;
}