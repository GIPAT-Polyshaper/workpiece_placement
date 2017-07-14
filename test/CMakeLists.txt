enable_testing()

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

add_executable(wpImage_test Image_test.cpp)
target_link_libraries(wpImage_test wplib Catch)
add_test(NAME testImage COMMAND wpImage_test)