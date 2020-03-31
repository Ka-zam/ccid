set(HEADER_LIST "${ccid_SOURCE_DIR}/include/ccid/harmest.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(harmest harmest.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(harmest PUBLIC ../include)

# This depends on (header only) boost
# target_link_libraries(modern_library PRIVATE Boost::boost)
target_link_libraries(harmest PRIVATE ${FFTW_LIBRARIES})


# All users of this library will need at least C++11
target_compile_features(harmest PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
