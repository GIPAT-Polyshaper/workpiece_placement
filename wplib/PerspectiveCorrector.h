//
// Created by riccardo on 16/08/17.
//

#ifndef WORKPIECE_PLACEMENT_PERSPECTIVECORRECTOR_H
#define WORKPIECE_PLACEMENT_PERSPECTIVECORRECTOR_H


#include "Image.h"
#include "ContourDetector.h"
#include "BiggestContourFinder.h"

class PerspectiveCorrector {

private:

    /**
     * @brief How many pixels add to corrected image
     */
    const int offsetSize = 300;

    /**
     * @brief Allow to keep the aspect ratio
     */
    const float aspectRatio = 1.6;

public:

    /**
     * @brief Take a image and apply a perspective correction of the biggest black area inside the image
     * @param img Image to correct
     * @return Image corrected image
     */
    Image correctedImage(const Image & img);

};


#endif //WORKPIECE_PLACEMENT_PERSPECTIVECORRECTOR_H
