project(math_glm)

set(PROJECT_SOURCE_DIR "./src")
set(PROJECT_INCLUDE_DIR "./inc")

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${PROJECT_INCLUDE_DIR}/*.h)


add_library(math_glm ${HEADERS} ${SOURCES})
target_include_directories(math_glm PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(math_glm cg_lib)