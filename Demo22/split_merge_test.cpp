#include <opencv2/opencv.hpp>

int main() {
    cv::Mat src = imread("../../Demo1/p1.jpeg", cv::IMREAD_COLOR);
    cv::namedWindow("src", cv::WINDOW_AUTOSIZE);
    cv::imshow("src", src);

    // Split the image into different channels
    std::vector<cv::Mat> rgbChannels(3);
    split(src, rgbChannels);

    // Show individual channels
    cv::Mat blank_ch, fin_img;
    blank_ch = cv::Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC1);

    // Showing Red Channel
    // G and B channels are kept as zero matrix for visual perception
    std::vector<cv::Mat> channels_r;
    channels_r.push_back(blank_ch);
    channels_r.push_back(blank_ch);
    channels_r.push_back(rgbChannels[2]);

    /// Merge the three channels
    cv::merge(channels_r, fin_img);
    cv::imshow("R", fin_img);


    // Showing Green Channel
    std::vector<cv::Mat> channels_g;
    channels_g.push_back(blank_ch);
    channels_g.push_back(rgbChannels[1]);
    channels_g.push_back(blank_ch);
    cv::merge(channels_g, fin_img);
    cv::imshow("G", fin_img);


    // Showing Blue Channel
    std::vector<cv::Mat> channels_b;
    channels_b.push_back(rgbChannels[0]);
    channels_b.push_back(blank_ch);
    channels_b.push_back(blank_ch);
    cv::merge(channels_b, fin_img);
    cv::imshow("B", fin_img);

    cv::waitKey(0);
    return 0;
}