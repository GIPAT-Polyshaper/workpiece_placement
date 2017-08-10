set(SOURCE_FILES Image.h Image.cpp
        WorkPiece.cpp WorkPiece.h ImageLoader.cpp ImageLoader.h
        ContourDetector.cpp ContourDetector.h WorkingAreaExtractor.cpp WorkingAreaExtractor.h ImageCutter.cpp ImageCutter.h BiggestContourFinder.cpp BiggestContourFinder.h WorkPieceExtractor.cpp WorkPieceExtractor.h CameraCapture.cpp CameraCapture.h)


add_library(wplib STATIC ${SOURCE_FILES})
#link opencv lib to wplib
target_link_libraries( wplib ${OpenCV_LIBS} )