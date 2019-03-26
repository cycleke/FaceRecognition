cmake_minimum_required(VERSION 3.13)
project(FaceRecognition
        VERSION 0.0.1)

set(APP_NAME "FaceRecognition")

if (WIN32)
    add_definitions(-DWIM32)
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-O2")

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5UiTools REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(
        ${OpenCV_INCLUDE_DIRS},
        ${Qt5_INCLUDE_DIRS},
        ${CMAKE_CURRENT_LIST_DIR}/include
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build)
set(SOURCE_FILES
        src/main.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.cpp
        src/ui/ui_aboutFaceRecognition.h
        src/ui/ui_mainwindow.h
        src/core/Detector.h
        src/core/Detector.cpp
        src/core/FMTCNN.h
        src/core/FMTCNN.cpp)
add_executable(${APP_NAME} ${SOURCE_FILES})
target_link_libraries(${APP_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::UiTools
        ${OpenCV_LIBS})
