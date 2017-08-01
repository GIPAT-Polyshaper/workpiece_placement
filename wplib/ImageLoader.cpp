//
// Created by riccardo on 27/07/17.
//



#include "ImageLoader.h"

namespace {

    /**
     * @brief read an image file in grayscale
     * @param filename name of the file
     * @throw invalid_argument exception when image is not found
     * @return cv::Mat matrix
     */
    cv::Mat readImageGS(const std::string & filename){
        cv::Mat m = cv::imread(filename, IMREAD_GRAYSCALE);
        if(!m.data)
            throw std::invalid_argument("No files found");
        return m;
    }
}

ImageLoader::ImageLoader(const std::string &filename) : m_image(filename, readImageGS(filename)) {}

const Image &ImageLoader::getM_image() const {
    return m_image;
}
