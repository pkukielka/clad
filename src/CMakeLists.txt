cmake_minimum_required (VERSION 2.6)

file (GLOB GENERATED_FILES "${GENERATED_FILES_DIR}/*.cpp")

add_executable (clad_serv ${GENERATED_FILES} Clad.cpp ClangHandler.cpp)

target_link_libraries (clad_serv thrift clang)
