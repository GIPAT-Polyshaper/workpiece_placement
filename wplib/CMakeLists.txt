set(SOURCE_FILES Image.h Image.cpp WorkPiece.cpp WorkPiece.h ImageLoader.cpp ImageLoader.h
        WorkingAreaExtractor.cpp WorkingAreaExtractor.h
        ImageCutter.cpp ImageCutter.h
        WorkPieceExtractor.cpp WorkPieceExtractor.h CameraCapture.cpp CameraCapture.h
        PerspectiveCorrector.cpp PerspectiveCorrector.h CameraCalibrator.cpp CameraCalibrator.h
        PixelsToMetric.cpp PixelsToMetric.h GcodeUpdater.cpp GcodeUpdater.h GcodePointUpdater.cpp
        GcodePointUpdater.h ImageCorrector.cpp ImageCorrector.h wp.h WorkingAreaSaver.cpp WorkingAreaSaver.h WorkingAreaLoader.cpp WorkingAreaLoader.h)


add_library(wplib STATIC ${SOURCE_FILES})
#link opencv lib to wplib
target_link_libraries( wplib ${OpenCV_LIBS} )