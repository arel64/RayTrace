include(FetchContent)
set(GTEST_VERSION "release-1.12.1")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        ${GTEST_VERSION}
)
FetchContent_MakeAvailable(googletest)
set(DGTEST_CREATE_SHARED_LIBRARY 1)
set(BUILD_SHARED_LIBS 1)


set(This TestRayTrace)
set(Sources
    TestDev.cpp
    Utils/TestColor.cpp
)


add_executable(${This} ${Sources})
target_link_libraries(${This}
    PUBLIC
       GTest::gtest_main
       GTest::gtest
       RAYTRACE
)

add_test(
    NAME ${This}
    COMMAND ${This}
)