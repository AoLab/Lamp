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
#include <time.h>

#include "log.h"

#define LOG_PREFIX_FORMAT "%04d/%02d/%02d %d:%02d:%02d [%s] [%s:%d] (%d) - "

/*
 * Printable loglevels
*/
static const char* log_level_name[] =
{
      "NONE"
    , "FATAL"
    , "ERROR"
    , "WARNING"
    , "INFO"
    , "DEBUG"
    , "TRACE"
};

struct logger *LOGGER;

int log_create(struct logger **logger_p, size_t buffer_size, FILE *sink)
{
	*logger_p = malloc(sizeof(struct logger));
	(*logger_p)->sink = sink;
	(*logger_p)->buffer_size = buffer_size;
	(*logger_p)->log_buffer = malloc(sizeof(char) * buffer_size);

	return 0;
}

int log_global_create(size_t buffer_size, FILE *sink)
{
	return log_create(&LOGGER, buffer_size, sink);
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
	size_t len;

	char *path_separator_pos = strrchr(source_file, '/');
	path_separator_pos = (path_separator_pos ? path_separator_pos : strrchr(source_file, '\\'));
    	const char *truncated_name = (path_separator_pos ? path_separator_pos + 1 : source_file);

	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	len = sprintf(self->log_buffer, LOG_PREFIX_FORMAT,
			timeinfo->tm_year, timeinfo->tm_mon, timeinfo->tm_mday,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
			log_level_name[log_level],
			truncated_name, lineno, 0);

	va_list args;

	va_start(args, fmt);
	len += vsprintf(self->log_buffer + len, fmt, args);
	va_end(args);

	self->log_buffer[len] = '\n';
	self->log_buffer[len + 1] = 0;

	fputs(self->log_buffer, self->sink);
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
