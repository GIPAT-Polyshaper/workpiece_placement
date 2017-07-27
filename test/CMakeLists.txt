enable_testing()

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

function(addTest testName)
    set(testTargetName "test_${testName}")
    set(testFileName "${testName}_test.cpp")
    add_executable("${testTargetName}"  "${testFileName}")
    target_link_libraries("${testTargetName}" wplib Catch)
    add_test(NAME "${testTargetName}"  COMMAND "${testTargetName}" )
 endfunction()

#add tests
addTest(Image)
addTest(WorkPiece)
addTest(ImageLoader)
addTest(ContourDetector)
addTest(WorkingAreaExtractor)
addTest(ImageCutter)
