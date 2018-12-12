cmake_minimum_required(VERSION 3.12)
project(monte_carlo)

cmake_policy(VERSION 3.3)

set(CMAKE_CXX_STANDARD 14)

################################################################
# Build a library
################################################################
add_library(monaco Uniform.cpp Normal.cpp Exponential.cpp Geometric.cpp
        Moments.cpp Expectation.cpp VerifyCLT.cpp)

################################################################
# Get Boost
################################################################
find_package(Boost COMPONENTS system filesystem iostreams REQUIRED)

add_executable(monte_carlo main.cpp
        Uniform.cpp Normal.cpp
        Exponential.cpp Geometric.cpp
        Moments.cpp Expectation.cpp
        VerifyCLT.cpp)

target_link_libraries(monte_carlo PUBLIC ${Boost_LIBRARIES})

################################################################
# Google test
################################################################

include(GoogleTest)
enable_testing()
find_package(GTest)
if (GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(test_my_distribution my_distribution_test.cpp)
#    add_executable(fixture_test fixture_test.cc)
    target_link_libraries(test_my_distribution ${GTEST_BOTH_LIBRARIES} pthread monaco)
#    target_link_libraries(fixture_test ${GTEST_BOTH_LIBRARIES} pthread particles)
    gtest_discover_tests(test_my_distribution)
#    gtest_discover_tests(fixture_test)
endif()

################################################################
# Doxygen
################################################################
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
    doxygen_add_docs(doxygen ${PROJECT_SOURCE_DIR} COMMENT "Generate html pages")
endif(DOXYGEN_FOUND)
