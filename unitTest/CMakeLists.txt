cmake_minimum_required(VERSION 2.6)
 

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-std=c99")

find_package(PkgConfig)
find_package(PkgConfig REQUIRED)
#Required packages
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include_directories("/pgdata/clone_pg/pg15_3_data/include")
LINK_LIBRARIES(postgresql)


project (test001)
#≤‚ ‘

add_executable(test unionTest01.c)

