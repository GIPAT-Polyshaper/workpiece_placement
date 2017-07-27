//
// Created by riccardo on 27/07/17.
//

#include "WorkingAreaExtractor.h"
#include "Image.h"
#include "ContourDetector.h"

namespace {

    cv::Rect pointVectorToRect(std::vector<cv::Point> cont){
        // contour search decrease width of 1 px when image has a frame
        return  Rect(cont[0],cv::Point(cont[2].x+1, cont[2].y+1));

        //TODO in image with no frame width and height are reduced of 3px
    }

}


WorkingAreaExtractor::WorkingAreaExtractor(const Image & img):
        m_workingArea(pointVectorToRect(ContourDetector(img, true).biggestContour())) {}

const cv::Rect &WorkingAreaExtractor::getM_workingArea() const {
    return m_workingArea;
}
