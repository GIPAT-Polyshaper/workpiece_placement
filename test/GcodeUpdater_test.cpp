

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "../include/catch.hpp"
#include "../wplib/GcodeUpdater.h"
#include "test_config.h"
#include <sstream>

TEST_CASE("Updating a gcode file") {

  auto output = std::ostringstream();


  SECTION("hasNextPoint() returns false if stream is empty") {
    auto input = std::istringstream("");

    auto gcodeUpdater = GcodeUpdater(input, output);

    REQUIRE(gcodeUpdater.hasNextPoint() == false);
  }

  SECTION("if input stream is empty, output stream must be empty, too") {
    auto input = std::istringstream("");

    auto gcodeUpdater = GcodeUpdater(input, output);

    REQUIRE(output.str() == "");
  }

  SECTION("if the input does not contain any G00 or G01 command, copy to output as-is") {
    auto input = std::istringstream("M3\nDummy stuff for sure");

    auto gcodeUpdater = GcodeUpdater(input, output);

    REQUIRE(gcodeUpdater.hasNextPoint() == false);
    REQUIRE(output.str() == input.str() + "\n");
  }

  SECTION("if the input contains any F, copy to output as-is") {
    auto input = std::istringstream("G01 F300\nDummy stuff for sure");

    auto gcodeUpdater = GcodeUpdater(input, output);

    REQUIRE(gcodeUpdater.hasNextPoint() == false);
    REQUIRE(output.str() == input.str() + "\n");
  }

  SECTION("hasNextPoint returns true if stream contains G00s") {
    auto input = std::istringstream("G00 X10.2 Y12.3 Z-98.3 E123.4");

    auto gcodeUpdater = GcodeUpdater(input, output);

    REQUIRE(gcodeUpdater.hasNextPoint() == true);
  }

  SECTION("extract point coordinates from G00 commands") {
    auto input = std::istringstream("G00 X10.2 Y12.3 Z-98.3 E123.4");

    auto gcodeUpdater = GcodeUpdater(input, output);

    REQUIRE(gcodeUpdater.hasNextPoint() == true);
    auto nextPoint = GcodeUpdater::Point{10.2, 12.3, -98.3, 123.4};
    REQUIRE(gcodeUpdater.nextPoint() == nextPoint);
  }

  SECTION("extract point coordinates from G01 commands") {
    auto input = std::istringstream("G01 X10.2 Y12.3 Z-98.3 E123.4");

    auto gcodeUpdater = GcodeUpdater(input, output);

    REQUIRE(gcodeUpdater.hasNextPoint() == true);
    auto nextPoint = GcodeUpdater::Point{10.2, 12.3, -98.3, 123.4};
    REQUIRE(gcodeUpdater.nextPoint() == nextPoint);
  }

  SECTION("fill missing point coordinates with 0 for the first point") {
    auto input = std::istringstream("G01 X10.2 Z-98.3");

    auto gcodeUpdater = GcodeUpdater(input, output);

    REQUIRE(gcodeUpdater.hasNextPoint() == true);
    auto nextPoint = GcodeUpdater::Point{10.2, 0.0, -98.3, 0.0};
    REQUIRE(gcodeUpdater.nextPoint() == nextPoint);
  }

  SECTION("fill missing point coordinates with previous point ones for points past the first one") {
    auto input = std::istringstream("G01 X1 Y2 Z3 E4\nG01 Y44 Z55\nG00 X-1 Z-2");

    auto gcodeUpdater = GcodeUpdater(input, output);

    auto nextPoint = GcodeUpdater::Point{1, 2, 3, 4};
    REQUIRE(gcodeUpdater.hasNextPoint() == true);
    REQUIRE(gcodeUpdater.nextPoint() == nextPoint);
    nextPoint = GcodeUpdater::Point{1, 44, 55, 4};
    REQUIRE(gcodeUpdater.hasNextPoint() == true);
    REQUIRE(gcodeUpdater.nextPoint() == nextPoint);
    nextPoint = GcodeUpdater::Point{-1, 44, -2, 4};
    REQUIRE(gcodeUpdater.hasNextPoint() == true);
    REQUIRE(gcodeUpdater.nextPoint() == nextPoint);
    REQUIRE(gcodeUpdater.hasNextPoint() == false);
  }

  SECTION("copy everything to output when no point is modified (points always get all coordinates)") {
    auto input = std::istringstream("Dummy\nG00 X10\nMore dummyStuffs\nG01 Z10 Y67\nfinal dummy stuff");

    auto gcodeUpdater = GcodeUpdater(input, output);

    while (gcodeUpdater.hasNextPoint()) {
      gcodeUpdater.nextPoint();
    }

    REQUIRE(output.str() == "Dummy\nG00 X10 Y0 Z0 E0\nMore dummyStuffs\nG01 X10 Y67 Z10 E0\nfinal dummy stuff\n");
  }

  SECTION("allow spaces before G00 or G01") {
    auto input = std::istringstream("   G00 X10.2 Y12.3 Z-98.3 E123.4\n       G01 X10.2 Y12.3 Z-98.3 E123.4");

    auto gcodeUpdater = GcodeUpdater(input, output);

    auto nextPoint = GcodeUpdater::Point{10.2, 12.3, -98.3, 123.4};
    REQUIRE(gcodeUpdater.hasNextPoint() == true);
    REQUIRE(gcodeUpdater.nextPoint() == nextPoint);
    REQUIRE(gcodeUpdater.hasNextPoint() == true);
    REQUIRE(gcodeUpdater.nextPoint() == nextPoint);
    REQUIRE(gcodeUpdater.hasNextPoint() == false);
  }

  SECTION("store updated points") {
    auto input = std::istringstream("Dummy\nG00 X10\nMore dummyStuffs\nG01 Z10 Y67\nfinal dummy stuff");

    auto gcodeUpdater = GcodeUpdater(input, output);

    while (gcodeUpdater.hasNextPoint()) {
      GcodeUpdater::Point p = gcodeUpdater.nextPoint();

      p[0] += 1;
      p[1] += 1;
      p[2] += 1;
      p[3] += 1;

      gcodeUpdater.updatePoint(p);
    }

    REQUIRE(output.str() == "Dummy\nG00 X11 Y1 Z1 E1\nMore dummyStuffs\nG01 X11 Y68 Z11 E1\nfinal dummy stuff\n");

  }
}
