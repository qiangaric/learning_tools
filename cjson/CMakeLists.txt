cmake_minimum_required(VERSION 2.6)
 
#使用gcc 编辑
set(CMAKE_C_COMPILER gcc)

#设置debug模式，开启debug?不然断点调试是无效的
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 加载glib2
find_package(PkgConfig)
pkg_search_module(GLIB REQUIRED glib-2.0)
MESSAGE(STATUS "glib-2.0 dirs:" ${GLIB_INCLUDE_DIRS})
MESSAGE(STATUS "glib-2.0 lib:" ${GLIB_LIBRARIES})
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

# find_package (Threads)

#Required packages
# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
# find_package(GLIB2)

# set(CMAKE_C_FLAGS "-std=c99")
set(CMAKE_C_FLAGS "-std=c99")
# set(CMAKE_C_FLAGS_DEBUG " ${CMAKE_C_FLAGS_DEBUG} -O0 -g -ggdb  -Wall  -mavx2 -maes -msse -mssse3 -mavx")
set(CMAKE_BUILD_TYPE "Debug")
option(BUILD_DOCS "Build the documentation" ON)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")


#项目名称 
project (test)

#添加源文件
#test 为可执行文件名称
add_executable(test example.c cJson.h cJson.c )
 
#target_link_libraries(hello ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GLIB_LIBRARIES})

#添加pthread
target_link_libraries(test ${GLIB_LIBRARIES} pthread -lm )