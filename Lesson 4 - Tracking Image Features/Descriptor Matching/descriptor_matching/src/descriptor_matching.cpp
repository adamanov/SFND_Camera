#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

#include "structIO.hpp"

using namespace std;

void matchDescriptors(cv::Mat &imgSource, cv::Mat &imgRef, vector<cv::KeyPoint> &kPtsSource, vector<cv::KeyPoint> &kPtsRef, cv::Mat &descSource, cv::Mat &descRef,
                      vector<cv::DMatch> &matches, string descriptorType, string matcherType, string selectorType)
{

    // configure matcher
    bool crossCheck = true;
    cv::Ptr<cv::DescriptorMatcher> matcher;

    // if crossCheck = true   --> result: BF matching cross-check=1 (NN) with n=1705 matches in 77.2177 ms  (reduce number of FP)
    // if crossCheck = false  --> result: BF matching cross-check=0 (NN) with n=2896 matches in 39.2552 ms

    if (matcherType.compare("MAT_BF") == 0)
    {

        int normType = descriptorType.compare("DES_BINARY") == 0 ? cv::NORM_HAMMING : cv::NORM_L2;
        matcher = cv::BFMatcher::create(normType, crossCheck);
        cout << "BF matching cross-check=" << crossCheck;
    }
    else if (matcherType.compare("MAT_FLANN") == 0)
    {
        if (descSource.type() != CV_32F)
        { // OpenCV bug workaround : convert binary descriptors to floating point due to a bug in current OpenCV implementation
            descSource.convertTo(descSource, CV_32F);
            descRef.convertTo(descRef, CV_32F);
        }

        //... TODO : implement FLANN matching
        cout << "FLANN matching";
        matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    }

    // perform matching task
    if (selectorType.compare("SEL_NN") == 0)
    { // nearest neighbor (best match)

        double t = (double)cv::getTickCount();
        matcher->match(descSource, descRef, matches); // Finds the best match for each descriptor in desc1
        t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
        cout << " (KNN) with n=" << matches.size() << " matches in " << 1000 * t / 1.0 << " ms" << endl;
    }
    else if (selectorType.compare("SEL_KNN") == 0)
    { // k nearest neighbors (k=2)
        double t = (double)cv::getTickCount();

        // TODO : implement k-nearest-neighbor matching
        vector<vector<cv::DMatch> > knn_matches;
        int k_nn = 2; // Count of best matches found per each query descriptor  (minDescDistRatio)
        matcher->knnMatch(descSource,descRef,knn_matches,k_nn);

        // TODO : filter matches using descriptor distance ratio test
        const float ratio_threshold = 0.8f;
        for (size_t i=0; i<knn_matches.size();i++)
        {
            if (knn_matches[i][0].distance<ratio_threshold * knn_matches[i][1].distance)
            {
                matches.push_back(knn_matches[i][0]);
            }

        }
        t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
        cout << "# keypoints removed = " << knn_matches.size() - matches.size() << endl;
        cout << " (NN) with n=" << matches.size() << " matches in " << 1000 * t / 1.0 << " ms" << endl;

    }

    // visualize results
    cv::Mat matchImg = imgRef.clone();
    cv::drawMatches(imgSource, kPtsSource, imgRef, kPtsRef, matches,
                    matchImg, cv::Scalar::all(-1), cv::Scalar::all(-1), vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    string windowName = "Matching keypoints between two camera images (best 50)";
    cv::namedWindow(windowName, cv::WINDOW_FREERATIO);
    cv::imshow(windowName, matchImg);
    cv::waitKey(0);
}

int main()
{
    cv::Mat imgSource = cv::imread("../images/img1gray.png");
    cv::Mat imgRef = cv::imread("../images/img2gray.png");

    vector<cv::KeyPoint> kptsSource, kptsRef; 
    readKeypoints("../dat/C35A5_KptsSource_SIFT.dat", kptsSource);
    readKeypoints("../dat/C35A5_KptsRef_SIFT.dat", kptsRef);

    cv::Mat descSource, descRef; 
    readDescriptors("../dat/C35A5_DescSource_SIFT.dat", descSource);
    readDescriptors("../dat/C35A5_DescRef_SIFT.dat", descRef);

    vector<cv::DMatch> matches;
    //string matcherType = "MAT_BF";
    string matcherType = "MAT_FLANN";

    //string descriptorType = "DES_BINARY";
    string descriptorType = "DES_HOG";


    //string selectorType = "SEL_NN";
    string selectorType = "SEL_KNN";


    matchDescriptors(imgSource, imgRef, kptsSource, kptsRef, descSource, descRef, matches, descriptorType, matcherType, selectorType);
}