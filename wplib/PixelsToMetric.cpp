//
// Created by riccardo on 23/08/17.
//

#include <bits/functexcept.h>
#include "PixelsToMetric.h"

float PixelsToMetric::MMConversion(int pixels) {
    if(pixels>0)
    return pixels/pixelsPerMetricRatio;
    else
        std::__throw_invalid_argument("pixel dimension could not be negative");
}

PixelsToMetric::PixelsToMetric(int pxSizeReferenceObject)
{
    if(mmKnownSize)
        pixelsPerMetricRatio = float(pxSizeReferenceObject)/mmKnownSize;
    else
        std::__throw_invalid_argument("The known size could not be zero");
}
