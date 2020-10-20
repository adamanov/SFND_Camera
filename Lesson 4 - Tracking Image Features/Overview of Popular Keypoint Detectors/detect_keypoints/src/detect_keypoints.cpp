#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

using namespace std;

void detKeypoints1()
{
    // load image from file and convert to grayscale
    cv::Mat imgGray;
    cv::Mat img = cv::imread("../images/img1.png");
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // Shi-Tomasi detector
    int blockSize = 6;       //  size of a block for computing a derivative covariation matrix over each pixel neighborhood
    double maxOverlap = 0.0; // max. permissible overlap between two features in %
    double minDistance = (1.0 - maxOverlap) * blockSize;  // Minimum possible Euclidean distance between the returned corners.
    int maxCorners = img.rows * img.cols / max(1.0, minDistance); // max. num. of keypoints
    double qualityLevel = 0.01;  // minimal accepted quality of image corners based on min. eigenvalues of Covariance (see cornerMinEigenVal), if lower->reject
    double k = 0.04;
    bool useHarris = false;

    vector<cv::KeyPoint> kptsShiTomasi;
    vector<cv::Point2f> corners;
    double t = (double)cv::getTickCount();
    cv::goodFeaturesToTrack(imgGray, corners, maxCorners, qualityLevel, minDistance, cv::Mat(), blockSize, useHarris, k);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    cout << "Shi-Tomasi with n= " << corners.size() << " keypoints in " << 1000 * t / 1.0 << " ms" << endl;

    for (auto it = corners.begin(); it != corners.end(); ++it)
    { // add corners to result vector

        cv::KeyPoint newKeyPoint;
        newKeyPoint.pt = cv::Point2f((*it).x, (*it).y);
        newKeyPoint.size = blockSize;
        kptsShiTomasi.push_back(newKeyPoint);

        //Circles can draw also with :
        //cv::circle()
    }

    // visualize results
    cv::Mat visImage = img.clone();
    cv::drawKeypoints(img, kptsShiTomasi, visImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    string windowName = "Shi-Tomasi Results";
    cv::namedWindow(windowName, 1);
    imshow(windowName, visImage);


    // TODO: use the OpenCV library to add the FAST detector
    // in addition to the already implemented Shi-Tomasi 
    // detector and compare both algorithms with regard to 
    // (a) number of keypoints, (b) distribution of 
    // keypoints over the image and (c) processing speed.
    vector<cv::KeyPoint> fast_kpts;
    double t_fast = (double)cv::getTickCount();
    cv::FAST(imgGray,fast_kpts,16,true);
    t_fast = ((double)cv::getTickCount() - t_fast) / cv::getTickFrequency();
    cout << "Fast with n= " << fast_kpts.size() << " keypoints in " << 1000 * t_fast / 1.0 << " ms" << endl;

    cout<< "Difference of keypoints: " << fast_kpts.size() - corners.size()<<endl;




    cv::Mat visImFast = img.clone();
    cv::drawKeypoints(img,fast_kpts,visImFast,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    string windowImage_fast = "Fast";
    cv::namedWindow(windowImage_fast,cv::WINDOW_AUTOSIZE);
    cv::imshow(windowImage_fast,visImFast);


    cv::waitKey(0);




}

int main()
{
    detKeypoints1();
}