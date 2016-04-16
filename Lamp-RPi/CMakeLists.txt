# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 22-02-2016
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
cmake_minimum_required(VERSION 2.8.8)
project(Lamp-RPi)
enable_language(C)

find_package(OpenSSL REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(LAMP_ROOM_NUMBER 203)
set(LAMP_ROOM_OWNER "\"Parham Alvani\"")
set(LAMP_SERIAL_PATH "\"/dev/tnt0\"")

message("LAMP_ROOM_NUMBER: ${LAMP_ROOM_NUMBER}")
message("LAMP_ROOM_OWNER: ${LAMP_ROOM_OWNER}")
message("LAMP_SERIAL_PATH: ${LAMP_SERIAL_PATH}")

# Configuration header file
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)

add_subdirectory(libs)
add_subdirectory(src)
