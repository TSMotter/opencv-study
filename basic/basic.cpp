#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    std::string image_path = "/home/ggm/Pictures/pool_table.png";
    cv::Mat     image      = cv::imread(image_path, cv::IMREAD_COLOR);
    cv::imshow("Display window", image);
    cv::waitKey(0);
    return 0;
}