/*
 * Saitek X52 Pro Daemon Thread Library
 *
 * Copyright (C) 2015 Nirenjan Krishnan (nirenjan@nirenjan.org)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, version 2.
 *
 */

/* This file defines standard thread API for internal thread creation */

#ifndef X52_DAEMON_THREAD_H
#define X52_DAEMON_THREAD_H

#define THREAD_START    0x1
#define THREAD_STOP     0x0

#define THREAD_FN(name) int x52_ ## name ## _thread(int state)

#define THREAD_DEF(name) \
static pthread_t name ## _pthr; \
static int name ## _thr_running; \
THREAD_FN(name) \
{ \
    int status; \
    if (state == THREAD_START) { \
        if (name ## _thr_running) { \
            return EEXIST; \
        } \
        status = pthread_create(& name ## _pthr, NULL, )
    }
}

#endif /* X52_DAEMON_THREAD_H */
