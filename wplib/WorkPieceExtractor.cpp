//
// Created by riccardo on 30/07/17.
//

#include "WorkPieceExtractor.h"
#include "wp.h"

WorkPiece WorkPieceExtractor::elaborate(const cv::Mat &mat) {

    std::vector<std::vector<cv::Point>> contours = wp::contourDetector(mat, false);
    if(contours.empty())
        throw std::runtime_error("No workpiece found");
    std::vector<cv::Point> biggestContour = wp::biggestContourFinder(contours);
    cv::RotatedRect r1 = cv::minAreaRect(biggestContour);
    cv::Point2f p[4];
    r1.points(p);
    cv::Mat m = cv::Mat::ones(500,500, CV_8UC1);

    clock_t begin = clock();

    cv::RotatedRect r2 = wp::largestRectInNonConvexPoly(mat);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<< "Time elapsed largestRectInNonConvexPoly function: "<<elapsed_secs << " sec"<<std::endl;

    return WorkPiece(r2);
}