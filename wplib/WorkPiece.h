//
// Created by riccardo on 25/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKPIECE_H
#define WORKPIECE_PLACEMENT_WORKPIECE_H


#include <ml.h>

class WorkPiece {

private:

    /**
     * @brief center point
     */
    cv::Point m_centerPoint;

    /**
     * @brief vertices of the workpiece
     */
    cv::Point m_vertices[4] = {cv::Point(0,0), cv::Point(0,0), cv::Point(0,0), cv::Point(0,0)};


private:

    /**
     * @brief Angle of rotation [0,180)
     * @details The angle between y-axis and the long side
     */
    float m_angle;

    /**
     * @brief longest side of workpiece
     */
    int m_longSide;

    /**
     * @brief shortest side of workpiece
     */
    int m_shortSide;


public:

    /**
     * @brief Constructor
     * @param point Top left corner point
     * @param angle the angle between working piece long side and y-axis 0-180
     * @param longSide The long side of the piece
     * @param shortSide The short side of the piece
     */
    WorkPiece(const cv::Point & point = cv::Point(), float angle=0, int longSide=0, int shortSide=0);

    /**
     * @brief constructor
     * @param rRect rotated rectangle
     */
    WorkPiece(const cv::RotatedRect& rRect);

    /**
     * @brief Get method for first point member
     * @return first point(top left) of working piece
     */
    const cv::Point &getCenterPoint() const;

    /**
     * @brief Get method for angle member
     * @return angle between working piece side and working area side
     */
    float getAngle() const;

    /**
     * @brief Get method for long side member
     * @return The long side of the piece
     */
    int getLongSide() const;
    
    /**
     * @brief Get method for short side member
     * @return The short side of the piece
     */
    int getShortSide() const;

    /**
     * @brief Get method for vertices member
     * @return Array of point representing vertices of workpiece
     */
    const cv::Point *getVertices() const;

    /**
     * @brief Set method for the center point of the piece
     * @param x X coordinate of the point
     * @param y Y coordinate of the point
     */
    void setCenterPoint(int x, int y);

    /**
     * @brief Set method for angle member
     * @param m_angle the angle between working piece side and working area side
     */
    void setAngle(float m_angle);

    /**
    * @brief Set method for long side member
    * @param longSide The longSide of the piece
    */
    void setLongSide(int longSide);

    /**
     * @brief Set method for short side member
     * @param shortSide The short side of the piece
     */
    void setShortSide(int shortSide);

};


#endif //WORKPIECE_PLACEMENT_WORKPIECE_H
