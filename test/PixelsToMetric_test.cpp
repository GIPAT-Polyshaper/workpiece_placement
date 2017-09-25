//
// Created by riccardo on 23/08/17.
//

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "../include/catch.hpp"
#include "../wplib/PixelsToMetric.h"


//WARNING!!! the result of this test depends on mmKnownSize constant defined in PixelsToMetri class

TEST_CASE("Pixels to metric conversion"){
    PixelsToMetric ptm(1000);
    SECTION("Converting negative value throws invalid argument exception")
    {
         
         REQUIRE_THROWS_AS(ptm.elaborate(-3), std::invalid_argument);
    }
    
    float mm = ptm.elaborate(1200);
    Approx mmTarget = Approx(327).epsilon(0.01);
    REQUIRE(mm == mmTarget);

}

