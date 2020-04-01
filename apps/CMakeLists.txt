#list(APPEND ccid_sources ccid.cpp )
#set(ccid_sources "${ccid_sources}" PARENT_SCOPE)
#add_executable(ccid ${ccid_sources})

add_executable(ccid ccid.cpp)

target_compile_features(ccid PUBLIC cxx_std_11)
target_link_libraries(ccid PRIVATE harmest snditf pthread curses)