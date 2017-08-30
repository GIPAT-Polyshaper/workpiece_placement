//
// Created by riccardo on 28/07/17.
//

#ifndef WORKPIECE_PLACEMENT_BIGGESTCONTOURFINDER_H
#define WORKPIECE_PLACEMENT_BIGGESTCONTOURFINDER_H


#include <vector>
#include <opencv2/opencv.hpp>

class BiggestContourFinder {

public:
    
    /**
     * @brief Find and return the contour having the biggest area
     * @throw invalid_argument exception when empty vector
     * @return the biggest contour (biggest area) in the vector
     */
    std::vector <cv::Point> biggestContour(const std::vector <std::vector<cv::Point>>& vector) const;
};


#endif //WORKPIECE_PLACEMENT_BIGGESTCONTOURFINDER_H
