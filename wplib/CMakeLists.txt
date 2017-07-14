set(SOURCE_FILES Image.h Image.cpp )


add_library(wplib STATIC ${SOURCE_FILES})
#link opencv lib to wplib
target_link_libraries( wplib ${OpenCV_LIBS} )