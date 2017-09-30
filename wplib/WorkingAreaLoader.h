//
// Created by riccardo on 30/09/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKINGAREALOADER_H
#define WORKPIECE_PLACEMENT_WORKINGAREALOADER_H

#include <opencv2/core/persistence.hpp>
#include <opencv2/core/types.hpp>

class WorkingAreaLoader {

private:

    /**
     * @brief indicates what file to read
     * @note should be the same value of the constant workingAreaFile in WorkingAreaSaver class
     */
    const std::string workingAreaFile = "workingArea.xml";

public:

    /**
     * @brief Load info from file indicates in workingAreaFile constant to build a rect object and return it
     * @throw runtime_error if can't open the file indicated in workingAreaFile constant
     * @return the rect representing working area
     */
    cv::Rect elaborate() const;


};


#endif //WORKPIECE_PLACEMENT_WORKINGAREALOADER_H
