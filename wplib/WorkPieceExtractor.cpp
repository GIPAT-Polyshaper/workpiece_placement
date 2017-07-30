//
// Created by riccardo on 30/07/17.
//

#include "WorkPieceExtractor.h"
#include "ContourDetector.h"
#include "BiggestContourFinder.h"

WorkPiece WorkPieceExtractor::workpiece(const cv::Mat &mat) {
    std::vector<std::vector<cv::Point>> contours = ContourDetector().contours(mat, false);
    std::vector<cv::Point> biggestContour = BiggestContourFinder().biggestContour(contours);
    cv::Rect r = cv::boundingRect(biggestContour);
    return WorkPiece(Point(r.tl().x, r.br().y), 0.0, r.width, r.height);
}
