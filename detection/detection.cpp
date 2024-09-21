#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main()
{
    // std::string img_path = "images/pool_table.png";
    std::string img_path = "images/flower.jpg";
    cv::Mat     img      = cv::imread(img_path, cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Could not load img!" << std::endl;
        return -1;
    }

    int   new_w        = 500;
    float aspect_ratio = static_cast<float>(img.cols) / static_cast<float>(img.rows);
    int   new_h        = static_cast<int>(new_w / aspect_ratio);

    cv::Mat resized_img;
    cv::resize(img, resized_img, cv::Size(new_w, new_h));
    cv::Mat hsv_img;
    cv::cvtColor(resized_img, hsv_img, cv::COLOR_BGR2HSV);
    cv::Mat median_hsv_blur;
    cv::medianBlur(hsv_img, median_hsv_blur, 9);

    // H = 0-360, S = 0-100 and V = 0-100
    int real_low_H  = 40;
    int real_low_S  = 80;
    int real_low_V  = 90;
    int real_high_H = 60;
    int real_high_S = 100;
    int real_high_V = 100;

    // H: 0-179, S: 0-255, V: 0-255
    int cv_low_H  = real_low_H / 2;
    int cv_low_S  = (int) (real_low_S * 2.55);
    int cv_low_V  = (int) (real_low_V * 2.55);
    int cv_high_H = real_high_H / 2;
    int cv_high_S = (int) (real_high_S * 2.55);
    int cv_high_V = (int) (real_high_V * 2.55);

    auto lower_bound  = cv::Scalar(cv_low_H, cv_low_S, cv_low_V);
    auto higher_bound = cv::Scalar(cv_high_H, cv_high_S, cv_high_V);

    cv::Mat img_threshold;
    cv::inRange(median_hsv_blur, lower_bound, higher_bound, img_threshold);

    cv::imshow("resized_img", resized_img);
    cv::imshow("hsv_img", hsv_img);
    cv::imshow("median_hsv_blur", median_hsv_blur);
    cv::imshow("img_threshold", img_threshold);
    cv::waitKey(0);
    return 0;
}