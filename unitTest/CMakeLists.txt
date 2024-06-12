cmake_minimum_required(VERSION 2.6)
 

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-std=c99")

find_package(PkgConfig)
find_package(PkgConfig REQUIRED)
#Required packages
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
# find_package(PostgreSQL REQUIRED)
# target_link_libraries(test PRIVATE PostgreSQL::PostgreSQL)
# # LINK_LIBRARIES(postgresql)

# # This command attempts to find the library, REQUIRED argument is optional
# find_package(PostgreSQL REQUIRED)

# # Add include directories to your target. PRIVATE is useful with multi-target projects - see documentation of target_include_directories for more info
# target_include_directories(test PRIVATE ${PostgreSQL_INCLUDE_DIRS})

# # Add libraries to link your target againts. Again, PRIVATE is important for multi-target projects
# target_link_libraries(test PRIVATE ${PostgreSQL_LIBRARIES})

# set(PostgreSQL_ADDITIONAL_VERSIONS "15.3")
# set(PostgreSQL_ADDITIONAL_SEARCH_PATHS ${PostgreSQL_ADDITIONAL_SEARCH_PATHS} "/usr/include/postgresql")

set(PostgreSQL_LIBRARIES, "/pgdata/clone_pg/pg15_3_data/")
set(PostgreSQL_LIBRARY_DIRS, "/pgdata/clone_pg/pg15_3_data/")
set(PostgreSQL_LIBRARY_DIRS, "/pgdata/clone_pg/pg15_3_data/")
find_package(PostgreSQL REQUIRED)
target_link_libraries(test ${PostgreSQL_LIBRARIES})
if(WIN32)
  target_link_libraries(multicorn postgres)
endif(WIN32)
target_link_directories(test PUBLIC ${PostgreSQL_LIBRARY_DIRS})
target_include_directories(test PUBLIC ${PostgreSQL_INCLUDE_DIRS})
if(WIN32)
  target_include_directories(multicorn PUBLIC ${PostgreSQL_INCLUDE_DIR}/server/port/win32)
endif()
if(MSVC)
  target_include_directories(multicorn PUBLIC ${PostgreSQL_INCLUDE_DIR}/server/port/win32_msvc)
endif()

project (test)


add_executable(test unionTest01.c)

