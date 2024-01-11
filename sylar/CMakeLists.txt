cmake_minimum_required(VERSION 2.6)
 
#使用gcc 编辑
set(CMAKE_C_COMPILER gcc)

#设置debug模式，开启debug?不然断点调试是无效的
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# 设置C++标准
# set(CMAKE_CXX_STANDARD 11)  # 将 C++ 标准设置为 C++ 11
# set(CMAKE_CXX_STANDARD_REQUIRED ON)  # C++ 11 是强制要求，不会衰退至低版本

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 打印此版本的 CMake 的已知编译特性列表
message("List of compile features: ${CMAKE_CXX_COMPILE_FEATURES}")

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


option(BUILD_DOCS "Build the documentation" ON)


#项目名称 
project (test)

#添加源文件
#test 为可执行文件名称
# add_executable(test sylar/parseBinlog.cpp)
add_executable(test sylar/vectorTest.cpp)
 
#target_link_libraries(hello ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GLIB_LIBRARIES})

#添加pthread
target_link_libraries(test ${GLIB_LIBRARIES} pthread )