cmake_minimum_required(VERSION 3.22)
project(mono_vio)

include_directories(${CMAKE_CURRENT_LIST_DIR})

include(cmake/ProjectSetting.cmake)
include(cmake/OptionSetting.cmake)
include(cmake/DependenciesHandle.cmake)
include(cmake/TargetFileGrabber.cmake)
include(cmake/TargetGeneration.cmake)