//
// Created by riccardo on 27/07/17.
//

#include "WorkingAreaExtractor.h"


const Rect WorkingAreaExtractor::elaborate(const Image& img)
{

    return findBoundingRect(BiggestContourFinder().elaborate(ContourDetector().contours(img.getM_mat(), true)));

}


cv::Rect WorkingAreaExtractor::findBoundingRect(const std::vector<cv::Point>& cont){

    //find bounding rectangle of Contour
    Rect bounding_rect = boundingRect(cont);
    return  bounding_rect;
    // contour search decrease width of 1 px when image has a frame
//        return  Rect(cont[0],cv::Point(cont[2].x+1, cont[2].y+1));

}


