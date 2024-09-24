#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main()
{
    std::string img_path = "images/opencv_hsv_map.png";

    cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
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

    cv::Mat yellow_mask;
    {
        // H: 0-179, S: 0-255, V: 0-255
        int  cv_low_H     = 28;
        int  cv_low_S     = 50;
        int  cv_low_V     = 20;
        int  cv_high_H    = 32;
        int  cv_high_S    = 255;
        int  cv_high_V    = 255;
        auto lower_bound  = cv::Scalar(cv_low_H, cv_low_S, cv_low_V);
        auto higher_bound = cv::Scalar(cv_high_H, cv_high_S, cv_high_V);
        cv::inRange(hsv_img, lower_bound, higher_bound, yellow_mask);
    }
    cv::Mat pink_mask;
    {
        // H: 0-179, S: 0-255, V: 0-255
        int  cv_low_H     = 148;
        int  cv_low_S     = 50;
        int  cv_low_V     = 20;
        int  cv_high_H    = 152;
        int  cv_high_S    = 255;
        int  cv_high_V    = 255;
        auto lower_bound  = cv::Scalar(cv_low_H, cv_low_S, cv_low_V);
        auto higher_bound = cv::Scalar(cv_high_H, cv_high_S, cv_high_V);
        cv::inRange(hsv_img, lower_bound, higher_bound, pink_mask);
    }

    cv::Mat resultant_mask;
    resultant_mask = cv::Mat::zeros(resized_img.size(), CV_8UC3);
    cv::bitwise_or(yellow_mask, pink_mask, resultant_mask);

    cv::Mat result_apply_masks;
    result_apply_masks = cv::Mat::zeros(resized_img.size(), CV_8UC3);
    cv::bitwise_and(resized_img, resized_img, result_apply_masks, resultant_mask);

    cv::imshow("resized_img", resized_img);
    cv::imshow("hsv_img", hsv_img);
    cv::imshow("yellow_mask", yellow_mask);
    cv::imshow("pink_mask", pink_mask);
    cv::imshow("resultant_mask", resultant_mask);
    cv::imshow("result_apply_masks", result_apply_masks);
    cv::waitKey(0);
    return 0;
}