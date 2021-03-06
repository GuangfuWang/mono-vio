if (${CMAKE_HOST_WIN32})
    add_compile_definitions("GF_WINDOWS")
elseif (${CMAKE_HOST_UNIX})
    add_compile_definitions("GF_LINUX")
elseif (${CMAKE_HOST_APPLE})
    add_compile_definitions("GF_APPLE")
else ()
    add_compile_definitions("GF_UNSUPPORTED_OS")
endif ()

if (${CMAKE_HOST_WIN32})
    # this is due to windows system will open a cmd window.
    set(PLAT_FLAG "WIN32")
else ()
    set(PLAT_FLAG "")
endif ()

add_executable(mono_vio ${PLAT_FLAG} Main.cpp ${SLAM_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Sophus::Sophus ${G2O_LIBS} yaml-cpp ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE  -lpthread -li2c)