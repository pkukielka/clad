cmake_minimum_required (VERSION 2.6)

#================================================
# Project
#================================================
project (clad_test)

#================================================
# Test executable
#================================================
add_executable (${PROJECT_NAME} main.cpp )

target_link_libraries (${PROJECT_NAME} gtest gtest_main LLVMSupport pthread dl)
