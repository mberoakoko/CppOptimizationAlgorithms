cmake_minimum_required(VERSION 3.22.1)
project(CppOptimizationAlgorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
find_package(xtl QUIET) # Use QUIET to suppress messages if not found

if(xtl_FOUND)
    message(STATUS "Found xtl (system installed). Version: ${xtl_VERSION}")
else()
    message(STATUS "xtl not found on system. Fetching from GitHub...")
    FetchContent_Declare(
            xtl
            GIT_REPOSITORY https://github.com/xtensor-stack/xtl.git
            GIT_TAG        0.7.2 # Recommend a specific tag for stability
    )
    FetchContent_MakeAvailable(xtl)
endif()

find_package(xtensor QUIET) # Use QUIET to suppress messages if not found

if(xtensor_FOUND)
    message(STATUS "Found xtensor (system installed). Version: ${xtensor_VERSION}")
else()
    message(STATUS "xtensor not found on system. Fetching from GitHub...")
    FetchContent_Declare(
            xtensor
            GIT_REPOSITORY https://github.com/xtensor-stack/xtensor.git
            GIT_TAG        0.23.10 # Recommend a specific tag for stability
    )
    FetchContent_MakeAvailable(xtensor)
endif()

add_executable(CppOptimizationAlgorithms main.cpp
        include/base/bracketing.hpp
        include/base/base_elements.hpp)

target_link_libraries(CppOptimizationAlgorithms PUBLIC xtensor xtl)