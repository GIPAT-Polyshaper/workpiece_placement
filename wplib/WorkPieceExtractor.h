//
// Created by riccardo on 30/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H
#define WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H

//TODO what happend if no workpiece found?????????

#include "WorkPiece.h"

class WorkPieceExtractor {

public:

    /**
     * @brief Find the workpiece
     * @param mat matrix where look for workpiece
     * @return workpiece
     */
    WorkPiece workpiece(const cv::Mat & mat);

};


#endif //WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H
