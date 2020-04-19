#list(APPEND ccid_sources ccid.cpp )
#set(ccid_sources "${ccid_sources}" PARENT_SCOPE)
#add_executable(ccid ${ccid_sources})


add_executable(ccid ccid.cpp)
target_link_libraries(ccid PRIVATE harmest snditf pthread curses ${JACK_LIBRARIES})
target_compile_features(ccid PUBLIC cxx_std_14)

add_executable(jackcopy jackcopy.c)
target_include_directories(jackcopy PUBLIC ${VOLK_INCLUDE_DIRS} ${JACK_INCLUDE_DIRS})
target_link_libraries(jackcopy PRIVATE m ${JACK_LIBRARIES} ${VOLK_LIBRARIES})
target_compile_features(jackcopy PUBLIC c_std_11)

add_executable(latency latency.c)
target_link_libraries(latency PRIVATE m ${ALSA_LIBRARIES})
