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
#include "common.h"

static int fd;

void open_serial(const char *dev)
{
	fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd <= 0)
		sdie("Unable to open %s - ", dev);
	fcntl(fd, F_SETFL, 0);
}

int set_interface_attribs(int fd, int speed, int parity)
{
        struct termios tty;

	if (tcgetattr (fd, &tty) != 0) {
                sdie("tcgetattr");
                return -1;
        }

	/* set the baud rate */
        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

	/* 8-bit chars */
        tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;

	/* ignore moden control and enable reading */
        tty.c_cflag |= (CLOCAL | CREAD);

	/* shutoff parity */
        tty.c_cflag &= ~PARENB;
	
	/* 1 stop bit */
        tty.c_cflag &= ~CSTOPB;

	/* raw output */
	tty.c_oflag = 0;

        if (tcsetattr (fd, TCSANOW, &tty) != 0) {
                sdie("tcsetattr");
                return -1;
        }

        return 0;
}

void init_serial(void)
{
	TEST_FD();
	set_interface_attribs(fd, B115200, 0);
}

int write_command(const char *str)
{
	TEST_FD();

	int put = 0;

	put = write(fd, str, strlen(str));
	if (put < strlen(str))
		slog("write(%d, %s, %zd) failed", fd, str, strlen(str));

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
