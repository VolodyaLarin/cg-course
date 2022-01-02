project(ogl_drawer)

set(PROJECT_SOURCE_DIR "./src")
set(PROJECT_INCLUDE_DIR "./inc")

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${PROJECT_INCLUDE_DIR}/*.h)


add_library(ogl_drawer ${HEADERS} ${SOURCES})
target_include_directories(ogl_drawer PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(ogl_drawer cg_lib math_glm GLEW glut)