/*
 * In The Name Of God
 * ========================================
 * [] File Name : lamp.c
 *
 * [] Creation Date : 27-03-2016
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2016 Parham Alvani.
*/

#include <unistd.h>

#include "lamp.h"
#include "serial.h"

void lamp(int interval)
{
	writechar('1');

	sleep(interval);

	writechar('0');
}
