cmake_minimum_required (VERSION 2.6)

file (GLOB GENERATED_FILES "${GENERATED_FILES_DIR}/*.cpp")

add_library (clad_serv_lib ${GENERATED_FILES} ClangHandler.cpp)

add_executable (clad_serv Clad.cpp)

target_link_libraries (clad_serv clad_serv_lib thrift clang)
