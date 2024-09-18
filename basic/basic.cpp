#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    std::string img_path = "images/pool_table.png";
    cv::Mat     img      = cv::imread(img_path, cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Could not load img!" << std::endl;
        return -1;
    }
    cv::imshow("Display window", img);
    cv::waitKey(0);
    return 0;
}