cmake_minimum_required(VERSION 3.0)
project(project)



set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(math_glm)
#add_subdirectory(ogl_drawer)
add_subdirectory(qp_drawer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/volodya/Qt/6.0.2/gcc_64/lib/cmake")



find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        OpenGLWidgets
        REQUIRED)


add_executable(project
        mainwindow.ui
        main.cpp
        mainwindow.cpp
        mainwindow.h
        MyAnimatedCoordParams.cpp MyAnimatedCoordParams.h MyAnimatedCoordParams.ui)
target_link_libraries(project
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::OpenGLWidgets
        cg_lib
        math_glm
        qp_drawer
        )

