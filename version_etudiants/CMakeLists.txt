cmake_minimum_required(VERSION 2.8)

# give a name to the project
project(stabilisation)

# add a "output" directory in the project binary directory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output)

# put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# find opencv
message("look for lib opencv ..." )
find_package(OpenCV REQUIRED)
if(${OpenCV_FOUND})
message(STATUS "lib opencv found")
message(STATUS "  version     : " ${OpenCV_VERSION})
message(STATUS "  include dir : " ${OpenCV_INCLUDE_DIRS})
message(STATUS "  libraries   : ")
foreach(opencvLibs ${OpenCV_LIBS})
	message("        " ${opencvLibs})
endforeach()	
endif()

# check opencv version
if(${OpenCV_VERSION} VERSION_LESS 2.0.0)
message(FATAL_ERROR “OpenCV version is not compatible : ${OpenCV_VERSION}”)
endif()

# include eigen
message("look for lib eigen ..." )
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
endif()

# link libs
include_directories(${EIGEN3_INCLUDE_DIR})

# compilation flags
set(CMAKE_CXX_FLAGS "-Wall -g -O2")

# compile
add_executable(stabilisation src/imageStabilization.cpp)
target_link_libraries(stabilisation ${OpenCV_LIBS})


