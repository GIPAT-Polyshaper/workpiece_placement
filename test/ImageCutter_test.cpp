//
// Created by riccardo on 27/07/17.
//


#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "../wplib/ImageCutter.h"
#include "test_config.h"

TEST_CASE("Image cutting")
{
    Image img = ImageLoader(img_path+"prova2.png").getM_image();

    SECTION("rectangle cropping") {

        Image imgC = ImageCutter().elaborate(img, cv::Rect(100, 350, 250, 150));
        REQUIRE(imgC.getM_mat().rows == 150);
        REQUIRE(imgC.getM_mat().cols == 250);
    }

}