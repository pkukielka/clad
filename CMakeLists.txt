cmake_minimum_required (VERSION 2.6)

project (clang-serv)

set (CMAKE_C_COMPILER   	"clang")
set (CMAKE_CXX_COMPILER 	"clang++")
set (CMAKE_CXX_FLAGS    	"${CMAKE_CXX_FLAGS} -std=c++11 -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H")

set (SRC_DIR 				"${PROJECT_SOURCE_DIR}/src")
set (THRIFT_DIR				"${PROJECT_SOURCE_DIR}/thrift")
set (GENERATED_FILES_DIR	"${SRC_DIR}/generated")

add_custom_target (			gen-serv
  COMMAND 					rm -Rf "${GENERATED_FILES_DIR}/*"	
  COMMAND 					thrift -r --gen cpp -out "${GENERATED_FILES_DIR}" "${THRIFT_DIR}/Clang.thrift"
)

file (GLOB THRIFT_SOURCES 	"${GENERATED_FILES_DIR}/*.cpp")

add_executable (${PROJECT_NAME} ${THRIFT_SOURCES} "${SRC_DIR}/ClangServ.cpp")

target_link_libraries(${PROJECT_NAME} thrift clang)