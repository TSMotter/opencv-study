#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    cv::Mat img;
    if (argc != 2 || !(img = cv::imread(argv[1], cv::IMREAD_COLOR)).data)
    {
        std::cout << "Could not load img!" << std::endl;
        return -1;
    }

    int     new_w        = 500;
    float   aspect_ratio = static_cast<float>(img.cols) / static_cast<float>(img.rows);
    int     new_h        = static_cast<int>(new_w / aspect_ratio);
    cv::Mat resized_img;
    cv::resize(img, resized_img, cv::Size(new_w, new_h));

    std::vector<cv::Mat> bgr_planes;
    cv::split(resized_img, bgr_planes);

    int          hist_size         = 256;
    float        bgr_pixel_range[] = {0, 256};  // upper bound exclusive
    const float* hist_ranges       = {bgr_pixel_range};
    bool         uniform           = true;
    bool         accumulate        = false;

    cv::Mat output_b_hist = cv::Mat::zeros(resized_img.size(), CV_8UC3);
    cv::calcHist(&bgr_planes[0],  // Input image
                 1,               // Number of input images
                 0,  // The channel to be measured. In this case it is just the intensity (each
                     // array is single-channel) so we just write 0.
                 cv::Mat(),      // A mask (not used in this case, so just create an empty array)
                 output_b_hist,  // Output image
                 1,              // Number of dimensions of the histogram
                 &hist_size,     // Number of 'bins' per used channel
                 &hist_ranges,   // Range of values to be measured by each dimension
                 uniform,        // Bin sizes are the same
                 accumulate      // Histogram is cleared at the beginning
    );
    cv::Mat output_g_hist = cv::Mat::zeros(resized_img.size(), CV_8UC3);
    cv::calcHist(&bgr_planes[1], 1, 0, cv::Mat(), output_g_hist, 1, &hist_size, &hist_ranges,
                 uniform, accumulate);
    cv::Mat output_r_hist = cv::Mat::zeros(resized_img.size(), CV_8UC3);
    cv::calcHist(&bgr_planes[2], 1, 0, cv::Mat(), output_r_hist, 1, &hist_size, &hist_ranges,
                 uniform, accumulate);

    int     bin_w = cvRound((double) new_w / hist_size);
    cv::Mat histogram_final(new_h, new_w, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::normalize(output_b_hist, output_b_hist, 0, histogram_final.rows, cv::NORM_MINMAX, -1,
                  cv::Mat());
    cv::normalize(output_g_hist, output_g_hist, 0, histogram_final.rows, cv::NORM_MINMAX, -1,
                  cv::Mat());
    cv::normalize(output_r_hist, output_r_hist, 0, histogram_final.rows, cv::NORM_MINMAX, -1,
                  cv::Mat());

    for (int i = 1; i < hist_size; i++)
    {
        cv::line(histogram_final,
                 cv::Point(bin_w * (i - 1), new_h - cvRound(output_b_hist.at<float>(i - 1))),
                 cv::Point(bin_w * (i), new_h - cvRound(output_b_hist.at<float>(i))),
                 cv::Scalar(255, 0, 0), 2, 8, 0);
        cv::line(histogram_final,
                 cv::Point(bin_w * (i - 1), new_h - cvRound(output_g_hist.at<float>(i - 1))),
                 cv::Point(bin_w * (i), new_h - cvRound(output_g_hist.at<float>(i))),
                 cv::Scalar(0, 255, 0), 2, 8, 0);
        cv::line(histogram_final,
                 cv::Point(bin_w * (i - 1), new_h - cvRound(output_r_hist.at<float>(i - 1))),
                 cv::Point(bin_w * (i), new_h - cvRound(output_r_hist.at<float>(i))),
                 cv::Scalar(0, 0, 255), 2, 8, 0);
    }

    cv::imshow("resized_img", resized_img);
    cv::imshow("bgr_planes[0]", bgr_planes[0]);
    cv::imshow("bgr_planes[1]", bgr_planes[1]);
    cv::imshow("bgr_planes[2]", bgr_planes[2]);
    cv::imshow("histogram_final", histogram_final);
    cv::waitKey(0);
    return 0;
}