//
// Created by riccardo on 27/07/17.
//


#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "test_config.h"


TEST_CASE("Loading image from file"){

    SECTION("loading image"){

        std::string filename = img_path+"IMG_2215.JPG";
        Image img = ImageLoader(filename).getImage();
        REQUIRE(img.getMat().cols == 3264);
        REQUIRE(img.getMat().rows == 2448);

    }

    SECTION("loading image from not existing file throw invalid argument exception"){

        std::string filename = "IMG_2";
        REQUIRE_THROWS_AS(ImageLoader(filename).getImage(), std::invalid_argument);

    }

}
