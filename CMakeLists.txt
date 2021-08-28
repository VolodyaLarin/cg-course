cmake_minimum_required(VERSION 3.20)
project(project)



set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/volodya/Qt/6.0.2/gcc_64/lib/cmake")



find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)


add_executable(project main.cpp)
target_link_libraries(project
        Qt::Core
        Qt::Gui
        Qt::Widgets
        cg_lib
        )

