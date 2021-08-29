project(cg_lib)

set(PROJECT_SOURCE_DIR "./src")
set(PROJECT_INCLUDE_DIR "./inc")

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/*/*.cpp)
file(GLOB HEADERS ${PROJECT_INCLUDE_DIR}/*.h)


add_library(cg_lib ${HEADERS} ${SOURCES} inc/utils/Time.h)
target_include_directories(cg_lib PUBLIC ${PROJECT_INCLUDE_DIR})