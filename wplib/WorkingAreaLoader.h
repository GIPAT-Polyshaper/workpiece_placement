//
// Created by riccardo on 30/09/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKINGAREALOADER_H
#define WORKPIECE_PLACEMENT_WORKINGAREALOADER_H


#include <opencv2/core/types.hpp>

class WorkingAreaLoader {

private:
    const std::string workingAreaFile = "workingArea.xml";

public:

    cv::Rect elaborate() const;


};


#endif //WORKPIECE_PLACEMENT_WORKINGAREALOADER_H
