cmake_minimum_required(VERSION 3.6)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(HDF5 COMPONENTS C CXX HL REQUIRED)

include_directories( ${HDF5_INCLUDE_DIR})
link_directories( ${HDF5_LIBRARY_DIRS} )

set(SOURCE_FILES
    1_write.cpp)

add_executable(src ${SOURCE_FILES})
#target_link_libraries (src LINK_PUBLIC ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES} )
target_link_libraries (src LINK_PUBLIC ${HDF5_LIBRARIES} ${HDF5_CXX_LIBRARIES})
