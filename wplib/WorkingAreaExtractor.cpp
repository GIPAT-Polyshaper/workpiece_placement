//
// Created by riccardo on 27/07/17.
//

#include "WorkingAreaExtractor.h"
#include "wp.h"


Rect WorkingAreaExtractor::elaborate(const Image& img)
{

//    return findBoundingRect(BiggestContourFinder().elaborate(ContourDetector().contours(img.getMat(), true)));

    //make a copy of the image
    cv::Mat* imgCopyMat = new cv::Mat();
    img.getMat().copyTo(*imgCopyMat);
    std::vector<std::vector<cv::Point>> biggestContour;
    std::vector<cv::Point> bigcont = BiggestContourFinder().elaborate(ContourDetector().contours(img.getMat(), true));
    biggestContour.push_back(bigcont);
    //filling white areas
    cv::drawContours(*imgCopyMat,biggestContour,-1, cv::Scalar(0,0,255), CV_FILLED);
//
//    imshow("filled", *imgCopyMat);
//    waitKey(0);

    cv::RotatedRect r1 = cv::minAreaRect(bigcont);

    Point2f p[4];
    r1.points(p);
    cv::Mat m = Mat::ones(500,500, CV_8UC1);
    cv::RotatedRect r2 = wp::largestRectInNonConvexPoly(*imgCopyMat, false);

    //rotatedrect to rect
    Point2f pts1[4] ;
    r2.points(pts1);
    cv::Size2f s = r2.size;
    cv::Rect re(pts1[0], pts1[2]);
    return re;

}


cv::Rect WorkingAreaExtractor::findBoundingRect(const std::vector<cv::Point>& cont){

    //find bounding rectangle of Contour
    Rect bounding_rect = boundingRect(cont);
    return  bounding_rect;
    // contour search decrease width of 1 px when image has a frame
//        return  Rect(cont[0],cv::Point(cont[2].x+1, cont[2].y+1));

}


