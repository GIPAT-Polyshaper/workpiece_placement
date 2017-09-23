//
// Created by riccardo on 23/09/17.
//

#ifndef WORKPIECE_PLACEMENT_WP_H
#define WORKPIECE_PLACEMENT_WP_H

#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

namespace wp{


    /**
     * @brief on it will be calculated the resizing factor
     */
    const int maxMatWidth = 280;

    /**
     * @brief Find largest rectangle containing only zeros in an binary matrix
     * @param src matrix where search largest rectangle
     * @return the max area rectangle inside the matrix
     */
    cv::Rect findMaxRect(const cv::Mat1b &src) {

        cv::Mat1f W(src.rows, src.cols, float(0));
        cv::Mat1f H(src.rows, src.cols, float(0));

        cv::Rect maxRect(0, 0, 0, 0);
        float maxArea = 0.f;

        for (int r = 0; r < src.rows; ++r) {
            for (int c = 0; c < src.cols; ++c) {
                if (src(r, c) == 0) {
                    H(r, c) = 1.f + ((r > 0) ? H(r - 1, c) : 0);
                    W(r, c) = 1.f + ((c > 0) ? W(r, c - 1) : 0);
                }

                float minw = W(r, c);
                for (int h = 0; h < H(r, c); ++h) {
                    minw = cv::min(minw, W(r - h, c));
                    float area = (h + 1) * minw;
                    if (area > maxArea) {
                        maxArea = area;
                        maxRect = cv::Rect(cv::Point(c - minw + 1, r - h), cv::Point(c + 1, r + 1));
                    }
                }
            }
        }

        return maxRect;
    }


        /**
    * @brief Find largest rotated rectangle containing only ones in an binary matrix
    * @details code took from here: https://stackoverflow.com/questions/32674256/how-to-adapt-or-resize-a-rectangle-inside-an-object-without-including-or-with-a/32682512
    * @param src2 matrix where search largest rectangle
    * @return largest rotated rect
    */
    cv::RotatedRect largestRectInNonConvexPoly(const cv::Mat1b &src2) {

        float resizingFactor = (float)src2.cols/(float)maxMatWidth;
        cv::Mat1b src;
        cv::resize(src2, src, cv::Size(), 1/resizingFactor, 1/resizingFactor, cv::INTER_LINEAR);
        threshold(src, src, 0, 255,  CV_THRESH_BINARY | CV_THRESH_OTSU);

        // Create a matrix big enough to not lose points during rotation
        std::vector<cv::Point> ptz;
        findNonZero(src, ptz);
        cv::Rect bbox = cv::boundingRect(ptz);
        int maxdim = cv::max(bbox.width, bbox.height);
        cv::Mat1b work(2 * maxdim, 2 * maxdim, uchar(0));
        src(bbox).copyTo(work(cv::Rect(maxdim - bbox.width / 2, maxdim - bbox.height / 2, bbox.width, bbox.height)));

        // Store best data
        cv::Rect bestRect;
        int bestAngle = 0;

        // For each angle
        for (int angle = 0; angle < 90; angle++) {

            // Rotate the image
            cv::Mat R = cv::getRotationMatrix2D(cv::Point(maxdim, maxdim), angle, 1);
            cv::Mat1b rotated;
            warpAffine(work, rotated, R, work.size());

            // Keep the crop with the polygon
            std::vector<cv::Point> pts;
            findNonZero(rotated, pts);
            cv::Rect box = boundingRect(pts);
            cv::Mat1b crop = rotated(box).clone();

            // Invert colors
            crop = ~crop;

            // Solve the problem: "Find largest rectangle containing only zeros in an binary matrix"
            // https://stackoverflow.com/questions/2478447/find-largest-rectangle-containing-only-zeros-in-an-n%C3%97n-binary-matrix
            cv::Rect r = findMaxRect(crop);
            // If best, save result
            if (r.area() > bestRect.area()) {
                bestRect = r + box.tl();    // Correct the crop displacement
                bestAngle = angle;
            }
        }

        // Apply the inverse rotation
        cv::Mat Rinv = cv::getRotationMatrix2D(cv::Point(maxdim, maxdim), -bestAngle, 1);
        std::vector<cv::Point> rectPoints{bestRect.tl(), cv::Point(bestRect.x + bestRect.width, bestRect.y), bestRect.br(),
                                          cv::Point(bestRect.x, bestRect.y + bestRect.height)};
        std::vector<cv::Point> rotatedRectPoints;
        transform(rectPoints, rotatedRectPoints, Rinv);

        // Apply the reverse translations
        for (int i = 0; i < rotatedRectPoints.size(); ++i)
        {
            rotatedRectPoints[i] += bbox.tl() - cv::Point(maxdim - bbox.width / 2, maxdim - bbox.height / 2);
        }

        // Get the rotated rect
        cv::RotatedRect rrect = minAreaRect(rotatedRectPoints);

        rrect.center = cv::Point(rrect.center.x * resizingFactor, rrect.center.y * resizingFactor);

        rrect.size = cv::Size(rrect.size.width * resizingFactor, rrect.size.height * resizingFactor);

        return rrect;
    }

}

#endif //WORKPIECE_PLACEMENT_WP_H
