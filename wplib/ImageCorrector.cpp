//
// Created by riccardo on 23/09/17.
//

#include "ImageCorrector.h"


Image ImageCorrector::elaborate(const Image & img) const {

    Mat intrinsic, distCoeffs;
    auto params = this->readParams();
    intrinsic = params.front();
    distCoeffs = params.back();
    Mat undistortMat;
    undistort(img.getMat(), undistortMat, intrinsic, distCoeffs);
    return Image("img",undistortMat);
}

std::vector<cv::Mat> ImageCorrector::readParams()const {

    cv::FileStorage fs;
    fs.open(this->filename, FileStorage::READ);

    if(!fs.isOpened())
        throw std::runtime_error("Could not open correction file");
    Mat intrinsic, distCoeffs;
    fs["distortion_coefficients"] >> distCoeffs;
    fs["intrinsic_matrix"] >> intrinsic;
    if (distCoeffs.empty() || intrinsic.empty())
        throw std::runtime_error("Intrinsic matrix and/or distortion coefficients matrix empty. Re-run calibration");
    std::vector<cv::Mat> params;
    params.push_back(intrinsic);
    params.push_back(distCoeffs);
    return params;
}
