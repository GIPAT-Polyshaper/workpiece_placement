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
     * @brief comparison accuracy
     *
     * @details Two image are equals if the result of histogram comparison is bigger than comparisonAccuracy; values range [0-1]
     *
     */
    const double comparisonAccuracy = 0.95;

    std::string m_name = "";

    cv::Mat m_mat;


public:


    /**
     * @brief Constructor
     * @param img_name name of the image
     * @param mat matrix
     */
    Image(std::string img_name, Mat mat);

    /**
     * @brief Constructor
     * @param mat matrix
     */
    Image(cv::Mat mat);

    /**
     * @brief Check if the image is equal to another one
     * @param img a pointer to image to compare
     * @return True if equal, False otherwise
     */
    bool isEqualTo(const Image &);

    /**
     * @brief get method for the name
     * @return string, name of the Image
     */
    const std::string &getM_name() const;

    /**
     * @brief shows the image in a fixed size window
     */
    void showImg();

    /**
     * @brief get method for matrix member
     * @return matrix of current Image
     */
    const Mat& getM_mat() const;

};


#endif //WORKPIECE_PLACEMENT_IMAGE_H
