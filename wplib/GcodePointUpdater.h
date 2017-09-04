//
// Created by riccardo on 01/09/17.
//

#ifndef WORKPIECE_PLACEMENT_GCODEPOINTUPDATER_H
#define WORKPIECE_PLACEMENT_GCODEPOINTUPDATER_H


#include <opencv2/core/types.hpp>

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
     */
    std::array<double, 4> elaborate(std::array<double, 4> point, float z);

private:

    const cv::Point2f *m_wpVerticesMM;
    cv::Size m_gcodeSize;
    float m_rotationAngle;
    std::map<float, int> m_sortedVertices;
    cv::Point2f m_translationPoint;
    float  m_workingAreaHeight;

    const cv::Point2f smallestX();

    const cv::Point2f biggestY();
    /**
     * @brief Sort point
     * @return sorted vertices
     */
    std::map<float, int> sortVertices();

    /**
     * @brief find translation and rotation parameter
     * @return translated gcode origin point
     */
    void rotoTranslation();

    const cv::Point2f smallestY();
};


#endif //WORKPIECE_PLACEMENT_GCODEPOINTUPDATER_H
