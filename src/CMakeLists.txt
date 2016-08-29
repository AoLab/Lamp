# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 22-02-2016
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
add_executable(Lamp-RPi.out main.c
	serial.c serial.h
	log.c log.h
	notification.c notification.h
	lamp.c lamp.h
	rs232.c rs232.h)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${Lamp-RPi_SOURCE_DIR}/libs/src")
target_link_libraries(Lamp-RPi.out kaac crypto)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -g -Wall")
