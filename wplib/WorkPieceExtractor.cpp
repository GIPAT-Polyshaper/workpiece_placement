//
// Created by riccardo on 30/07/17.
//

#include "WorkPieceExtractor.h"
#include "ContourDetector.h"
#include "BiggestContourFinder.h"




namespace {


    /**
     * @brief on it will be calculate the resizing factor
     */
    const int maxMatWidth = 280;

    /**
     * @brief Find largest rectangle containing only zeros in an binary matrix
     * @param src matrix where search largest rectangle
     * @return the max area rectangle inside the matrix
     */
    Rect findMaxRect(const Mat1b &src) {

        Mat1f W(src.rows, src.cols, float(0));
        Mat1f H(src.rows, src.cols, float(0));

        Rect maxRect(0, 0, 0, 0);
        float maxArea = 0.f;

        for (int r = 0; r < src.rows; ++r) {
            for (int c = 0; c < src.cols; ++c) {
                if (src(r, c) == 0) {
                    H(r, c) = 1.f + ((r > 0) ? H(r - 1, c) : 0);
                    W(r, c) = 1.f + ((c > 0) ? W(r, c - 1) : 0);
                }

                float minw = W(r, c);
                for (int h = 0; h < H(r, c); ++h) {
                    minw = min(minw, W(r - h, c));
                    float area = (h + 1) * minw;
                    if (area > maxArea) {
                        maxArea = area;
                        maxRect = Rect(Point(c - minw + 1, r - h), Point(c + 1, r + 1));
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
    RotatedRect largestRectInNonConvexPoly(const Mat1b &src2) {

        float resizingFactor = (float)src2.cols/(float)maxMatWidth;
        cv::Mat1b src;
        resize(src2, src, Size(), 1/resizingFactor, 1/resizingFactor, INTER_LINEAR);
        threshold(src, src, 0, 255,  CV_THRESH_BINARY | CV_THRESH_OTSU);

        // Create a matrix big enough to not lose points during rotation
        std::vector<Point> ptz;
        findNonZero(src, ptz);
        Rect bbox = boundingRect(ptz);
        int maxdim = max(bbox.width, bbox.height);
        Mat1b work(2 * maxdim, 2 * maxdim, uchar(0));
        src(bbox).copyTo(work(Rect(maxdim - bbox.width / 2, maxdim - bbox.height / 2, bbox.width, bbox.height)));

        // Store best data
        Rect bestRect;
        int bestAngle = 0;

        // For each angle
        for (int angle = 0; angle < 90; angle++) {

            // Rotate the image
            Mat R = getRotationMatrix2D(Point(maxdim, maxdim), angle, 1);
            Mat1b rotated;
            warpAffine(work, rotated, R, work.size());

            // Keep the crop with the polygon
            std::vector<Point> pts;
            findNonZero(rotated, pts);
            Rect box = boundingRect(pts);
            Mat1b crop = rotated(box).clone();

            // Invert colors
            crop = ~crop;

            // Solve the problem: "Find largest rectangle containing only zeros in an binary matrix"
            // https://stackoverflow.com/questions/2478447/find-largest-rectangle-containing-only-zeros-in-an-n%C3%97n-binary-matrix
            Rect r = findMaxRect(crop);
            // If best, save result
            if (r.area() > bestRect.area()) {
                bestRect = r + box.tl();    // Correct the crop displacement
                bestAngle = angle;
            }
        }

        // Apply the inverse rotation
        Mat Rinv = getRotationMatrix2D(Point(maxdim, maxdim), -bestAngle, 1);
        std::vector<Point> rectPoints{bestRect.tl(), Point(bestRect.x + bestRect.width, bestRect.y), bestRect.br(),
                                 Point(bestRect.x, bestRect.y + bestRect.height)};
        std::vector<Point> rotatedRectPoints;
        transform(rectPoints, rotatedRectPoints, Rinv);

        // Apply the reverse translations
        for (int i = 0; i < rotatedRectPoints.size(); ++i) {
            rotatedRectPoints[i] += bbox.tl() - Point(maxdim - bbox.width / 2, maxdim - bbox.height / 2);
        }

        // Get the rotated rect
        RotatedRect rrect = minAreaRect(rotatedRectPoints);

        rrect.center = cv::Point(rrect.center.x * resizingFactor, rrect.center.y * resizingFactor);

        rrect.size = Size(rrect.size.width * resizingFactor, rrect.size.height * resizingFactor);

        return rrect;
    }
}


WorkPiece WorkPieceExtractor::workpiece(const cv::Mat &mat) {

    std::vector<std::vector<cv::Point>> contours = ContourDetector().contours(mat, false);
    std::vector<cv::Point> biggestContour = BiggestContourFinder().biggestContour(contours);
    cv::RotatedRect r1 = cv::minAreaRect(biggestContour);
    Point2f p[4];
    r1.points(p);
    cv::Mat m = Mat::ones(500,500, CV_8UC1);

    clock_t begin = clock();


    cv::RotatedRect r2 = largestRectInNonConvexPoly(mat);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<< "Time elapsed largestRectInNonConvexPoly function: "<<elapsed_secs << " sec"<<std::endl;

//    Rect r =r1.boundingRect();
//    cv::Rect r = cv::boundingRect(biggestContour);
//    if(r.area()<r1.size.area())
//    return WorkPiece(Point(r.tl().x, r.br().y), 0.0, r.width, r.height);
    return WorkPiece(r2);
}

