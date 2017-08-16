enable_testing()

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

function(addTest testName)
    set(testTargetName "test_${testName}")
    set(testFileName "${testName}_test.cpp")
    add_executable("${testTargetName}" "${testFileName}" "${CMAKE_CURRENT_BINARY_DIR}/test_config.h")
    target_link_libraries("${testTargetName}" wplib Catch)
    add_test(NAME "${testTargetName}"  COMMAND "${testTargetName}")
endfunction()

file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/sample_imgs/" SAMPLE_IMGS_DIR)
configure_file("test_config.h.in" "test_config.h" @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

#add tests
addTest(Image)
addTest(WorkPiece)
addTest(ImageLoader)
addTest(ContourDetector)
addTest(WorkingAreaExtractor)
addTest(ImageCutter)
addTest(BiggestContourFinder)
addTest(WorkPieceExtractor)
addTest(PerspectiveCorrector)
