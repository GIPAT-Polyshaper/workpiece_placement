//
// Created by riccardo on 27/07/17.
//

#ifndef WORKPIECE_PLACEMENT_CONTOURDETECTOR_H
#define WORKPIECE_PLACEMENT_CONTOURDETECTOR_H


#include "Image.h"

class ContourDetector {

public:

    /**
     * @brief Constructor
     * @param img Image where detect contours
     * @param inverse if true detect contours of the black external areas on a binary image, if false detect contours of the white  external areas on a binary image
     */
    ContourDetector(const Image & img, bool inverse);

    /**
     * @brief Get method contours member
     * @return Contour of the external area
     */
    const vector<vector<Point>> &getM_contours() const;
    
    std::vector<cv::Point> biggestContour();

private:

    std::vector<std::vector<cv::Point>> m_contours;

};


#endif //WORKPIECE_PLACEMENT_CONTOURDETECTOR_H
