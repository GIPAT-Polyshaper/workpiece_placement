//
// Created by riccardo on 27/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H
#define WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H


#include "Image.h"

class WorkingAreaExtractor {

public:
//
//    struct WorkingArea{
//
//        WorkingArea(int x, int y , int width, int height):
//                x(x),
//                y(y),
//                width(width),
//                height(height)
//        {}
//        
//        WorkingArea(const WorkingArea& a):
//                x(a.x),
//                y(a.y),
//                width(a.width),
//                height(a.height)
//        {}
//
//        int x;
//        int y;
//        int width;
//        int height;
//
//    };
//
//    using WorkingArea;

    cv::Rect m_workingArea;

public:

    WorkingAreaExtractor(const Image &img);

    const cv::Rect &getM_workingArea() const;
};


#endif //WORKPIECE_PLACEMENT_WORKINGAREAEXTRACTOR_H
