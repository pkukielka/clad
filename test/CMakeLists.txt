cmake_minimum_required (VERSION 2.6)

add_executable (clad_test main.cpp diagnostics_test.cpp)

target_link_libraries (clad_test clad_serv_lib thrift clang gtest gtest_main LLVMSupport pthread dl)
