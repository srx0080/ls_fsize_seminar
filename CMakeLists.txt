cmake_minimum_required(VERSION 2.8)
ADD_COMPILE_OPTIONS (-std=c++11)
INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/include)

# Project's name
PROJECT(ls_fsize_seminar)

# Set the output folder where your program will be created
SET (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
SET (SRC_FILES Seminar_modified.cpp ls_fsize.cpp)
SET (CMAKE_VERBOSE_MAKEFILE true)
SET (CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin_installed)
# The following folder will be included
ADD_EXECUTABLE(example01 ${SRC_FILES})
