//
// Created by riccardo on 30/09/17.
//

#include "WorkingAreaSaver.h"

void WorkingAreaSaver::elaborate(const cv::Rect &rect) const {

    cv::FileStorage fs(this->workingAreaFile, cv::FileStorage::WRITE);

    if( !fs.isOpened() )
        throw std::runtime_error("Could not open file");
    fs << "x" << rect.x << "y" << rect.y;
    fs << "width" << rect.width << "height" << rect.height;
    fs.release();

}
