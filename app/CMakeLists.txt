add_executable(wp_main main.cpp)
#link wplib to wp_main
target_link_libraries(wp_main wplib )

add_executable(wp_calib calib.cpp)
#link wplib to wp_main
target_link_libraries(wp_calib wplib )