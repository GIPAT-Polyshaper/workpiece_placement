//
// Created by riccardo on 10/07/17.
//

#include "Image.h"

namespace {

    template <typename Type>
    /**
     * @brief crop image
     * @param img image to be cropped
     * @param area cropping area
     * @return cropped image
     */
    Image imageCutter(const Mat &mat, Type area) {

        //find bounding rectangle of Contour
        Rect bounding_rect = boundingRect(area);
        // rectangle mask to crop original image
        Mat drawing = Mat::zeros(mat.size(), CV_8UC3 ); //new zeros matrix same size image
        rectangle(drawing, bounding_rect,  Scalar(255,0,0),2, 8,0);
        // crop image
        return imageCutter(mat,bounding_rect);
    }

    template <> Image imageCutter(const Mat &mat, cv::Rect area){

        Mat croppedMat = mat(area);
        Image i = Image(croppedMat);
        return i;

    }
}

Image::Image(std::string img_name, Mat mat) :
        m_name(img_name)
{
    if(mat.channels()!=1)
    {
        cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
    }
    this->m_mat = mat;
}

Image::Image(cv::Mat mat) {

    if(mat.channels()!=1)
    {
        cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
    }
    this->m_mat = mat;
}

const std::string &Image::getM_name() const {
    return m_name;
}

const Mat &Image::getM_mat() const {
    return m_mat;
}

void Image::showImg() {
    namedWindow(this->m_name, WINDOW_NORMAL);
    imshow(this->m_name, this->m_mat);
    waitKey(0);
}

bool Image::isEqualTo(const Image& img) {

    Mat src_base, hsv_base;
    Mat src_test, hsv_test;
    src_base = this->m_mat;
    src_test = img.getM_mat();
    //Histogram dimensionality
    int dims;

    //channels should be the same otherwise the images are not equals
    if(src_base.channels()!= src_test.channels())
    {
        return false;
    }
    int * channels;
    int channels1[] = {0};
    int channels2[] = {0,1};
    //if not grayscale
    if(src_base.channels()!=1)
    {
        dims = 2;
        //Hue Saturation Value conversion
        cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
        cvtColor(src_test, hsv_test, COLOR_BGR2HSV);
        // we compute the histogram from the 0-th and 1-st channels
        channels = channels2;

    } else{
        dims = 1;
        hsv_base = src_base;
        hsv_test = src_test;
        channels = channels1;
    }

    // Quantize the hue to 30 levels
    // and the saturation to 32 levels
    int h_bins = 50, s_bins = 60;
    int histSize[] = {h_bins, s_bins};

    // hue varies from 0 to 179, see cvtColor
    float h_ranges[] = { 0, 180 };

    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float s_ranges[] = { 0, 256 };
    const float* ranges[] = { h_ranges, s_ranges };
    MatND hist_base;
    MatND hist_test;

    calcHist( &hsv_base, 1, channels, Mat(),     // do not use mask
              hist_base, dims, histSize, ranges, true,     // the histogram is uniform
              false );
    normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_test, 1, channels, Mat(), hist_test, dims, histSize, ranges, true, false );
    normalize( hist_test, hist_test, 0, 1, NORM_MINMAX, -1, Mat() );

    double resultComparison = compareHist( hist_base, hist_test, CV_COMP_CORREL);

    return resultComparison < comparisonAccuracy ? false : true;
}
