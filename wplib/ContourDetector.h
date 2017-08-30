//
// Created by riccardo on 27/07/17.
//

#ifndef WORKPIECE_PLACEMENT_CONTOURDETECTOR_H
#define WORKPIECE_PLACEMENT_CONTOURDETECTOR_H


#include "Image.h"

class ContourDetector {

public:
    
    /**
     * @brief Find external contours of shapes in the image
     * @param mat opencv matrix where find contours
     * @param inv if true search contours on inverted image(find black areas contour)
     * @return vector of pointVector
     */
    std::vector<std::vector<cv::Point>> contours(const cv::Mat &mat, bool inv) const;
    
};


#endif //WORKPIECE_PLACEMENT_CONTOURDETECTOR_H
