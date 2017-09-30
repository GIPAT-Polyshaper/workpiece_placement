//
// Created by riccardo on 30/09/17.
//

#include <opencv2/core/persistence.hpp>
#include "WorkingAreaLoader.h"

cv::Rect WorkingAreaLoader::elaborate() const {

    cv::Rect rect;

    cv::FileStorage fs(this->workingAreaFile, cv::FileStorage::READ);
    if( fs.isOpened() )
        //todo throw exception
        ;
        fs["x"] >> rect.x;
        fs["y"] >> rect.y;
        fs["width"] >> rect.width;
        fs["height"] >> rect.height;

    return rect;
}
