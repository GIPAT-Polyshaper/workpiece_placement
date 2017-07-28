//
// Created by riccardo on 27/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H
#define WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H


#include "Image.h"

class WorkingAreaExtractor {

public:

    cv::Rect m_workingArea;

public:

    /**
     * @brief constructor
     * @param img image where search working area
     */
    WorkingAreaExtractor(const Image &img);

    /**
     * @brief Get method workingArea member
     * @return rectangle representing working area
     */
    const cv::Rect &getM_workingArea() const;
};


#endif //WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H
