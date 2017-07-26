set(SOURCE_FILES Image.h Image.cpp WorkingArea.cpp WorkingArea.h WorkPiece.cpp WorkPiece.h)


add_library(wplib STATIC ${SOURCE_FILES})
#link opencv lib to wplib
target_link_libraries( wplib ${OpenCV_LIBS} )