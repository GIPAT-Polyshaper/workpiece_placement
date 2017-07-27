//
// Created by riccardo on 27/07/17.
//

#include "ContourDetector.h"

namespace {

    /**
     * @brief Find external contours of shapes in the image
     * @param mat opencv matrix where find contours
     * @param inv if true search contours on inverted image(find black areas contour)
     * @return vector of pointVector
     */
    std::vector<std::vector<cv::Point>> contours(const cv::Mat& mat, bool inv){

        cv::Mat mask;
        // convert to binary|binary_inverted, findContours find only contours of white areas
        (inv) ? cv::threshold(mat, mask, 0, 255,  CV_THRESH_BINARY_INV | CV_THRESH_OTSU) : threshold(mat, mask, 0, 255,  CV_THRESH_BINARY | CV_THRESH_OTSU);

        // find contours
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        return contours;
    }

}

ContourDetector::ContourDetector(const Image & img, bool inverse):
        m_contours(contours(img.getM_mat(), inverse))
{}

const std::vector<std::vector<cv::Point>> &ContourDetector::getM_contours() const {
    return m_contours;
}

/**
 *
 * @brief Find and return the contour having the biggest area
 * @throw invalid_argument exception when empty vector
 * @return the biggest contour (biggest area) in the vector
 */
std::vector<cv::Point> ContourDetector::biggestContour()
{
    std::vector<cv::Point> p;
    if(this->m_contours.size()==0)
        throw std::invalid_argument("Empty vector");
    int largest_area = 0;
    int largest_contour_index = 0;
    for (int i = 0; i < this->m_contours.size(); i++) {
        //  Find the area of Contour
        double a = contourArea(this->m_contours[i], false);
        if (a > largest_area) {
            largest_area = a;
            // Store the index of largest Contour
            largest_contour_index = i;
        }
    }
    return this->m_contours[largest_contour_index];
}
