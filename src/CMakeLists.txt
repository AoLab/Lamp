# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 22-02-2016
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
add_executable(Lamp.out main.c
	serial.c serial.h
	common.c common.h)

include_directories("${Lamp_SOURCE_DIR}/libs/src")
target_link_libraries(Lamp.out kaac crypto)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -g -Wall")
