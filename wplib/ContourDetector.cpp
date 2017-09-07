//
// Created by riccardo on 27/07/17.
//

#include "ContourDetector.h"


std::vector<std::vector<cv::Point>> ContourDetector::contours(const cv::Mat &mat, bool inv) const 
{

    cv::Mat mask;
    // convert to binary|binary_inverted, findContours find only contours of white areas
    (inv) ? cv::threshold(mat, mask, 0, 255,  CV_THRESH_BINARY_INV | CV_THRESH_OTSU)
          : threshold(mat, mask, 0, 255,  CV_THRESH_BINARY | CV_THRESH_OTSU);
//
//    //todo da eliminare
//    imshow("cap", mask);
//    waitKey(0);

    // find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    if(inv)
        cv::drawContours(mat,contours,-1, cv::Scalar(0,0,255), CV_FILLED);

//    //todo eliminare parte commentata
//    imshow("ciao", mat);
//    waitKey(0);

    return contours;
}
