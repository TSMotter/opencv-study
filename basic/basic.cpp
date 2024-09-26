#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    cv::Mat img;
    if (argc != 2 || !(img = cv::imread(argv[1], cv::IMREAD_COLOR)).data)
    {
        std::cout << "Could not load img!" << std::endl;
        return -1;
    }
    cv::imshow("img", img);
    cv::waitKey(0);
    return 0;
}