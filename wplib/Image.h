//
// Created by riccardo on 10/07/17.
//

#ifndef WORKPIECE_PLACEMENT_IMAGE_H
#define WORKPIECE_PLACEMENT_IMAGE_H

#include "stdio.h"
#include "string"
#include "WorkingArea.h"
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
    const std::string img_path = ".." + kPathSeparator + ".." + kPathSeparator + "sample_imgs" + kPathSeparator;

    /**
     * @brief comparison accuracy
     *
     * @details Two image are equals if the result of histogram comparison is bigger than comparisonAccuracy; values range [0-1]
     *
     */
    const double comparisonAccuracy = 0.95;

    std::string m_name = "";

    cv::Mat m_mat;

    WorkingArea m_workingArea;

private:

    /**
     * @brief Read an image
     * @param img_name Name of the image to read
     * @throw invalid_argument exception when image is not found
     * @return Matrix
     */
    cv::Mat readImage(std::string img_name);

public:

    /**
     * @brief Constructor
     * @throw invalid_argument exception when image is not found
     * @param img_name name of the image
     */
    Image(std::string img_name);

    /**
     * @brief Constructor
     * @param img_name name of the image
     * @param mat matrix
     */
    Image(std::string img_name, Mat mat);

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
    const std::string getName() const;

    /**
     * @brief get method for the image path
     * @return string, path of the Image
     */
    const std::string getPath() const;

    /**
     * @brief shows the image in a fixed size window
     */
    void showImg();

    /**
     * @brief draw working area
     */
    void drawWorkingArea();

    /**
     * @brief get method for matrix member
     * @return matrix of current Image
     */
    const Mat& getImgMat() const;

    /**
     * @brief get methif for the working area member
     * @return working area
     */
    const WorkingArea &getWorkingArea() const;

    Image extractWorkingArea();
};


#endif //WORKPIECE_PLACEMENT_IMAGE_H
