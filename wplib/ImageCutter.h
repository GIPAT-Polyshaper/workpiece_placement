//
// Created by riccardo on 27/07/17.
//

#ifndef WORKPIECE_PLACEMENT_IMAGECUTTER_H
#define WORKPIECE_PLACEMENT_IMAGECUTTER_H


#include "Image.h"

class ImageCutter {

private:

    Image m_image;

public:

    /**
     * @brief constructo
     * @param img image to be cropped
     * @param r cropping area
     */
    ImageCutter(const Image& img, const cv::Rect & r);

    /**
     * @brief Get method image member
     * @return
     */
    const Image &getM_image() const;

};


#endif //WORKPIECE_PLACEMENT_IMAGECUTTER_H
