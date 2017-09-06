//
// Created by riccardo on 28/07/17.
//

#include "BiggestContourFinder.h"

std::vector<cv::Point> BiggestContourFinder::elaborate(const std::vector<std::vector<cv::Point>> &contours) const
{
    std::vector<cv::Point> p;
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
    std::vector<cv::Point> t = contours[largest_contour_index];
    return t;
}
