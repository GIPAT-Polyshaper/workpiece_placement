cmake_minimum_required(VERSION 3.7)
project(workpiece_placement)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES app/main.cpp wplib/Image.cpp wplib/Image.h )
add_executable(workpiece_placement ${SOURCE_FILES})
target_link_libraries( workpiece_placement ${OpenCV_LIBS} )

# -------------- test section --------------

enable_testing()

set(YOUR_CATCH_INCLUDE_DIR ./include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${YOUR_CATCH_INCLUDE_DIR})

set(MY_TEST_SOURCES wplib/Image.cpp wplib/Image.h test/Image_test.cpp)
add_executable(wpImage_test ${MY_TEST_SOURCES})
target_link_libraries(wpImage_test Catch ${OpenCV_LIBS})
add_test(NAME testImage COMMAND wpImage_test)