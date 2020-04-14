# Distributed under GPLv3
# Copyright (c) 2020, Magnus Lundmark

#[=======================================================================[.rst:
FindVOLK
--------

Find the VOLK library. First looks in $HOME/local for a user compiled version

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``volk::volk``
  The VOLK library


Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``VOLK_FOUND``
  True if the system has the VOLK library.
``VOLK_VERSION``
  The version of the VOLK library which was found.
``VOLK_INCLUDE_DIRS``
  Include directories needed to use VOLK.
``VOLK_LIBRARIES``
  Libraries needed to link to VOLK.  

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``VOLK_INCLUDE_DIR``
  The directory containing ``volk.h``.
``VOLK_LIBRARY``
  The path to the VOLK library.

#]=======================================================================]

include(FeatureSummary)
set_package_properties(volk PROPERTIES
   URL "https://www.libvolk.org/"
   DESCRIPTION "VOLK is the Vector-Optimized Library of Kernels")

find_package(PkgConfig)
pkg_check_modules(PC_VOLK QUIET volk)

find_path(VOLK_INCLUDE_DIR
  NAMES volk/volk.h
  HINTS 
        $ENV{HOME}/local/include
        $ENV{VOLK_DIR}/include
        ${PC_VOLK_INCLUDEDIR} 
  PATHS ${PC_VOLK_INCLUDE_DIRS}
  PATH_SUFFIXES volk
)

find_library(VOLK_LIBRARY
  NAMES volk
  HINTS 
        $ENV{HOME}/local/lib
        $ENV{VOLK_DIR}/lib
        ${PC_VOLK_LIBDIR}  
  PATHS ${PC_VOLK_LIBRARY_DIRS}
)

set(VOLK_VERSION ${PC_VOLK_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(VOLK
  FOUND_VAR VOLK_FOUND
  REQUIRED_VARS
    VOLK_LIBRARY
    VOLK_INCLUDE_DIR
  VERSION_VAR VOLK_VERSION
)

if(VOLK_FOUND)
  set(VOLK_LIBRARIES ${VOLK_LIBRARY})
  set(VOLK_INCLUDE_DIRS ${VOLK_INCLUDE_DIR})
  set(VOLK_DEFINITIONS ${PC_VOLK_CFLAGS_OTHER})
endif()

if(VOLK_FOUND AND NOT TARGET volk::volk)
  add_library(volk::volk UNKNOWN IMPORTED)
  set_target_properties(volk::volk PROPERTIES
    IMPORTED_LOCATION "${VOLK_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_VOLK_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${VOLK_INCLUDE_DIR}"
  )
endif()

set(VOLK_VERSION_STRING ${VOLK_VERSION})