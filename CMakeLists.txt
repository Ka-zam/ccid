# Init
cmake_minimum_required(VERSION 3.10...3.17)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/Modules)
#set(CMAKE_CXX_STANDARD 11)

# set the project name
project(ccid 
VERSION 0.1 
DESCRIPTION "A system identification tool aimed at Compact Cassette players"
LANGUAGES CXX C)

# Options
option(BUILD_SHARED_LIBS "Build shared or static libs." ON)


# find required packages
find_package(ALSA REQUIRED)
if (ALSA_FOUND)
	message("   Found ALSA sound library")
	message("    ${ALSA_INCLUDE_DIRS}")
endif()

find_package(FFTW REQUIRED FLOAT_LIB)
if (FFTW_FOUND)
	message("   Found FFTW3 single precision library")
	message("    ${FFTW_INCLUDE_DIRS}")
endif()

find_package(Curses REQUIRED)
if (CURSES_FOUND)
	message("   Found curses")
endif()

find_package(Threads)
if (THREADS_FOUND)
	message("   Found threads")
	set(THREADS_PREFER_PTHREAD_FLAG TRUE)
endif()

find_package(VOLK REQUIRED)
if (VOLK_FOUND)
	message("   Found VOLK ${VOLK_VERSION}")
	message("   ${VOLK_LIBRARIES}")
	message("   ${VOLK_INCLUDE_DIRS}")
endif()


# add directory
add_subdirectory(src)
add_subdirectory(apps)


# Status
message("Installing to ${CMAKE_INSTALL_PREFIX}")
message("Building shared is ${BUILD_SHARED_LIBS}")
message("$ENV{HOME}")