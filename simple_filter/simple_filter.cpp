#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    std::string img_path = "images/flower.jpg";
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

    cv::Mat median_blur;
    cv::medianBlur(resized_img, median_blur, 9);

    cv::Mat gaussian_blur;
    cv::GaussianBlur(resized_img, gaussian_blur, cv::Size(1, 1), 9, 9);

    cv::imshow("Original img", resized_img);
    cv::imshow("median blur", median_blur);
    cv::imshow("gaussian blur", gaussian_blur);
    cv::waitKey(0);
    return 0;
}