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
	route.h route.c
	kaa.h kaa.c
	event.h event.c
	user.h user.c
	response.h response.c)

find_package(PkgConfig)
pkg_check_modules(LIBSOUP REQUIRED libsoup-2.4)
include_directories(${LIBSOUP_INCLUDE_DIRS})
link_directories(${LIBSOUP_LIBRARY_DIRS})
target_link_libraries (Lamp-REST.out ${LIBSOUP_LIBRARIES})
pkg_check_modules(LIBJSON REQUIRED json-glib-1.0)
include_directories(${LIBJSON_INCLUDE_DIRS})
link_directories(${LIBJSON_LIBRARY_DIRS})
target_link_libraries (Lamp-REST.out ${LIBJSON_LIBRARIES})

include_directories("${Lamp-REST_SOURCE_DIR}/libs/src")
target_link_libraries(Lamp-REST.out kaac crypto)

include_directories("${PROJECT_BINARY_DIR}")

# Add personal c flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0 -g -std=gnu11 ")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -DDEBUG")
