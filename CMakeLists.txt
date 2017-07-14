cmake_minimum_required(VERSION 3.7)
project(workpiece_placement)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIR} )

# Adding all subdirectories
add_subdirectory(wplib)
add_subdirectory(app)
add_subdirectory(test)