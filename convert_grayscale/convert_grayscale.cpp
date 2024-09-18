#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    std::string img_path = "images/pool_table.png";

    cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Could not load image!" << std::endl;
        return -1;
    }

    cv::Mat gray_img(img.rows, img.cols, CV_8UC1);

    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            cv::Vec3b pixel_color = img.at<cv::Vec3b>(row, col);

            // luminance formula:
            // Gray = 0.299 * R + 0.587 * G + 0.114 * B
            uchar gray_pixel_value = static_cast<uchar>(
                0.299 * pixel_color[2] + 0.587 * pixel_color[1] + 0.114 * pixel_color[0]);

            gray_img.at<uchar>(row, col) = gray_pixel_value;
        }
    }

    cv::imshow("Original img", img);
    cv::imshow("Grayscale img", gray_img);
    cv::waitKey(0);
    return 0;
}