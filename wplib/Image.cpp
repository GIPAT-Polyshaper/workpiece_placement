//
// Created by riccardo on 10/07/17.
//

#include "Image.h"


Image::Image(std::string img_name) {

    this->name = img_name;

    this->imgMat = imread(this->img_path + img_name, CV_LOAD_IMAGE_GRAYSCALE );
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


std::vector<std::vector<cv::Point>> Image::contours(){
    // convert to binary inverted, findContours find only contours of white area but background is black
    cv::Mat mask;
    cv::threshold(this->getMatImg(), mask, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

    // find contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    return contours;
}

std::vector<cv::Point> Image::biggestAreaContour(std::vector<std::vector<cv::Point>> contours){
    int largest_area=0;
    int largest_contour_index=0;
    for( int i = 0; i< contours.size(); i++ )
    {
        //  Find the area of contour
        double a=contourArea( contours[i],false);
        if(a>largest_area){
            largest_area=a;
            // Store the index of largest contour
            largest_contour_index=i;
        }
    }
    return contours[largest_contour_index];
}



Image Image::clean() {
    //find contours
    std::vector<std::vector<cv::Point>> contours = this->contours();
    // ?????????????background should be bigger than other shapes on the image???????????????
    // detect the biggest contour
    std::vector<cv::Point> biggestContour = this->biggestAreaContour(contours);
    //find bounding rectangle of contour
    Rect bounding_rect = boundingRect(biggestContour);
    // rectangle mask to crop original image
    Mat drawing = Mat::zeros(this->getMatImg().size(), CV_8UC3 ); //new zeros matrix same size image
    rectangle(drawing, bounding_rect,  Scalar(255,0,0),2, 8,0);
    // crop image
    Mat croppedMat = this->imgMat(bounding_rect);

    return Image("croppedImage", croppedMat);
}
