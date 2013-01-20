cmake_minimum_required (VERSION 2.6)

#================================================
# Project
#================================================
project (clad)

#================================================
# Directories
#================================================
set (SRC_DIR              "${PROJECT_SOURCE_DIR}/src")
set (THRIFT_DIR           "${PROJECT_SOURCE_DIR}/thrift")
set (SERV_DIR             "${PROJECT_SOURCE_DIR}/src")
set (TEST_DIR             "${PROJECT_SOURCE_DIR}/test")
set (GENERATED_FILES_DIR  "${SRC_DIR}/generated")

#================================================
# Compilation options
#================================================
set (CMAKE_C_COMPILER     "clang")
set (CMAKE_CXX_COMPILER   "clang++")
set (CMAKE_CXX_FLAGS      "${CMAKE_CXX_FLAGS} -Weverything -Werror -std=c++11 -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H")
set (CMAKE_CXX_FLAGS      "${CMAKE_CXX_FLAGS} -Wno-weak-vtables -Wno-padded -Wno-global-constructors -Wno-c++98-compat")
set (CMAKE_CXX_FLAGS      "${CMAKE_CXX_FLAGS} -Wno-missing-variable-declarations -Wno-exit-time-destructors -Wno-unused-macros")

include_directories (${SRC_DIR})

#================================================
# Subprojects
#================================================
add_subdirectory (${SERV_DIR})
add_subdirectory (${TEST_DIR})

#================================================
# Auto-generation of server using Thift
#================================================
add_custom_target (       gen-serv
  COMMAND                 rm -Rf "${GENERATED_FILES_DIR}/*"
  COMMAND                 thrift -r --gen cpp -out "${GENERATED_FILES_DIR}" "${THRIFT_DIR}/Clang.thrift"
)

#================================================
# Enable testing
#===============================================
enable_testing ()

add_test (test "${CMAKE_CURRENT_BINARY_DIR}/test/clad_test")
