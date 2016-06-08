/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>

#include "serial.h"
#include "rs232.h"
#include "log.h"

static int cport_nr;

void open_serial(const char *dev)
{
	cport_nr = 24;
	int bdrate = 115200;
	char mode[] = {'8', 'E', '2', 0};

	if (RS232_OpenComport(cport_nr, bdrate, mode))
		sdie("RS232_OpenComport");
}

void write_command(const char *str)
{
	RS232_cputs(cport_nr, str);
}

int read_status(unsigned char *buff, int buff_size)
{
	return RS232_PollComport(cport_nr, buff, buff_size);
}
