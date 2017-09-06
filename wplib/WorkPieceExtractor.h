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

private:

    /**
     * @brief Find largest rectangle containing only zeros in an binary matrix
     * @param src matrix where search largest rectangle
     * @return the max area rectangle inside the matrix
     */
    cv::Rect findMaxRect(const cv::Mat1b &src);

    /**
    * @brief Find largest rotated rectangle containing only ones in an binary matrix
    * @details code took from here: https://stackoverflow.com/questions/32674256/how-to-adapt-or-resize-a-rectangle-inside-an-object-without-including-or-with-a/32682512
    * @param src2 matrix where search largest rectangle
    * @return largest rotated rect
    */
    cv::RotatedRect largestRectInNonConvexPoly(const cv::Mat1b &src2);

};


#endif //WORKPIECE_PLACEMENT_WORKPIECEEXTRACTOR_H
