
/*
 * In The Name Of God
 * ========================================
 * [] File Name : common.h
 *
 * [] Creation Date : 21-12-2014
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2014 Parham Alvani.
*/
#ifndef LOG_H
#define LOG_H

struct logger {
	FILE *sink;
	char *log_buffer;
	size_t buffer_size;
};

int log_create(logger *logger_p, size_t buffer_size, FILE *sink);

void sdie(struct logger *self, const char *source_file, int lineno, const char *fmt, ...)
    __attribute__((format(printf, 4, 5)));

void udie(struct logger *self, const char *source_file, int lineno, const char *fmt, ...)
    __attribute__((format(printf, 4, 5)));

void ulog(struct logger *self, const char *source_file, int lineno, int log_level, const char *fmt, ...)
    __attribute__((format(printf, 5, 6)));

void slog(struct logger *self, const char *source_file, int lineno, int log_level, const char *fmt, ...)
    __attribute__((format(printf, 5, 6)));

#endif
