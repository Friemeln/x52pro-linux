/*
 * Saitek X52 Pro Daemon Clock Thread
 *
 * Copyright (C) 2015 Nirenjan Krishnan (nirenjan@nirenjan.org)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, version 2.
 *
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "libx52.h"
#include "x52_daemon_common.h"

static void * clock_thread(void *context)
{
    int rc;

    /* This thread simply updates the clock display every second.
     * libx52_set_clock returns 0 only if there's a need to update the
     * clock.
     */
    for(;;) {
        rc = libx52_set_clock(x52d.dev, time(NULL),
                x52d.clock_timezone[LIBX52_CLOCK_1]);
        if (!rc) {
            libx52_update(x52d.dev);
        }
        sleep(1);
    }
}

int x52_clock_thread_control(int state)
{
    static pthread_t clock_pthr;
    static int clock_thr_running = 0;

    int status;

    if (state) {
        /* Start the thread, if it isn't already running */
        if (clock_thr_running) {
            return EEXIST;
        }

        /* Start the clock thread */
        status = pthread_create(&clock_pthr, NULL, clock_thread, NULL);
        if (status == 0) {
            clock_thr_running = 1;
        } 

        return status;
    } else {
        if (!clock_thr_running) {
            return ENOENT;
        }

        /* Cancel the clock thread */
        status = pthread_cancel(clock_pthr);
        if (status == 0) {
            clock_thr_running = 0;
        }

        return status;
    }

    return 0;
}
