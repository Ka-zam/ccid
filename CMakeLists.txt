# Init
cmake_minimum_required(VERSION 3.10...3.16)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/Modules)
#set(CMAKE_CXX_STANDARD 11)

# set the project name
project(ccid 
VERSION 0.1 
DESCRIPTION "A system identification tool aimed at Compact Cassette players"
LANGUAGES CXX)

# find required packages
find_package(FFTW REQUIRED FLOAT_LIB)

if (FFTW_FOUND)
	message("   Found FFTW3 single precision library")
endif()

# add directory
add_subdirectory(src)
add_subdirectory(apps)
