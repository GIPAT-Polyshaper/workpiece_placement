//
// Created by riccardo on 27/07/17.
//


#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"

TEST_CASE("Loading image from file"){

    SECTION("loading image"){

        std::string filename = "IMG_2215.JPG";
        Image img = ImageLoader(filename).getM_image();
        REQUIRE(img.getM_mat().cols == 3264);
        REQUIRE(img.getM_mat().rows == 2448);

    }

    SECTION("loading image from not existing file throw invalid argument exception"){

        std::string filename = "IMG_2";
        REQUIRE_THROWS_AS(ImageLoader(filename).getM_image(), std::invalid_argument);

    }

}