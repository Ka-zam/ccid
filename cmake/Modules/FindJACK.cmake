# Distributed under GPLv3
# Copyright (c) 2020, Magnus Lundmark

#[=======================================================================[.rst:
FindJACK
--------

Find the JACK library. First looks in $HOME/local for a user compiled version

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``jack::jack``
  The JACK library


Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``JACK_FOUND``
  True if the system has the JACK library.
``JACK_VERSION``
  The version of the JACK library which was found.
``JACK_INCLUDE_DIRS``
  Include directories needed to use JACK.
``JACK_LIBRARIES``
  Libraries needed to link to JACK.  

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``JACK_INCLUDE_DIR``
  The directory containing ``jack.h``.
``JACK_LIBRARY``
  The path to the JACK library.

#]=======================================================================]

include(FeatureSummary)
set_package_properties(jack PROPERTIES
   URL "http://www.jackaudio.org/"
   DESCRIPTION "JACK Audio Connection Kit")

find_package(PkgConfig)
pkg_check_modules(PC_JACK QUIET jack)

find_path(JACK_INCLUDE_DIR 
	NAMES jack/jack.h 
	HINTS 
		${PC_JACK_INCLUDE_DIRS}
		${PC_JACK_INCLUDEDIR}
  	PATHS 
  		${PC_JACK_INCLUDE_DIRS}		
)

find_library(JACK_LIBRARY 
	NAMES jack 
	HINTS 
		${PC_JACK_LIBRARY_DIRS}
		${PC_JACK_LIBDIR}
)

set(JACK_VERSION ${PC_JACK_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JACK
  FOUND_VAR JACK_FOUND
  REQUIRED_VARS
    JACK_LIBRARY
    JACK_INCLUDE_DIR
  VERSION_VAR JACK_VERSION
)

if(JACK_FOUND)
  set(JACK_LIBRARIES ${JACK_LIBRARY})
  set(JACK_INCLUDE_DIRS ${JACK_INCLUDE_DIR})
  set(JACK_DEFINITIONS ${PC_JACK_CFLAGS_OTHER})
endif()

if(JACK_FOUND AND NOT TARGET jack::jack)
  add_library(jack::jack UNKNOWN IMPORTED)
  set_target_properties(jack::jack PROPERTIES
    IMPORTED_LOCATION "${JACK_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_JACK_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${JACK_INCLUDE_DIR}"
  )
endif()

set(JACK_VERSION_STRING ${JACK_VERSION})