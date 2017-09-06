//
// Created by riccardo on 27/07/17.
//

#ifndef WORKPIECE_PLACEMENT_IMAGECUTTER_H
#define WORKPIECE_PLACEMENT_IMAGECUTTER_H


#include "Image.h"

class ImageCutter {

public:

    /**
     * @brief Crops an image based on the rectangle passed
     * @param img Image to be cropped
     * @param r Define the cropping area
     * @return Cropped image
     */
    const Image elaborate(const Image &img, const Rect &r);

private:

    /**
     * @brief Remove extension and add Cut in the filename then add extension back
     * @param filename name of the image
     * @return name of the cropped image
     */
    std::string nameComposer(const std::string& filename);

    /**
     * @brief crop image
     * @param mat image to be cropped
     * @param rect cropping rectangle
     * @return cropped image
     */
    Image imageCut(const Image & img, const cv::Rect& rect);

    /**
     * @brief crop image
     * @param mat image matrix to be cropped
     * @param area cropping area
     * @return cropped image
     */
    Image imageCut(const Mat &mat, std::vector<std::vector<cv::Point>> area);

};


#endif //WORKPIECE_PLACEMENT_IMAGECUTTER_H
