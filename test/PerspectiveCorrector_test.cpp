//
// Created by riccardo on 16/08/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/Image.h"
#include "../wplib/ImageLoader.h"
#include "test_config.h"
#include "../wplib/PerspectiveCorrector.h"


TEST_CASE("Perspective correction")
{

    Image img = ImageLoader(img_path + "perspective.png").getM_image();
    PerspectiveCorrector pr;
    Image imgCorrected = pr.correctedImage(img);
    Image comparisonImage = ImageLoader(img_path + "imageCorrected.jpg").getM_image();
    REQUIRE(imgCorrected.isEqualTo(comparisonImage));

}
