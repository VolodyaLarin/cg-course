cmake_minimum_required(VERSION 3.0)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(math_glm)
add_subdirectory(ogl_drawer)


add_executable(project
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_glut.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        main.cpp
)
target_include_directories(project PUBLIC imgui .)
target_link_libraries(project cg_lib math_glm  ogl_drawer GL glut)

