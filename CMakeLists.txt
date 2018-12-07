cmake_minimum_required(VERSION 3.12)
project(monte_carlo)

cmake_policy(VERSION 3.3)

set(CMAKE_CXX_STANDARD 14)

add_executable(monte_carlo main.cpp Exception.hpp
        Distribution.hpp Distribution.cpp Uniform.cpp Uniform.hpp
        Normal.cpp Normal.hpp Exponential.cpp Exponential.hpp
        Geometric.cpp Geometric.hpp Exception.hpp Moments.cpp Moments.hpp
        VerifyCLT.cpp VerifyCLT.hpp Expectation.cpp Expectation.hpp)

################################################################
# Matplotlib-cpp
################################################################
find_package(PythonLibs 2.7)
target_include_directories(monte_carlo PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(monte_carlo ${PYTHON_LIBRARIES})

################################################################
# Doxygen
################################################################

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
    doxygen_add_docs(doxygen ${PROJECT_SOURCE_DIR} COMMENT "Generate html pages")
endif(DOXYGEN_FOUND)
