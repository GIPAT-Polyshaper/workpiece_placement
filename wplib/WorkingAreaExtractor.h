//
// Created by riccardo on 27/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H
#define WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H

#include "Image.h"

class WorkingAreaExtractor {

public:

    /**
     * @brief Find working area inside an Image
     * @param img Image where search working Area
     * @return rectangle representing working area
     */
    Rect elaborate(const Image& img);

private:

  /**
   * @brief find bounding rectangle
   * @param cont contour of the shape
   * @return rectangle bounding the passed contour
   */
    cv::Rect findBoundingRect(const std::vector<cv::Point>& cont);

};


#endif //WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H
