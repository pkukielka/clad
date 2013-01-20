cmake_minimum_required (VERSION 2.6)

add_executable (clad_test main.cpp fixit_test.cpp)

target_link_libraries (clad_test gtest gtest_main LLVMSupport pthread dl)
