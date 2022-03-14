/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef SVM_LOG_H
#define SVM_LOG_H

#ifndef SVM_NO_LOG

/// Trace log info.
#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
/// Debug log info.
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
/// Info log info.
#define log_info(...)  log_log(LOG_INFO,  __FILE__,  __LINE__, __VA_ARGS__)
/// Warn log info.
#define log_warn(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
/// Erorr log info.
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
/// Fatal log info. Does not bail.
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#else /* SVM_NO_LOG */

#define log_trace(...) {}
#define log_debug(...) {}
#define log_info(...) {}
#define log_warn(...) {}
#define log_error(...) {}
#define log_fatal(...) {}

#endif /* SVM_NO_LOG */

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

/** No idea what this does. */
#define LOG_VERSION "0.1.0"

/** A log event. */
typedef struct {
  va_list ap;
  const char *fmt;
  const char *file;
  int line;
  struct tm *time;
  void *udata;
  int level;
} log_event;

typedef void (*log_LogFn)(log_event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

/// Log levels.
enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

/// Get the log level as a string.
const char* log_level_string(int level);
/// Lock logging.
void log_set_lock(log_LockFn fn, void *udata);
/// Set minimum logging level.
void log_set_level(int level);
/// Set log quitely.
void log_set_quiet(bool enable);
/// Add logging callback.
int log_add_callback(log_LogFn fn, void *udata, int level);
/// Add a file pointer.
int log_add_fp(FILE *fp, int level);
/// Actually log.
void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif /* SVM_LOG_H */
