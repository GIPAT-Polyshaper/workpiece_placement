//
// Created by riccardo on 30/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H
#define WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H

//TODO what happend if no workpiece found?????????

#include "WorkPiece.h"
#include "ContourDetector.h"
#include "BiggestContourFinder.h"


class WorkPieceExtractor {

    /**
     * @brief on it will be calculated the resizing factor
     */
    const int maxMatWidth = 280;

public:

    /**
     * @brief Find the workpiece
     * @param mat matrix where look for workpiece
     * @return workpiece
     */
    WorkPiece elaborate(const cv::Mat &mat);


};


#endif //WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H
