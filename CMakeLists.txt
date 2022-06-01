cmake_minimum_required(VERSION 3.22)
project(mono_vio)

set(CMAKE_CXX_STANDARD 17)

find_package(Sophus CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

include(cmake/TargetFileGrabber.cmake)
VIO_SLAM(SLAM_SRC)
add_executable(mono_vio main.cpp ${SLAM_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE Sophus::Sophus)