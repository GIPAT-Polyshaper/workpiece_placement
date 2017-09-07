//
// Created by riccardo on 27/07/17.
//

#include "WorkingAreaExtractor.h"
namespace {


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


    RotatedRect largestRectInNonConvexPoly(const Mat1b &src2) {

        float resizingFactor = (float)src2.cols/(float)300;
        cv::Mat1b src;
        resize(src2, src, Size(), 1/resizingFactor, 1/resizingFactor, INTER_LINEAR);
        threshold(src, src, 0, 255,  CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

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
//
//        // For each angle
//        for (int angle = 0; angle < 90; angle++) {

            int angle = 0;
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
//        }

        // Apply the inverse rotation
        Mat Rinv = getRotationMatrix2D(Point(maxdim, maxdim), -bestAngle, 1);
        std::vector<Point> rectPoints{bestRect.tl(), Point(bestRect.x + bestRect.width, bestRect.y), bestRect.br(),
                                      Point(bestRect.x, bestRect.y + bestRect.height)};
        std::vector<Point> rotatedRectPoints;
        transform(rectPoints, rotatedRectPoints, Rinv);

        // Apply the reverse translations
        for (int i = 0; i < rotatedRectPoints.size(); ++i)
        {
            rotatedRectPoints[i] += bbox.tl() - Point(maxdim - bbox.width / 2, maxdim - bbox.height / 2);
        }

        // Get the rotated rect
        RotatedRect rrect = minAreaRect(rotatedRectPoints);

        rrect.center = cv::Point(rrect.center.x * resizingFactor, rrect.center.y * resizingFactor);

        rrect.size = Size(rrect.size.width * resizingFactor, rrect.size.height * resizingFactor);

        return rrect;
    }
}

RotatedRect WorkingAreaExtractor::elaborate(const Image& img)
{

//    return findBoundingRect(BiggestContourFinder().elaborate(ContourDetector().contours(img.getMat(), true)));

    std::vector<cv::Point> biggestContour = BiggestContourFinder().elaborate(ContourDetector().contours(img.getMat(), true));
    cv::RotatedRect r1 = cv::minAreaRect(biggestContour);

    Point2f p[4];
    r1.points(p);
    cv::Mat m = Mat::ones(500,500, CV_8UC1);
    cv::RotatedRect r2 = largestRectInNonConvexPoly(img.getMat());
    return r2;

}


cv::Rect WorkingAreaExtractor::findBoundingRect(const std::vector<cv::Point>& cont){

    //find bounding rectangle of Contour
    Rect bounding_rect = boundingRect(cont);
    return  bounding_rect;
    // contour search decrease width of 1 px when image has a frame
//        return  Rect(cont[0],cv::Point(cont[2].x+1, cont[2].y+1));

}


