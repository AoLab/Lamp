/*
 * In The Name Of God
 * ========================================
 * [] File Name : common.c
 *
 * [] Creation Date : 12-12-2014
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2014 Parham Alvani.
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

int log_create(struct logger *logger_p, size_t buffer_size, FILE *sink)
{
}

void sdie(struct logger *self, const char *source_file, int lineno, const char *fmt, ...)
{
	char buf[self->buffer_size];
	va_list args;

	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	perror(buf);
	exit(EXIT_FAILURE);

}

void udie(struct logger *self, const char *source_file, int lineno, const char *fmt, ...)
{
	char buf[self->buffer_size];
	va_list args;

	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	size_t len = strlen(buf);

	buf[len] = '\n';
	buf[len + 1] = 0;

	fputs(buf, self->sink);
	exit(EXIT_FAILURE);

}

void ulog(struct logger *self, const char *source_file, int lineno, int log_level, const char *fmt, ...)
{
	printf("DEBUG: ");
	fflush(stdout);

	char buf[self->buffer_size];
	va_list args;

	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	size_t len = strlen(buf);

	buf[len] = '\n';
	buf[len + 1] = 0;

	fputs(buf, self->sink);
}

void slog(struct logger *self, const char *source_file, int lineno, int log_level, const char *fmt, ...)
{
	printf("DEBUG: ");
	fflush(stdout);

	char buf[self->buffer_size];
	va_list args;

	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	perror(buf);
}	
