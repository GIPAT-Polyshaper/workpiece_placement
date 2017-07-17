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
    const std::string img_path = ".." + kPathSeparator + ".." + kPathSeparator + "sample_imgs" + kPathSeparator;

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
    bool isEqualTo(Image *img);

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
     * get method for the matrix
     * @return matrix of the image
     */
    Mat getMatImg() const;

    /**
     * @brief remove everything is outside the worktop
     * @details if the shot is larger than worktop removes everything is outside. Worktop must be black!
     * @return Image cropped image
     */
    Image clean();

//    Image * grayScale();

/**
 * @brief Find contours of shapes in the image
 * @return array of contours
 */
    vector<vector<Point>> contours();

/**
 * @brief Find and return the contour with the biggest area
 * @param contours vector of contours
 * @return the biggest contour (biggest area) in the vector
 */
    vector<Point> biggestAreaContour(vector<vector<Point>> contours);
};


#endif //WORKPIECE_PLACEMENT_IMAGE_H
