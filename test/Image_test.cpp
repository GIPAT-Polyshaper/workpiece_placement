//
// Created by riccardo on 10/07/17.
//

#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../wplib/Image.h"


TEST_CASE( "Image_isEqualTo_test", "[compare]" ) {

    Image *img1 = new Image("IMG_2215.JPG");
    Image *img2 = new Image("IMG_2215.JPG");
    // is an image  equal to itself?
    REQUIRE(img1->isEqualTo(img2));
    Image *img3 = new Image("IMG_2216.JPG");
    // are two different images  equal?
    REQUIRE_FALSE(img1->isEqualTo(img3));

}

TEST_CASE("Image_contour_test", "[contour]"){
    Image *img = new Image("disegno.png");
    std::vector<std::vector<Point>>cont = img->contours();
    REQUIRE(cont.size() == 1);
    REQUIRE(cont[0].size() == 4);
    REQUIRE(cont[0][0].x == 1);
    REQUIRE(cont[0][0].y == 1);
    REQUIRE(cont[0][1].x == 1);
    REQUIRE(cont[0][1].y == 399);
    REQUIRE(cont[0][2].x == 299);
    REQUIRE(cont[0][2].y == 399);
    REQUIRE(cont[0][3].x == 299);
    REQUIRE(cont[0][3].y == 1);
}

TEST_CASE("Image_biggestAreaContour_test", "[big_contour]"){
    vector<Point> contour1;
    contour1.push_back(Point(0, 0));
    contour1.push_back(Point(10, 0));
    contour1.push_back(Point(10, 10));
    contour1.push_back(Point(0, 10));
    //biggest contour
    vector<Point> contour2;
    contour2.push_back(Point(0, 0));
    contour2.push_back(Point(100, 0));
    contour2.push_back(Point(100, 100));
    vector<Point> contour3;
    contour3.push_back(Point(0, 0));
    contour3.push_back(Point(20, 0));
    contour3.push_back(Point(20, 20));
    contour3.push_back(Point(0, 20));
    std::vector<std::vector<cv::Point>> contours{ contour1, contour3, contour2};
    Image *img;
    std::vector<cv::Point> cont = img->biggestAreaContour(contours);
    Point p2 = cont[2];
    REQUIRE(p2.x == 100);
    REQUIRE(p2.y == 100);

}

TEST_CASE( "Image_clean_test", "[clean]" ) {

    Image *img16 = new Image("IMG_2216.JPG");
    Image cleanedImg16 = img16->clean();
    // manual cropped image
    Image *img16c = new Image("IMG_2216_cut.JPG");
    //  check if the image result of clean method is equal to a manual cropped image
    REQUIRE(cleanedImg16.isEqualTo(img16c));
    Image *img17 = new Image("IMG_2217.JPG");
    Image cleanedImg17 = img17->clean();
    Image *img17c = new Image("IMG_2217_cut.JPG");
    REQUIRE(cleanedImg17.isEqualTo(img17c));

}


