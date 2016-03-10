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

    ulog("TEST_FD ejra :)");

    struct termios old_tio, tio;

    /* ** Set serial port tio ** */

    /* Backup port settings */
    tcgetattr(fd, &old_tio);
    ulog("TEST_FD tcgetattr:)");
    tcflush(fd, TCIOFLUSH);

    memset(&tio, 0, sizeof(tio));

    cfsetspeed(&tio, B9600);

    tcsetattr(fd, TCSAFLUSH, &tio);
    ulog("TEST_FD tcsetattr:)");
    tcflush(fd, TCIOFLUSH);
}

int writechar(char c)
{
    TEST_FD();

    int put = 0;

    put = write(fd, &c, 1);
    fsync(fd);

    return put;
}
