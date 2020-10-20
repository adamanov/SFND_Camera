#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>

using namespace std;

void magnitudeSobel()
{
    // load image from file
    cv::Mat img;
    //img = cv::imread("./images/img1gray.png");
    img = cv::imread("../images/img1.png");

    // convert image to grayscale
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // apply smoothing using the GaussianBlur() function from the OpenCV
    // ToDo : Add your code here
    cv::Mat imgGaussFilt = imgGray.clone();

    int stdDev = 2.0; // Hyperparameter, as well kernel sizes 5x5
    cv::GaussianBlur(imgGray,imgGaussFilt,cv::Size(5,5),stdDev,stdDev,cv::BorderTypes(cv::BORDER_DEFAULT));
    cv::imshow("imgGaussFilt",imgGaussFilt);

    // create filter kernels using the cv::Mat datatype both for x and y
    // ToDo : Add your code here
    float sobel_x[9] = { -1, 0 , 1,
                         -2, 0 , 2,
                         -1, 0 , 1};

    float sobel_y[9] ={-1 ,-2 ,-1,
                       0 , 0 ,0,
                       1 , 1 ,2};
    cv::Mat kernel_x = cv::Mat(3,3,CV_32F,sobel_x);
    cv::Mat kernel_y = cv::Mat (3,3,CV_32F,sobel_y);

    // apply filter using the OpenCv function filter2D()
    // ToDo : Add your code here
    cv::Mat imgSobelX, imgSobelY;
    cv::filter2D(imgGaussFilt,imgSobelX,-1,kernel_x,cv::Point(-1,-1),0,cv::BORDER_DEFAULT);
    cv::imshow("Sobel operator (x-direction)",imgSobelX);
    cv::filter2D(imgGaussFilt,imgSobelY,-1,kernel_y,cv::Point(-1,-1),0,cv::BORDER_DEFAULT);
    cv::imshow("Sobel operator (y-direction)",imgSobelY);


    // compute magnitude image based on the equation presented in the lesson
    // ToDo : Add your code here


    cv::Mat gradient_dir = imgGray.clone();
    cv::Mat magnitude = imgGray.clone();
/*
 *
 * // This following operation is abbaneded since we are already calculated imgSobelX and imgSobelY
 * if we although decided to go compute in following way, we will get a lot of noise. Thats why it  is better go with Sobel operation
    cv::Mat dIdX = imgGray.clone(); ;
    // into X direction
    for(int r=0; r<dIdY.rows;r++)
    {
        for (int c = 0; c<dIdY.cols; c++)
        {
            dIdX.at<u_int8_t>(r,c) = imgGaussFilt.at<u_int8_t>(r,c+1) - imgGaussFilt.at<u_int8_t>(r,c);

        }

    }
    // into Y direction
    cv::Mat dIdY = imgGray.clone();;
    for(int c  = 0 ; c<dIdY.cols; c++)
    {
        for (int r = 0; r<dIdY.rows;r++)
        {
            dIdY.at<u_int8_t>(r,c) = imgGaussFilt.at<u_int8_t>(r+1,c) - imgGaussFilt.at<u_int8_t>(r,c);
        }
    }
*/


    for (int r=0; r<magnitude.rows; r++)
    {
        for (int c=0; c<magnitude.cols; c++)
        {
            // Compute Gradient_Direction
            //gradient_dir.at<u_int8_t>(r,c) = atan(imgSobelX.at<u_int8_t>(r,c) /
            //                                         imgSobelY.at<u_int8_t>(r,c) );

            //compute Magnitude
            magnitude.at<u_int8_t>(r,c) = sqrt(pow(imgSobelX.at<u_int8_t>(r,c),2) +
                                                  pow(imgSobelY.at<u_int8_t>(r,c),2)
                                                  );

        }
    }



    // show result
    string windowName = "Gaussian Blurring";
    cv::namedWindow(windowName, 1); // create window
    cv::imshow(windowName, magnitude);
    cv::waitKey(0); // wait for keyboard input before continuing


}

int main()
{
    magnitudeSobel();
}