//
// Created by riccardo on 27/07/17.
//

#ifndef WORKPIECE_PLACEMENT_IMAGELOADER_H
#define WORKPIECE_PLACEMENT_IMAGELOADER_H


#include "Image.h"

class ImageLoader {

private:
    /**
     * @brief directory separator
     */
    const std::string kPathSeparator =
#ifdef _WIN32
            "\\";
#else
            "/";
#endif

    /**
     * @brief images directory relative path
     */
    const std::string img_path = ".." + kPathSeparator + ".." + kPathSeparator + "sample_imgs" + kPathSeparator;

public:

    /**
     * @brief constructor
     * @param filename name of the image file to be loaded
     * @throw invalid_argument exception when image is not found
     */
    ImageLoader(const std::string & filename);

public:

    /**
     * @brief Get method Image member
     * @return Image member
     */
    const Image &getM_image() const;

private:

    Image m_image;

};


#endif //WORKPIECE_PLACEMENT_IMAGELOADER_H
