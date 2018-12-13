cmake_minimum_required(VERSION 3.12)
project(monte_carlo)

cmake_policy(VERSION 3.3)

set(CMAKE_CXX_STANDARD 14)

################################################################
# Build a library
################################################################
add_library(monaco Distribution/Uniform.cpp Distribution/Normal.cpp Distribution/Exponential.cpp Distribution/Geometric.cpp
        Moments/Moments.cpp Expectation/Expectation.cpp VerifyCLT/VerifyCLT.cpp)

################################################################
# Get Boost
################################################################
find_package(Boost COMPONENTS system filesystem iostreams REQUIRED)

add_executable(monte_carlo main.cpp
        Distribution/Uniform.cpp Distribution/Normal.cpp
        Distribution/Exponential.cpp Distribution/Geometric.cpp
        Moments/Moments.cpp Expectation/Expectation.cpp
        VerifyCLT/VerifyCLT.cpp)

target_link_libraries(monte_carlo PUBLIC ${Boost_LIBRARIES})

################################################################
# Google test
################################################################

include(GoogleTest)
enable_testing()
find_package(GTest)
if (GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(test_my_distribution tests/my_distribution_test.cpp)
    add_executable(test_my_expectation tests/my_expectation_test.cpp)
    add_executable(test_my_moments tests/my_moments_test.cpp)
    add_executable(test_my_CLT tests/my_CLT_test.cpp)
#    add_executable(fixture_test fixture_test.cc)
    target_link_libraries(test_my_distribution ${GTEST_BOTH_LIBRARIES} pthread monaco)
    target_link_libraries(test_my_expectation ${GTEST_BOTH_LIBRARIES} ${Boost_LIBRARIES} pthread monaco)
    target_link_libraries(test_my_moments ${GTEST_BOTH_LIBRARIES} ${Boost_LIBRARIES} pthread monaco)
    target_link_libraries(test_my_CLT ${GTEST_BOTH_LIBRARIES} ${Boost_LIBRARIES} pthread monaco)
#    target_link_libraries(fixture_test ${GTEST_BOTH_LIBRARIES} pthread particles)
    gtest_discover_tests(test_my_distribution)
    gtest_discover_tests(test_my_expectation)
    gtest_discover_tests(test_my_moments)
    gtest_discover_tests(test_my_CLT)
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
