cmake_minimum_required(VERSION 3.6)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(HDF5 REQUIRED COMPONENTS C CXX)

#include_directories( ${HDF5_INCLUDE_DIR} ${HDF5_INCLUDE_DIRS})
include_directories( ${HDF5_INCLUDE_DIR})

set(SOURCE_FILES
    main1.cpp)

add_executable(src ${SOURCE_FILES})
#target_link_libraries (src LINK_PUBLIC ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES} )
target_link_libraries (src LINK_PUBLIC ${HDF5_LIBRARIES})
