//
// Created by riccardo on 10/07/17.
//

#ifndef WORKPIECE_PLACEMENT_IMAGE_H
#define WORKPIECE_PLACEMENT_IMAGE_H

#include "stdio.h"
#include "string"
#include <opencv2/opencv.hpp>

using namespace cv;

class Image {


private:

    /**
     * @brief directory separator
     */
    const std::string kPathSeparator =
    #ifdef _WIN32
                "\\";
    #else
                "/";
    #endif


    /**
     * @brief images directory relative path
     */
    const std::string img_path = ".." + kPathSeparator + "sample_imgs" + kPathSeparator;

    /**
     * @brief comparison accuracy
     *
     * @details Two image are equals if the result of histogram comparison is bigger than comparisonAccuracy; values range [0-1]
     *
     */
    const double comparisonAccuracy = 0.95;

    std::string name = "";

    cv::Mat imgMat = Mat();

public:

    /**
     * @brief Constructor
     * @param img_name
     */
    Image(std::string img_name);

    /**
     * @brief Check if the image is equal to another one
     * @param img a pointer to imagine to compare
     * @return True if equal, False otherwise
     */
    bool isEqualTo(Image *img);


    const std::string getPath() const;

    Mat getMatImg() const;


};


#endif //WORKPIECE_PLACEMENT_IMAGE_H
