//
// Created by riccardo on 01/09/17.
//

#ifndef WORKPIECE_PLACEMENT_GCODEPOINTUPDATER_H
#define WORKPIECE_PLACEMENT_GCODEPOINTUPDATER_H


#include <opencv2/core/types.hpp>
#include <map>
#include <iostream>
#include <opencv2/core/mat.hpp>

#define PI 3.14159265

class GcodePointUpdater {

public:

    /**
     * @brief Constructor
     * @param gcodeSize x side and y size of gcode
     * @param vertices vertices of workpiece
     * @param rotationAngle rotation angle respect y-axis
     */
    GcodePointUpdater(cv::Size gcodeSize, cv::Point2f vertices[4], float rotationAngle, float workingAreaHeight);

    /**
     * @brief Execute the tranlation and rotation of a single point
     * @param point point to roto-translate
     * @param z the height of workpiece
     * @details Note: Execute the inversion of y-axis according to gcode coordinate system
     */
    std::array<double, 4> elaborate(std::array<double, 4> point, float z);

private:

    /**
     * @brief Vertices of worpiece in mm
     */
    const cv::Point2f *m_wpVerticesMM;

    /**
     * @brief Width and height of gcode
     */
    cv::Size m_gcodeSize;

    /**
     * Rotation angle
     */
    float m_rotationAngle;

    /**
     * @brief Vertices sorted based on the distance from origin (origin of opencv coordinate system)
     */
    std::map<float, int> m_sortedVertices;

    /**
     * @brief The point where translate origin of gcode
     */
    cv::Point2f m_translationPoint;

    /**
     * @brief The height of working area
     * @details it is needed to reverse y-axis to switch from opencv coordinate system to gcode coordinate system
     */
    float  m_workingAreaHeight;

    /**
     * @brief Find point with the smallest x
     * @return point with the smallest x
     */
    const cv::Point2f smallestX();

    /**
     * @brief Find point with the biggest y
     * @return point with the biggest y
     */
    const cv::Point2f biggestY();

    /**
     * @brief Find point with the smallest y
     * @return point with the smallest y
     */
    const cv::Point2f smallestY();

/**
     * @brief Find point with the biggest x
     * @return point with the biggest x
     */
    const cv::Point2f biggestX();

    /**
     * @brief Sort point based on their distance from opencv coordinate system origin
     * @return sorted vertices
     */
    std::map<float, int> sortVertices();

    /**
     * @brief find translation and rotation parameter
     * @details initialize m_trandlationPoint and m_rotationAngle
     */
    void rotoTranslation();

};


#endif //WORKPIECE_PLACEMENT_GCODEPOINTUPDATER_H
