# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 22-02-2016
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
cmake_minimum_required(VERSION 2.8.8)
project(Lamp)
enable_language(C)

find_package(OpenSSL REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(libs)
add_subdirectory(src)
