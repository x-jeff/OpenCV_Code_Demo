#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {
    Mat src, dst;
    src = imread("../15x1.png");
    if (!src.data) {
        printf("could not find the image...\n");
        return -1;
    }
    namedWindow("src", WINDOW_AUTOSIZE);
    imshow("src", src);

    int top = (int) (0.05 * src.rows);
    int bottom = (int) (0.05 * src.rows);
    int left = (int) (0.05 * src.cols);
    int right = (int) (0.05 * src.cols);
    RNG rng(12345);
    int borderType = BORDER_DEFAULT;

    int c = 0;
    while (true) {
        c = waitKey(500);
        //27为ESC
        if ((char) c == 27) {
            break;
        }
        if ((char) c == 'r') {
            borderType = BORDER_REPLICATE;
        } else if ((char) c == 'w') {
            borderType = BORDER_WRAP;
        } else if ((char) c == 'c') {
            borderType = BORDER_CONSTANT;
        } else {
            borderType = BORDER_DEFAULT;
        }
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst, top, bottom, left, right, borderType,
                       color);//只有borderType= BORDER_CONSTANT时，color才起作用。
        imshow("dst", dst);
    }

    //GaussianBlur(src, dst, Size(5, 5), 0, 0, BORDER_CONSTANT);
    //imshow("dst", dst);

    waitKey(0);
    return 0;
}