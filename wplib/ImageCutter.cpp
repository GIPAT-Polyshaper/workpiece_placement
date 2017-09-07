//
// Created by riccardo on 27/07/17.
//

#include "ImageCutter.h"

std::string ImageCutter::nameComposer(const std::string &filename)
{
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename+"Cut";
    return filename.substr(0, lastdot)+"Cut"+filename.substr(lastdot);
}

Image ImageCutter::imageCut(const Image & img, const cv::Rect& rect)
{

    Mat croppedMat = img.getMat()(rect);
    Image i = Image(nameComposer(img.getM_name()), croppedMat);
    return i;

}

Image ImageCutter::imageCut(const Mat &mat, std::vector<std::vector<cv::Point>> area) {

    //find bounding rectangle of Contour
    Rect bounding_rect = boundingRect(area);
    // rectangle mask to crop original image
    Mat drawing = Mat::zeros(mat.size(), CV_8UC3 ); //new zeros matrix same size image
    rectangle(drawing, bounding_rect,  Scalar(255,0,0),2, 8,0);
    // crop image
    return imageCut(mat, bounding_rect);
}


const Image ImageCutter::elaborate(const Image &img, const cv::Rect& r)
{
    return imageCut(img, r);
}
