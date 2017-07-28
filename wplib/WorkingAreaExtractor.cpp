//
// Created by riccardo on 27/07/17.
//

#include "WorkingAreaExtractor.h"
#include "Image.h"
#include "ContourDetector.h"
#include "BiggestContourFinder.h"

namespace {

    /**
     * @brief find bunding rectangle
     * @param cont contour of the shape
     * @return rectangle bounding the passed contour
     */
    cv::Rect findBundingRect(std::vector<cv::Point> cont){

        //find bounding rectangle of Contour
        Rect bounding_rect = boundingRect(cont);
        return  bounding_rect;
        // contour search decrease width of 1 px when image has a frame
//        return  Rect(cont[0],cv::Point(cont[2].x+1, cont[2].y+1));

        //TODO in image with no frame width and height are reduced of 3px
    }


}


WorkingAreaExtractor::WorkingAreaExtractor(const Image & img):
        m_workingArea(findBundingRect(BiggestContourFinder().biggestContour(ContourDetector().contours(img.getM_mat(), true)))) {}

const cv::Rect &WorkingAreaExtractor::getM_workingArea() const {
    return this->m_workingArea;
}
