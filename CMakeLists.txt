cmake_minimum_required(VERSION 2.8.4)

project(sdump C)

set(PCRE_LIBS_PATH "/usr/local/lib" CACHE INTERNAL "")
set(PCRE_INCS_PATH "/usr/local/include" CACHE INTERNAL "")
set(CMAKE_C_FLAGS "-Wall -g")

add_executable(sdump sdump.c main.c)
target_link_libraries(sdump m)
