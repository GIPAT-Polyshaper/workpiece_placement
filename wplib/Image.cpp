//
// Created by riccardo on 10/07/17.
//

#include "Image.h"


Image::Image(std::string img_name) {

    this->name = img_name;

    this->imgMat = imread(this->img_path + img_name );
//    if ( imgMat.data )
//    {
//        //TODO: add exception when no file found
//        printf("No image data \n");
//    }
}

Image::Image(std::string img_name, Mat mat) {

    this->name = img_name;
    this->imgMat = mat;
}

const std::string Image::getPath() const {
    return this->img_path;
}

Mat Image::getMatImg() const {
    return this->imgMat;
}

const std::string Image::getName() const {
    return this->name;
}

void Image::showImg() {
    namedWindow(this->name, WINDOW_NORMAL);
    imshow(this->name, this->imgMat);
    waitKey(0);
}

bool Image::isEqualTo(Image *img) {

    Mat src_base, hsv_base;
    Mat src_test, hsv_test;
    src_base = this->imgMat;
    src_test = img->getMatImg();

    //Hue Saturation Value conversion
    cvtColor( src_base, hsv_base, COLOR_BGR2HSV );
    cvtColor( src_test, hsv_test, COLOR_BGR2HSV );

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

    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};

    calcHist( &hsv_base, 1, channels, Mat(),     // do not use mask
              hist_base, 2, histSize, ranges, true,     // the histogram is uniform
              false );
    normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_test, 1, channels, Mat(), hist_test, 2, histSize, ranges, true, false );
    normalize( hist_test, hist_test, 0, 1, NORM_MINMAX, -1, Mat() );
    double resultComparison = compareHist( hist_base, hist_test, CV_COMP_CORREL);

    return resultComparison < comparisonAccuracy ? false : true;
}

Image Image::clean() {

    // convert to grayscale
    cv::Mat gray;
    cv::cvtColor(this->imgMat,gray, CV_BGR2GRAY);

    // convert to binary inverted, findContours find only contours of white area but background is black
    cv::Mat mask;
    cv::threshold(gray, mask, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

    // find contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(mask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    // detect the biggest contour
    // ?????????????background should be bigger than other shapes on the image???????????????
    int largest_area=0;
    int largest_contour_index=0;
    Rect bounding_rect;
    Mat drawing = Mat::zeros(mask.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        //  Find the area of contour
        double a=contourArea( contours[i],false);
        if(a>largest_area){
            largest_area=a;
            // Store the index of largest contour
            largest_contour_index=i;
            // Find the bounding rectangle for biggest contour
            bounding_rect=boundingRect(contours[i]);
        }
    }
    // rectangle mask to crop original image
    rectangle(drawing, bounding_rect,  Scalar(255,0,0),2, 8,0);
    // crop image
    Mat croppedMat = this->imgMat(bounding_rect);

    return Image("croppedImage", croppedMat);
}
