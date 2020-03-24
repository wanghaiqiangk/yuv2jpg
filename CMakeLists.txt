cmake_minimum_required(VERSION 2.8)

project(yuv2jpg)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include_directories("${CMAKE_SOURCE_DIR}/thirdparty/opencv-3.3.1/include")
link_directories("${CMAKE_SOURCE_DIR}/thirdparty/opencv-3.3.1/lib")

set(OPENCV_LIB  "-lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_imgcodecs")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${OPENCV_LIB})

target_compile_options(${PROJECT_NAME} PRIVATE -std=c++11)
