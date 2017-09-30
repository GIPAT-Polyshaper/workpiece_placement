//
// Created by riccardo on 23/09/17.
//

#ifndef WORKPIECE_PLACEMENT_IMAGECORRECTOR_H
#define WORKPIECE_PLACEMENT_IMAGECORRECTOR_H


#include "Image.h"

class ImageCorrector {

public:

    /**
     * @brief Take an Image and correct distorsions
     * @return Undistorted image
     */
    Image elaborate(const Image &) const;

private:

    /**
    *  @brief where to read calibration parameters
    */
    const std::string filename = "calibrationParams.xml";

    /**
     * @brief Read undistortion params
     * @throw runtime_error if can't open file indicates in filename const
     * @return a vector, first element is intrinsic matrix, second is distCoeff matrix
     */
    std::vector<cv::Mat> readParams()const;

};


#endif //WORKPIECE_PLACEMENT_IMAGECORRECTOR_H
