//
// Created by riccardo on 30/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H
#define WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H

#include "WorkPiece.h"

class WorkPieceExtractor {

    /**
     * @brief on it will be calculated the resizing factor
     */
    const int maxMatWidth = 280;

public:

    /**
     * @brief Find the workpiece
     * @param mat matrix where look for workpiece
     * @throw runtime_error if no workpiece found
     * @return workpiece
     */
    WorkPiece elaborate(const cv::Mat &mat);


};

#endif //WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H