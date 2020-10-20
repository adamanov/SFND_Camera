#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void gaussianSmoothing1()
{
    // load image from file
    cv::Mat img;
    img = cv::imread("../images/img1gray.png");

    // create filter kernel
    float gauss_data[25] = {1, 4, 7, 4, 1,
                            4, 16, 26, 16, 4,
                            7, 26, 41, 26, 7,
                            4, 16, 26, 16, 4,
                            1, 4, 7, 4, 1};

    cv::Mat kernel = cv::Mat(5, 5, CV_32F, gauss_data)/ (float)(5*5); // we had to normalize the box filter

    // apply filter
    cv::Mat result;  cv::Mat result_gaussian; cv::Mat result_median; cv::Mat result_bilateral;
    cv::Point anchor = cv::Point(-1,-1);
    cv::filter2D(img, result, -1, kernel, anchor, 0, cv::BORDER_DEFAULT);

    // TODO Trying out other Popular filters
    // Gaussian blurring is highly effective in removing Gaussian noise from an image.
    cv::GaussianBlur(img,result_gaussian,cv::Size(5,5),0);
    //Here, the function cv.medianBlur() takes the median of all the pixels under the kernel area and the central element is replaced with this median value.
    //This is highly effective against salt-and-pepper noise in an imag
    cv::medianBlur(img,result_median,5);
    //cv.bilateralFilter() is highly effective in noise removal while keeping edges sharp.
    cv::bilateralFilter(img,result_bilateral,9,75,75);

    cv::imshow("Orginal Image", img);
    cv::imshow("GaussianBlur", result_gaussian);
    cv::imshow("medianBlur", result_median);
    cv::imshow("bilateralFilter", result_bilateral);


    // show result
    string windowName = "Gaussian Blurring";
    cv::namedWindow(windowName, 1); // create window
    cv::imshow(windowName, result);




    cv::waitKey(0); // wait for keyboard input before continuing
}

int main()
{
    gaussianSmoothing1();
}