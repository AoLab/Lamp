
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

/* Use as the max log level to switch logging off */
#define LOG_LEVEL_NONE  0
/* Use for severe errors that cause premature program termination */
#define LOG_LEVEL_FATAL 1
/* Use for runtime errors or unexpected conditions that the program might gracefully recover from */
#define LOG_LEVEL_ERROR 2
/* Use for unexpected or undesirable runtime conditions that are not necessarily affecting the program */
#define LOG_LEVEL_WARN  3
/* Use for important or interesting runtime events that help understanding what the program is doing */
#define LOG_LEVEL_INFO  4
/* Use to log detailed information on the logic flow through the system */
#define LOG_LEVEL_DEBUG 5
/* Use to log most detailed information intended for development and debugging purposes only */
#define LOG_LEVEL_TRACE 6

#ifndef MAX_LOG_LEVEL
/* Use KAA_LOG_TRACE as the max log level by default */
#define MAX_LOG_LEVEL   KAA_LOG_LEVEL_TRACE
#endif

#define LOG_LEVEL_FATAL_ENABLED     (MAX_LOG_LEVEL >= LOG_LEVEL_FATAL)
#define LOG_LEVEL_ERROR_ENABLED     (MAX_LOG_LEVEL >= LOG_LEVEL_ERROR)
#define LOG_LEVEL_WARN_ENABLED      (MAX_LOG_LEVEL >= LOG_LEVEL_WARN)
#define LOG_LEVEL_INFO_ENABLED      (MAX_LOG_LEVEL >= LOG_LEVEL_INFO)
#define LOG_LEVEL_DEBUG_ENABLED     (MAX_LOG_LEVEL >= LOG_LEVEL_DEBUG)
#define LOG_LEVEL_TRACE_ENABLED     (MAX_LOG_LEVEL >= LOG_LEVEL_TRACE)

int log_create(struct logger *logger_p, size_t buffer_size, FILE *sink);

void sdie(struct logger *self, const char *source_file, int lineno, const char *fmt, ...)
    __attribute__((format(printf, 4, 5)));

void udie(struct logger *self, const char *source_file, int lineno, const char *fmt, ...)
    __attribute__((format(printf, 4, 5)));

void ulog(struct logger *self, const char *source_file, int lineno, int log_level, const char *fmt, ...)
    __attribute__((format(printf, 5, 6)));

void slog(struct logger *self, const char *source_file, int lineno, int log_level, const char *fmt, ...)
    __attribute__((format(printf, 5, 6)));

/*
 * Shortcut macros for logging at various log levels
 */
#if LOG_LEVEL_FATAL_ENABLED
#define LOG_FATAL(logger, fmt, ...) ulog(logger, __FILE__, __LINE__, KAA_LOG_LEVEL_FATAL, fmt, __VA_ARGS__)
#else
#define LOG_FATAL(...)
#endif

#if LOG_LEVEL_ERROR_ENABLED
#define LOG_ERROR(logger, fmt, ...) ulog(logger, __FILE__, __LINE__, KAA_LOG_LEVEL_ERROR, fmt, __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#if LOG_LEVEL_WARN_ENABLED
#define LOG_WARN(logger, fmt, ...)  ulog(logger, __FILE__, __LINE__, KAA_LOG_LEVEL_WARN, fmt, __VA_ARGS__)
#else
#define LOG_WARN(...)
#endif

#if LOG_LEVEL_INFO_ENABLED
#define LOG_INFO(logger, fmt, ...)  ulog(logger, __FILE__, __LINE__, KAA_LOG_LEVEL_INFO, fmt, __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#if LOG_LEVEL_DEBUG_ENABLED
#define LOG_DEBUG(logger, fmt, ...) ulog(logger, __FILE__, __LINE__, KAA_LOG_LEVEL_DEBUG, fmt, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

#if LOG_LEVEL_TRACE_ENABLED
#define LOG_TRACE(logger, fmt, ...) ulog(logger, __FILE__, __LINE__, KAA_LOG_LEVEL_TRACE, fmt, __VA_ARGS__)
#else
#define LOG_TRACE(...)
#endif

#endif
