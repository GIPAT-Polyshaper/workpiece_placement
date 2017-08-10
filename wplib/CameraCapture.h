//
// Created by riccardo on 10/08/17.
//

#ifndef WORKPIECE_PLACEMENT_CAMERACAPTURE_H
#define WORKPIECE_PLACEMENT_CAMERACAPTURE_H

#include <opencv2/opencv.hpp>

class CameraCapture {

public:
    int m_camera = 0;

public:

    /**
     * @brief Constructor
     * @param cam camera identifier
     */
    CameraCapture(int cam);

    /**
     * @brief Capture a frame from camera pressing "s" key, exit pressing "Esc" key
     * @return opencv matrix captured
     */
    cv::Mat capturing();

};


#endif //WORKPIECE_PLACEMENT_CAMERACAPTURE_H
