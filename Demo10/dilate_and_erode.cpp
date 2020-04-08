#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
Mat src, dst;//设为全局变量，否则CallBack_Demo函数中无法使用
char winName[] = "output";
int element_size = 3;
int max_size = 21;
void CallBack_Demo(int, void*);//Trackbarcallback func的原型必须是这样！
int main(int argc, char**argv){
    src = imread("p1.png", -1);
    if (!src.data){
        printf("the image could not find...\n");
        return -1;
    }
    namedWindow("input image", WINDOW_AUTOSIZE);
    imshow("input image", src);

    namedWindow(winName, WINDOW_AUTOSIZE);
    //如果没有callback函数，就只有数值变化，即轨迹条可以正常滑动，数值可以正常随着滑块变化，但是图片不会变化
    //第三和第四个参数指的是运行callback函数的次数，本例中，callback函数运行几次就相当于dilate执行几次
    createTrackbar("Element Size", winName, &element_size, max_size, CallBack_Demo);
    CallBack_Demo(0, 0);
    //CallBack_Demo(1, &element_size);两个参数值随便设，好像并不会影响结果

    waitKey(0);
    return 0;
}

void CallBack_Demo(int, void*){
    int s = element_size * 2 + 1;
    Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    //dilate(src, dst, structureElement, Point(-1, -1), 1);//kernel就是structureElement，1是迭代次数，迭代次数指的是对原图整体做几次膨胀操作，次数越多，图片越偏白
    erode(src, dst, structureElement);
    imshow(winName, dst);
}