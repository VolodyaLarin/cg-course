project(ogl_drawer)

set(PROJECT_SOURCE_DIR "./src")
set(PROJECT_INCLUDE_DIR "./inc")

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${PROJECT_INCLUDE_DIR}/*.h)


set(CMAKE_PREFIX_PATH "/home/volodya/Qt/6.0.2/gcc_64/lib/cmake")


find_package(Qt6 COMPONENTS
        Widgets
        OpenGLWidgets
        REQUIRED)

add_library(ogl_drawer ${HEADERS} ${SOURCES})
target_include_directories(ogl_drawer PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(ogl_drawer
        Qt::OpenGLWidgets
        Qt::Widgets
        cg_lib
        math_glm)