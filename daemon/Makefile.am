bin_PROGRAMS = x52joyd

# Joystick daemon program that monitors and controls the X52 Pro Joystick
x52joyd_SOURCES = x52_daemon_core.c x52_daemon_clock.c x52_daemon_thread.c
x52joyd_CFLAGS = @X52_INCLUDE@
x52joyd_LDADD = ../lib/libx52/libx52.la
x52joyd_LDFLAGS = -lpthread

