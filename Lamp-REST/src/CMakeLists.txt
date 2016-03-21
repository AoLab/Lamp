# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 15-02-2016
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
add_executable(Lamp-REST.out main.c
	server.h server.c
	route.h route.c)

find_package(PkgConfig)
pkg_check_modules(LIBSOUP REQUIRED libsoup-2.4)
include_directories(${LIBSOUP_INCLUDE_DIRS})
link_directories(${LIBSOUP_LIBRARY_DIRS})
target_link_libraries (Lamp-REST.out ${LIBSOUP_LIBRARIES})

#include_directories("${Lamp-REST_SOURCE_DIR}/libs/src")
#target_link_libraries(Lamp-REST.out kaac crypto)

include_directories("${PROJECT_BINARY_DIR}")

# Add personal c flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0 -g -std=gnu11 ")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -DDEBUG")
