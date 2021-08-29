cmake_minimum_required(VERSION 3.20)
project(project)



set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(math_glm)
add_subdirectory(ogl_drawer)


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


add_executable(project main.cpp)
target_link_libraries(project
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::OpenGLWidgets
        cg_lib
        math_glm
        ogl_drawer
        )

