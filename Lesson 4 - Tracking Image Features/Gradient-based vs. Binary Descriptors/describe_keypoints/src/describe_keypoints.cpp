#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#ifdef HAVE_OPENCV_XFEATURES2D

using namespace std;

void descKeypoints1()
{
    // load image from file and convert to grayscale
    cv::Mat imgGray;
    cv::Mat img = cv::imread("../images/img1.png");
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // BRISK detector / descriptor
    cv::Ptr<cv::FeatureDetector> detector = cv::BRISK::create();
    vector<cv::KeyPoint> kptsBRISK;

    double t = (double)cv::getTickCount();
    detector->detect(imgGray, kptsBRISK);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    cout << "BRISK detector with n= " << kptsBRISK.size() << " keypoints in " << 1000 * t / 1.0 << " ms" << endl;

    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::BRISK::create();
    cv::Mat descBRISK;
    t = (double)cv::getTickCount();
    descriptor->compute(imgGray, kptsBRISK, descBRISK);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    cout << "BRISK descriptor in " << 1000 * t / 1.0 << " ms" << endl;

    // visualize results
    cv::Mat visImage = img.clone();
    cv::drawKeypoints(img, kptsBRISK, visImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    string windowName = "BRISK Results";
    cv::namedWindow(windowName, 1);
    imshow(windowName, visImage);

    // TODO: Add the SIFT detector / descriptor, compute the
    // time for both steps and compare both BRISK and SIFT
    // with regard to processing speed and the number and 
    // visual appearance of keypoints.

    //Detection of keypoints
    cv::Ptr<cv::FeatureDetector> sift_detector = cv::SIFT::create();
    vector<cv::KeyPoint> SIFT_kpts;

    t = (double)cv::getTickCount();
    sift_detector->detect(imgGray,SIFT_kpts);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    cout << "SIFT detector with n= " << SIFT_kpts.size() << " keypoints in " << 1000 * t / 1.0 << " ms" << endl;

    //Computation of descriptors
    cv::Ptr<cv::DescriptorExtractor> sift_descriptor = cv::SIFT::create();
    cv::Mat descSIFT;
    t = (double)cv::getTickCount();
    sift_descriptor->compute(imgGray,SIFT_kpts,descSIFT);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    cout << "SIFT descriptor in " << 1000 * t / 1.0 << " ms" << endl;

    // Visualization
    cv::Mat visImSIFT = img.clone();
    cv::drawKeypoints(img,SIFT_kpts,visImSIFT,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    string nameWindowSIFT ="SIFT Results";
    cv::namedWindow(nameWindowSIFT,cv::WINDOW_NORMAL);
    cv::imshow(nameWindowSIFT,visImSIFT);


    //TODO: Add the SURF detector / descriptor, compute PS: REQUIRE A LICENSE
/*

    //Detect keypoints
    int minHessian = 400;
    cv::Ptr<cv::xfeatures2d::SURF> surf_detector = cv::xfeatures2d::SURF::create(minHessian);
    vector<cv::KeyPoint> SURF_kpts;
    t = (double)cv::getTickCount();
    surf_detector->detect(imgGray,SURF_kpts);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    cout << "SURF detector with n= " << SURF_kpts.size() << " keypoints in " << 1000 * t / 1.0 << " ms" << endl;

    //Compute Descriptors
    cv::Ptr<cv::DescriptorExtractor> surf_descriptor = cv::xfeatures2d::SURF::create(minHessian);
    cv::Mat descSURF;
    t = (double)cv::getTickCount();
    surf_descriptor->compute(imgGray,SURF_kpts,descSURF);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    cout << "SURF descriptor in " << 1000 * t / 1.0 << " ms" << endl;

    // Visualization
    cv::Mat visImSURF = img.clone();
    cv::drawKeypoints(img,SURF_kpts,visImSURF,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    string nameWindowSURF ="SURF Results";
    cv::namedWindow(nameWindowSURF,cv::WINDOW_NORMAL);
    cv::imshow(nameWindowSURF,visImSURF);

*/




    cv::waitKey(0);

}

int main()
{
    descKeypoints1();
    return 0;
}
#endif