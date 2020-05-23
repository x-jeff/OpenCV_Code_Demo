#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv){
    Mat src,gray1,gray2,binary1,binary2,dst,dst1,dst2;

    //读入原始图像
    src = imread("p1.png");
    if (src.empty()){
        printf("could not find the image...\n");
        return -1;
    }

    //将原始图像转换为灰度图像
    cvtColor(src, gray1, COLOR_BGR2GRAY);

    //将灰度图像转换为二值图像
    adaptiveThreshold(~gray1, binary1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);//~gray1取反，即255-gray1
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);
    imshow("gray1", gray1);
    imshow("~gray1", ~gray1);
    imshow("binary1", binary1);

    //定义结构元素
    Mat hline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));//用于提取水平线的结构元素
    Mat vline = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16), Point(-1, -1));//用于提取垂直线的结构元素

    //提取水平线或者垂直线都是开操作，即先腐蚀后膨胀，提取水平线的kernel是hline，提取垂直线的kernel是vline
    //提取水平线
    //erode(binary1, dst1, hline);
    //dilate(dst1, dst2, hline);
    morphologyEx(binary1, dst2, MORPH_OPEN, hline);
    bitwise_not(dst2,dst2);
    imshow("extract_hline",dst2);

    //提取垂直线
    //erode(binary1, dst1, vline);
    //dilate(dst1, dst2, vline);
    morphologyEx(binary1, dst2, MORPH_OPEN, vline);
    //imshow("extract_vline",dst2);
    imshow("extract_vline",~dst2);

    //可以添加模糊效果
    Mat dst3;
    blur(~dst2,dst3,Size(3,3),Point(-1,-1));
    imshow("extract_vline_blur",dst3);

    waitKey(0);
    return 0;
}