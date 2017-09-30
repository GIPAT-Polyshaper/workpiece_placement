//
// Created by riccardo on 30/09/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKINGAREASAVER_H
#define WORKPIECE_PLACEMENT_WORKINGAREASAVER_H


#include <opencv2/core/types.hpp>

class WorkingAreaSaver {

private:

    const std::string workingAreaFile = "workingArea.xml";

public:

    void elaborate(const cv::Rect &rect) const;

};


#endif //WORKPIECE_PLACEMENT_WORKINGAREASAVER_H
