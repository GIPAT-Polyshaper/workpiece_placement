//
// Created by riccardo on 23/08/17.
//

#ifndef WORKPIECE_PLACEMENT_PIXELSTOMETRIC_H
#define WORKPIECE_PLACEMENT_PIXELSTOMETRIC_H

#include <bits/functexcept.h>

class PixelsToMetric {

private:

    /**
     * @brief known dimension in millimeters
     * @details working area width
     */
    const float mmKnownSize = 310.0;

    /**
     * @brief pixels per metric ratio
     */
    float pixelsPerMetricRatio;


public:

    /**
     * @brief Converts pixels in mm
     * @param pixels dimesion in pixels
     * @throw invalid argument exception if the provided dimension is negative
     * @return dimension in mm
     */
    float elaborate(int pixels);

    /**
     * @brief Constructor
     * @param pxSizeReferenceObject The size in pixels of the reference object whose length in mm is known
     * @throw invalid argument exception if working area width in mm is zero
     */
    PixelsToMetric(int pxSizeReferenceObject);
};


#endif //WORKPIECE_PLACEMENT_PIXELSTOMETRIC_H
