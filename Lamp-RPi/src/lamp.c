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

void on(const char id[2])
{
	char command[5];

	command[0] = 'L';
	command[1] = id[0];
	command[2] = id[1];
	command[3] = '1';
	command[4] = '\n';
	write_command(command);
}

void off(const char id[2])
{
	char command[5];

	command[0] = 'L';
	command[1] = id[0];
	command[2] = id[1];
	command[3] = '0';
	command[4] = '\n';
	write_command(command);
}
