//
// Created by riccardo on 19/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKINGAREA_H
#define WORKPIECE_PLACEMENT_WORKINGAREA_H


#include <vector>
#include <opencv2/opencv.hpp>
#include "WorkPiece.h"

class WorkingArea {

public:
    /**
     * @brief Constructor of WorkingArea class
     * @throw invalid_argument exception when no working area found
     * @param Image of which find working area
     */
    WorkingArea(const cv::Mat&);
    /**
     * @brief Constructor of WorkingArea class
     * @param mat opencv matrix
     * @param piece workpiece inside working area 
     */
    WorkingArea(const cv::Mat &mat, const WorkPiece &piece);

public:

    /**
   * @brief The type of the list of contours
   */
    using pointVector = std::vector<cv::Point>;

    /**
     * @brief Get the top left corner of the working area
     * @return Point: top left corner of the working area
     */
    cv::Point_<int> getTopLeft()const;

    /**
     *@brief Get the bottom right corner of the working area
     * @return Point: bottom right corner of the working area
     */
    cv::Point_<int> getBottomRight() const;
    
    /**
     * @brief Get method contour member
     * @return contour of the working area
     */
    const cv::Rect &getM_rect() const;

    /**
     * @brief Get method for the work piece member
     * @return work piece member
     */
    const WorkPiece &getM_workPiece() const;

    /**
     * Working area width
     * @return Working area width
     */
     int workingAreaWidth();

     /**
      * Working area height
      * @return Working area height
      */
     int workingAreaHeight();

private:

    const cv::Rect m_rect;
    const WorkPiece m_workPiece;

};


#endif //WORKPIECE_PLACEMENT_WORKINGAREA_H
