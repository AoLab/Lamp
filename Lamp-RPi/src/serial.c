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

#include "serial.h"
#include "common.h"

static int fd;

void open_serial(const char *dev)
{
	fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd <= 0)
		sdie("Unable to open %s - ", dev);
}

void init_serial(void)
{
	TEST_FD();

	struct termios old_tio, tio;

	/** Set serial port tio **/

	tcgetattr(fd, &old_tio);
	tcflush(fd, TCIOFLUSH);

	memset(&tio, 0, sizeof(tio));

	cfsetspeed(&tio, B9600);

    tio.c_cflag |= (CS7 | CSTOPB | PARODD);

	tcsetattr(fd, TCSAFLUSH, &tio);
	tcflush(fd, TCIOFLUSH);

}

int write_command(const char *str)
{
	TEST_FD();

	int put = 0;

	put = write(fd, str, strlen(str));
	printf("%d\n", put);
	fsync(fd);

	return put;
}

char readchar(void)
{
	TEST_FD();

	char c;

	if (!read(fd, &c, 1))
		return 0;

	return c;
}
