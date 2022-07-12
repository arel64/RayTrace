cmake_minimum_required(VERSION 3.13) 
project(RAYTRACE)             
set(CMAKE_CXX_STANDARD 20)           
include(FetchContent)
enable_testing()

#######SFML########
set(SFML_VERSION "2.5.1")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)



if (WIN32)
    add_compile_definitions(WIN32)
endif (WIN32)
if (UNIX)
    add_compile_definitions(UNIX)
endif (UNIX)


#For intellisense
set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_PREFIX_PATH}/include)
include_directories("D:/Dev/Workspace/RayTrace/build/_deps/googletest-src/googletest/include")

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
#######GLM########
find_package(glm CONFIG REQUIRED)


set(SOURCE_FILES 
    #main.cpp
    src/Window.cpp
    src/Camera.cpp
    src/Ray.cpp
    src/Render/Render.cpp
    src/Scene.cpp
    src/Sphere.cpp
    src/Utils/RandomReal.cpp
    src/Utils/Color.cpp
    src/Materials/Diffuse.cpp
    src/Materials/Metal.cpp
    src/Materials/Dielectric.cpp
)
set(HEADERS 
    #main.cpp
    h/Window.hpp
    h/Camera.hpp
    h/Ray.hpp
    h/Scene.hpp
    h/Sphere.hpp
    h/Hittable.hpp
    h/Render/Render.hpp
    h/Render/PixelCluster.hpp
    h/Utils/RandomReal.hpp
    h/Utils/Color.hpp
    h/Utils/Pair.hpp
    h/Utils/SafeQueue.hpp
    h/Materials/Diffuse.hpp
    h/Materials/Metal.hpp
    h/Materials/Dielectric.hpp
    h/Materials/Material.hpp
)
add_library(RAYTRACE STATIC ${SOURCE_FILES} ${HEADERS})

target_link_libraries(RAYTRACE
    PUBLIC
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window
        glm::glm
)

add_subdirectory(test)
