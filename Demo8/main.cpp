#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
Mat bgImage;//定义一个全局变量
void MyLines();
void MyRectangle();
void MyEllipse();
void MyCircle();
void MyPolygon();
void RandomLineDemo();
int main(int argc, char**argv){
    bgImage = imread("..//..//Demo1//p1.jpeg");
    //Mat dst = bgImage(Rect(0, 0, 100, 100));
    MyLines();
    MyRectangle();
    MyEllipse();
    MyCircle();
    MyPolygon();
    //八个参数：目标图像，文字，文本框左下角位置，字体，字号(缩放比例)，颜色，线宽，线类型
    putText(bgImage, "hello opencv", Point(300, 300), FONT_HERSHEY_COMPLEX, 1.0, Scalar(0, 255, 211), 1, 8);
    namedWindow("output", WINDOW_AUTOSIZE);
    imshow("output", bgImage);
    RandomLineDemo();
    waitKey(0);
    return 0;
}
void MyLines(){
    Point p1 = Point(20, 30);
    Point p2;
    p2.x = 300;
    p2.y = 300;
    Scalar color = Scalar(0, 0, 255);
    //六个参数分别是：原图，起始点，结束点，颜色，线宽，线类型
    line(bgImage, p1, p2, color, 1, 8);//该opencv版本不支持LINE_8，直接写8就行
}
void MyRectangle(){
    Rect rect = Rect(200, 100, 300, 300);
    Scalar color = Scalar(255, 0, 0);
    //空心矩形
    rectangle(bgImage, rect, color, 2, 8);//五个参数分别是：原图，矩形大小，颜色，线宽，线类型
}
void MyEllipse(){
    Scalar color = Scalar(0, 255, 0);
    //九个参数：原图，圆心，大小（width和height），椭圆的摆放角度，起始角度，结束角度，颜色，线宽，线类型
    ellipse(bgImage, Point(bgImage.cols / 2, bgImage.rows / 2), Size(100,200), 0, 0, 360, color, 2, 8);
}
void MyCircle(){
    Scalar color = Scalar(0, 255, 255);
    Point center = Point(bgImage.cols / 2, bgImage.rows / 2);
    circle(bgImage, center, 150,color,2,8);//六个参数：原图，圆心，半径，颜色，线宽，线类型
}
void MyPolygon(){
    Point pts[1][5];
    pts[0][0] = Point(100, 100);
    pts[0][1] = Point(100, 200);
    pts[0][2] = Point(200, 200);
    pts[0][3] = Point(200, 100);
    pts[0][4] = Point(100, 100);
    const Point* ppts[] = { pts[0] };//指向指针的指针
    int npt[] = { 5 };//定义一个整形数组
    Scalar color = Scalar(255, 12, 255);
    //六个参数：目标图像，多边形的顶点集合（指针数组），多边形顶点的数目（整型数组），要绘制的多边形的数量，颜色，线宽
    fillPoly(bgImage, ppts, npt, 1, color, 8);

}
void RandomLineDemo(){
    RNG rng(12345);
    Point pt1, pt2;
    Mat bg = Mat::zeros(bgImage.size(), bgImage.type());
    for (int i = 0; i < 100000; i++){
        pt1.x = rng.uniform(0, bgImage.cols);
        pt2.x = rng.uniform(0, bgImage.cols);
        pt1.y = rng.uniform(0, bgImage.rows);
        pt2.y = rng.uniform(0, bgImage.rows);
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        if (waitKey(50)>0){
            break;
        }
        line(bg, pt1, pt2, color, 1, 8);
        namedWindow("random_line", WINDOW_AUTOSIZE);
        imshow("random_line", bg);
    }
}