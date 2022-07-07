cmake_minimum_required(VERSION 3.13)  # CMake version check
project(RAYTRACE)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard
include(FetchContent)

set(SFML_VERSION "2.5.1")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})


FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG        "${SFML_VERSION}"
)

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

set(SOURCE_FILES 
    main.cpp
    src/Window.cpp
    src/Camera.cpp
    src/Ray.cpp
    src/Render.cpp
    src/Scene.cpp
)
add_executable(RAYTRACE ${SOURCE_FILES})
target_link_libraries(RAYTRACE
    PRIVATE
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window
)
