#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

constexpr const int max_value_H   = 360 / 2;
constexpr const int max_value_S_V = 255;

int main()
{
    std::string img_path = "images/pool_table.png";
    cv::Mat     img      = cv::imread(img_path, cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Could not load img!" << std::endl;
        return -1;
    }

    int     new_w        = 500;
    float   aspect_ratio = static_cast<float>(img.cols) / static_cast<float>(img.rows);
    int     new_h        = static_cast<int>(new_w / aspect_ratio);
    cv::Mat resized_img;
    cv::resize(img, resized_img, cv::Size(new_w, new_h));

    std::vector<int> lower_bound = {170, 80, 50};
    int              low_H       = lower_bound[0];
    int              low_S       = lower_bound[1];
    int              low_V       = lower_bound[2];
    int              high_H      = max_value_H;
    int              high_S      = max_value_S_V;
    int              high_V      = max_value_S_V;

    cv::Mat hsv_img, img_threshold;
    cv::cvtColor(resized_img, hsv_img, cv::COLOR_BGR2HSV);

    cv::Mat median_hsv_blur;
    cv::medianBlur(hsv_img, median_hsv_blur, 9);

    cv::inRange(median_hsv_blur, cv::Scalar(low_H, low_S, low_V),
                cv::Scalar(high_H, high_S, high_V), img_threshold);

    cv::imshow("resized_img", resized_img);
    cv::imshow("hsv_img", hsv_img);
    cv::imshow("median_hsv_blur", median_hsv_blur);
    cv::imshow("img_threshold", img_threshold);
    cv::waitKey(0);
    return 0;
}