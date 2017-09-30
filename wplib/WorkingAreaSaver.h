//
// Created by riccardo on 30/09/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKINGAREASAVER_H
#define WORKPIECE_PLACEMENT_WORKINGAREASAVER_H


#include <opencv2/core/types.hpp>
#include <iostream>
#include <opencv2/core/persistence.hpp>

class WorkingAreaSaver {

private:

    /**
     * @brief indicates where to store working are attributes
     * @note should be the same value of the constant workingAreaFile in WorkingAreaLoader class
     */
    const std::string workingAreaFile = "workingArea.xml";

public:

    /**
     * @brief Store rect members in the file indicates by workingAreaFile constant
     * @throw runtime_error if can't open the file indicated in workingAreaFile constant
     * @param rect The rect representing working area
     */
    void elaborate(const cv::Rect &rect) const;

};


#endif //WORKPIECE_PLACEMENT_WORKINGAREASAVER_H
