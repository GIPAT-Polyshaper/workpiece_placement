//
// Created by riccardo on 25/07/17.
//

#ifndef WORKPIECE_PLACEMENT_WORKPIECE_H
#define WORKPIECE_PLACEMENT_WORKPIECE_H


#include <ml.h>

class WorkPiece {

private:

    cv::Point m_point;
    float m_angle;
    int m_width;
    int m_height;


public:

    /**
     * @brief Constructor
     * @param m_point Top left corner point
     * @param m_angle the angle between working piece side and working area side
     * @param m_width The width of the piece
     * @param m_height The height of the piece
     */
    WorkPiece(const cv::Point &m_point = cv::Point(), float m_angle=0, int m_width=0, int m_height=0);

    /**
     * @brief constructor
     * @param rRect rotated rectangle
     */
    WorkPiece(const cv::RotatedRect rRect);

    /**
     * @brief Get method for first point member
     * @return first point(top left) of working piece
     */
    const cv::Point &getM_point() const;


    /**
     * @brief Get method for angle member
     * @return angle between working piece side and working area side
     */
    float getM_angle() const;

    /**
     * @brief Get method for width member
     * @return The width of the piece
     */
    int getM_width() const;
    
    /**
     * @brief Get method for height member
     * @return The height of the piece
     */
    int getM_height() const;

    /**
     * @brief Set method for top right corner of the piece
     * @param x X coordinate of the point
     * @param y Y coordinate of the point
     */
    void setM_point(int x, int y);

    /**
     * @brief Set method for angle member
     * @param m_angle the angle between working piece side and working area side
     */
    void setM_angle(float m_angle);

    /**
    * @brief Set method for height member
    * @param m_width The width of the piece
    */
    void setM_width(int m_width);

    /**
     * @brief Set method for height member
     * @return The height of the piece
     */
    void setM_height(int m_height);

};


#endif //WORKPIECE_PLACEMENT_WORKPIECE_H
