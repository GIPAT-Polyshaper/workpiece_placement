//
// Created by riccardo on 16/08/17.
//

#include "PerspectiveCorrector.h"
#include "wp.h"

namespace {

    /**
     * @brief Sort polygon vertices
     * @param vector vertices of a polygon
     * @param center polygon center
     * @return sorted vertices
     */
    std::map<float, Point2f> sortVertices(std::vector<std::vector<cv::Point>> vector, cv::Point center) {

        std::map<float, cv::Point2f> pointsMap;

        for (int i = 0; i <4 ; ++i) {
            float angle = atan2(center.y - vector[0][i].y, center.x - vector[0][i].x);
            float deg = angle * (180.0/3.14);
            (deg >=0 ? : deg = 360 + deg);
            pointsMap[deg] = cv::Point2f(vector[0][i].x, vector[0][i].y );
        }

        return pointsMap;

    }
}

Image PerspectiveCorrector::correctedImage(const Image &img) {

    //Find contour
    Mat src = img.getMat();
    const std::vector<cv::Point> &bc = wp::biggestContourFinder(wp::contourDetector(src, true));
    std::vector<std::vector<cv::Point>> p;
    p.push_back(bc);

    //find aproximated polygon
    std::vector<std::vector<cv::Point> > contours_poly(1);
    approxPolyDP( Mat(bc), contours_poly[0], 30, true );

    cv::Rect boundRect(boundingRect(bc));

    //keep original aspect ratio
    boundRect.height = static_cast<int>(boundRect.width / aspectRatio);

    std::vector<Point2f> quad_pts;
    std::vector<Point2f> squre_pts;

    squre_pts.emplace_back(boundRect.x,boundRect.y);
    squre_pts.emplace_back(boundRect.x+boundRect.width,boundRect.y);
    squre_pts.emplace_back(boundRect.x+boundRect.width,boundRect.y+boundRect.height);
    squre_pts.emplace_back(boundRect.x,boundRect.y+boundRect.height);

    std::map<float, cv::Point2f> pointsMap = sortVertices(contours_poly, Point((boundRect.x + boundRect.width)/2, (boundRect.y + boundRect.height)/2));

    for(auto elem : pointsMap)
    {
        quad_pts.push_back(elem.second);
    }

    //find tranformation matrix
    Mat transmtx = getPerspectiveTransform(quad_pts,squre_pts);
    Mat transformed = Mat::zeros(boundRect.height + offsetSize, boundRect.width + offsetSize, CV_8UC1);

    //apply trasformation
    warpPerspective(img.getMat(), transformed, transmtx, transformed.size());

    Image imgCorrected("correctedImage",transformed);
    return imgCorrected;

}


