/*
 * Saitek X52 Pro Daemon
 *
 * Copyright (C) 2015 Nirenjan Krishnan (nirenjan@nirenjan.org)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, version 2.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

#include "libx52.h"
#include "x52_daemon_common.h"
#include "x52_daemon_control.h"

/** Common structure shared among threads */
struct x52_daemon_control x52_d;

static int main_loop()
{
    int status;

    status = x52_clock_thread_control(THREAD_ENABLE);
}

static int setup_message_queue(void)
{
    mode_t old_umask;
    mqd_t  msg_q;
    struct mq_attr attr;

    /* The queue needs to be writable by everybody */
    old_umask = umask(0);

    attr.mq_flags = 0;
    attr.mq_maxmsg = X52_DAEMON_QUEUE_DEPTH;
    attr.mq_msgsize = X52_DAEMON_MSG_SIZE;
    attr.mq_curmsgs = 0;

    /* Create the message queue for reading in blocking mode */
    msg_q = mq_open(X52_DAEMON_MSG_QUEUE, O_CREAT | O_RDONLY,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, &attr);

    if (msg_q == (mqd_t)-1) {
        return errno;
    }

    x52d.mq = msg_q;

    /* Restore the original umask */
    umask(old_umask);

    return 0;
}

int main()
{
    int ret;
    /* Ensure that we are running as root */
    if (getuid() != 0) {
        /* Insufficient permissions */
        return EPERM;
    }

    /* Initialize message queue */
    ret = setup_message_queue();
    if (ret != 0) {
        /* Unable to create message queue */
        return ret;
    }

    /* TODO: Daemonize */

    return 0;
}
