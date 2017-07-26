//
// Created by riccardo on 19/07/17.
//

#include "WorkingArea.h"

namespace {

    /**
     * @brief Find contours of shapes in the image
     * @param mat opencv matrix where find contours
     * @return vector of pointVector
     */
    std::vector<WorkingArea::pointVector> contours(const cv::Mat& mat){
        // convert to binary inverted, findContours find only contours of white area but background is black
        cv::Mat mask;
        cv::threshold(mat, mask, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

        // find contours
        std::vector<WorkingArea::pointVector> contours;
        cv::findContours(mask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        return contours;
    }

    /**
     *
     * @brief Find and return the contour with the biggest area
     * @param contours vector of pointVector
     * @throw invalid_argument exception when empty vector passed
     * @return the biggest contour (biggest area) in the vector
     */
    WorkingArea::pointVector biggestAreaContour(std::vector<WorkingArea::pointVector> contours)
    {
        WorkingArea::pointVector p;
        if(contours.size()==0)
            throw std::invalid_argument("Empty vector");
        int largest_area = 0;
        int largest_contour_index = 0;
        for (int i = 0; i < contours.size(); i++) {
            //  Find the area of Contour
            double a = contourArea(contours[i], false);
            if (a > largest_area) {
                largest_area = a;
                // Store the index of largest Contour
                largest_contour_index = i;
            }
        }
        return contours[largest_contour_index];
    }

}

WorkingArea::WorkingArea(const cv::Mat& mat) : m_rect(cv::boundingRect(biggestAreaContour(contours(mat)))) {}

 int WorkingArea::workingAreaWidth() {
    return this->m_rect.width;
}

 int WorkingArea::workingAreaHeight() {
    return this->m_rect.height;
}

cv::Point_<int> WorkingArea::getTopLeft()const {
    return this->m_rect.tl();
}

cv::Point_<int> WorkingArea::getBottomRight() const {
    return this->m_rect.br();
}

WorkingArea::WorkingArea(const cv::Mat &mat, const WorkPiece &piece): m_rect(cv::Rect(0, 0, mat.size().width, mat.size().height)),
                                                                      m_workPiece(piece)
{}

const WorkPiece &WorkingArea::getM_workPiece() const {
    return m_workPiece;
}

const cv::Rect &WorkingArea::getM_rect() const {
    return m_rect;
}
