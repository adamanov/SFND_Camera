#include <iostream>
#include <opencv2/core.hpp>
// for input and output of image, contain a gui
#include <opencv2/highgui.hpp>
// contain basic transformation on the image such as: image filtering, geometric transformation, feature detection and tracking.
#include <opencv2/imgproc/imgproc.hpp>
// contain some algorithms for detecting, describing and matching keypoints
#include <opencv2/features2d/features2d.hpp>


using namespace std;

void createMatrix1()
{
    // create matrix
    int nrows = 480, ncols = 640;
    cv::Mat m1_8u;
    m1_8u.create(nrows, ncols, CV_8UC1); // two-channel matrix with 8bit unsigned elements
    m1_8u.setTo(cv::Scalar(255));        // white

    // STUDENT TASK :
    // Create a variable of type cv::Mat* named m3_8u which has three channels with a
    // depth of 8bit per channel. Then, set the first channel to 255 and display the result.

    cv::Mat m3_8u(nrows,ncols,CV_8UC3);  // CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
    m3_8u.setTo(cv::Scalar(255));
    cv::imshow("m3_8u",m3_8u);



    // show result
    string windowName = "First steps in OpenCV (m1_8u)";
    cv::namedWindow(windowName, 1); // create window
    cv::imshow(windowName, m1_8u);
    cv::waitKey(0); // wait for keyboard input before continuing

    // STUDENT TASK :
    // Display the results from the STUDENT TASK above


}


int main()
{
    createMatrix1();
    return 0;
}