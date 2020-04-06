set(HARMEST_HEADER_LIST "${ccid_SOURCE_DIR}/include/ccid/harmest.hpp")
set(SNDITF_HEADER_LIST "${ccid_SOURCE_DIR}/include/ccid/snditf.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(harmest harmest.cpp ${HARMEST_HEADER_LIST})
add_library(snditf snditf.cpp ${SNDITF_HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(harmest PUBLIC ../include ${VOLK_INCLUDE_DIRS} ${FFTW_INCLUDE_DIRS})
target_include_directories(snditf PUBLIC ../include ${VOLK_INCLUDE_DIRS} ${ALSA_INCLUDE_DIRS})

# Library dependencies
target_link_libraries(harmest PRIVATE ${FFTW_LIBRARIES} ${VOLK_LIBRARIES})
target_link_libraries(snditf PRIVATE ${ALSA_LIBRARIES} ${VOLK_LIBRARIES})

# All users of this library will need at least C++11
target_compile_features(harmest PUBLIC cxx_std_14)
target_compile_features(snditf PUBLIC cxx_std_14)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HARMEST_HEADER_LIST})
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${SNDITF_HEADER_LIST})
