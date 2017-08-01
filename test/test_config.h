//
// Created by riccardo on 01/08/17.
//

#ifndef WORKPIECE_PLACEMENT_TEST_CONFIG_H
#define WORKPIECE_PLACEMENT_TEST_CONFIG_H

#endif //WORKPIECE_PLACEMENT_TEST_CONFIG_H

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
