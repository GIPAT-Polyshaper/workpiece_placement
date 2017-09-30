//
// Created by riccardo on 30/09/17.
//

#include <iostream>
#include <opencv2/core/persistence.hpp>
#include "WorkingAreaSaver.h"

void WorkingAreaSaver::elaborate(const cv::Rect &rect) const {

    cv::FileStorage fs(this->workingAreaFile, cv::FileStorage::WRITE);

    if( !fs.isOpened() )
        //todo throw exception
        ;

    fs << "x" << rect.x << "y" << rect.y;
    fs << "width" << rect.width << "height" << rect.height;
    fs.release();

}
