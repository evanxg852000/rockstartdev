cmake_minimum_required(VERSION 3.9)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# pull in the generated conan cmake
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories("${PROJECT_SOURCE_DIR}/vendor")

file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(app ${SOURCE_FILES})
target_link_libraries(app ${CONAN_LIBS})

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resources/" "${PROJECT_SOURCE_DIR}/build"
)
