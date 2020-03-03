#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//添加椒盐噪声
Mat addSaltNoise(Mat src, int n)
{
    Mat result = src.clone();
    for (int k = 0; k < n; k++)
    {
        //随机选取行列值
        int i = rand() % result.cols;
        int j = rand() % result.rows;
        if (result.channels() == 1)
        {
            result.at<uchar>(j, i) = 255;
        }
        else
        {
            result.at<Vec3b>(j, i)[0] = 255;
            result.at<Vec3b>(j, i)[1] = 255;
            result.at<Vec3b>(j, i)[2] = 255;
        }

    }
    return result;
}

int main(int argc,char** argv){
    Mat src;
    src=imread("../../Demo1/p1.jpeg");
    if(!src.data){
        printf("could not find the image...\n");
        return (0);
    }
    namedWindow("src",WINDOW_AUTOSIZE);
    imshow("src",src);

    Mat src_blur;
    blur(src,src_blur,Size(5,5),Point(-1,-1));
//    imshow("src_blur",src_blur);

    Mat src_gaussian_blur;
    GaussianBlur(src,src_gaussian_blur,Size(5,5),3,3);
//    imshow("src_gaussian_blur",src_gaussian_blur);

    Mat src_salt,src_median_blur;
    src_salt=addSaltNoise(src,100000);
//    imshow("src_salt",src_salt);
    medianBlur(src_salt,src_median_blur,3);
//    imshow("src_median_blur",src_median_blur);

    Mat src_bilateral;
    bilateralFilter(src,src_bilateral,3,100,3);
    imshow("src_bilateral",src_bilateral);

    waitKey(0);
    return (0);
}