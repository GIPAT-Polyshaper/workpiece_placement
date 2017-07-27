//
// Created by riccardo on 27/07/17.
//

#include "ImageCutter.h"

namespace {

    /**
    * @brief crop image
    * @param mat image matrix to be cropped
    * @param rect cropping rectangle
    * @return cropped image
    */
    Image imageCut(const Mat &mat, const cv::Rect& rect){

        Mat croppedMat = mat(rect);
        Image i = Image(croppedMat);
        return i;

    }

    /**
     * @brief crop image
     * @param mat image matrix to be cropped
     * @param area cropping area
     * @return cropped image
     */
    Image imageCut(const Mat &mat, std::vector<std::vector<cv::Point>> area) {

        //find bounding rectangle of Contour
        Rect bounding_rect = boundingRect(area);
        // rectangle mask to crop original image
        Mat drawing = Mat::zeros(mat.size(), CV_8UC3 ); //new zeros matrix same size image
        rectangle(drawing, bounding_rect,  Scalar(255,0,0),2, 8,0);
        // crop image
        return imageCut(mat, bounding_rect);
    }

}

const Image &ImageCutter::getM_image() const {
    return m_image;
}

ImageCutter::ImageCutter(const Image& img, const cv::Rect& r):
    m_image(imageCut(img.getM_mat(), r))
{}
