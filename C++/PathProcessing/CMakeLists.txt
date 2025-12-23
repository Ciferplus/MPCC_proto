# PathProcessing Library CMakeLists.txt

cmake_minimum_required(VERSION 3.7)

# Option to build as a standalone library
option(BUILD_PATH_PROCESSING_STANDALONE "Build PathProcessing as standalone library" OFF)

if(BUILD_PATH_PROCESSING_STANDALONE)
    project(PathProcessing)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_FLAGS "-O2")
    
    # Find Eigen3
    find_package(Eigen3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})
    
    # Try to find nlohmann/json, fall back to local path if not found
    find_package(nlohmann_json QUIET)
    if(NOT nlohmann_json_FOUND)
        message(STATUS "nlohmann/json not found via find_package, using local path")
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../External/Json/include")
            include_directories(../External/Json/include)
        else()
            message(WARNING "nlohmann/json not found. Please install it or set the correct path.")
        endif()
    endif()
endif()

# Library source files
set(PATH_PROCESSING_SOURCES
    cubic_spline.cpp
    arc_length_spline.cpp
    track.cpp
    normalization.cpp
)

# Library header files
set(PATH_PROCESSING_HEADERS
    path_processing.h
    path_processing_config.h
    cubic_spline.h
    arc_length_spline.h
    track.h
    normalization.h
)

if(BUILD_PATH_PROCESSING_STANDALONE)
    # Build as a static library when standalone
    add_library(path_processing STATIC ${PATH_PROCESSING_SOURCES})
    
    # Install targets
    install(TARGETS path_processing DESTINATION lib)
    install(FILES ${PATH_PROCESSING_HEADERS} DESTINATION include/PathProcessing)
endif()

# Export sources for parent CMake project
set(PATH_PROCESSING_SOURCES ${PATH_PROCESSING_SOURCES} PARENT_SCOPE)
set(PATH_PROCESSING_HEADERS ${PATH_PROCESSING_HEADERS} PARENT_SCOPE)
