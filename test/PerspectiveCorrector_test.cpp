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

//TODO pensare un test valido

TEST_CASE("Perspective correction") {

    Image img = ImageLoader(img_path + "perspective.png").getM_image();
    img.showImg();
    PerspectiveCorrector pr;
    Image imgcorrected = pr.correctedImage(img);
    imgcorrected.showImg();

}
