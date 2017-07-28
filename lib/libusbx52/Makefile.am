ACLOCAL_AMFLAGS = -I m4

# libusb stub library for use by test programs
noinst_LTLIBRARIES = libusbx52.la

libusbx52_la_SOURCES = usb_x52_stub.c
libusbx52_la_LDFLAGS = -rpath /nowhere

# Utility programs for use by tests
noinst_PROGRAMS = x52test_create_device_list x52test_log_actions

x52test_create_device_list_SOURCES = util/create_device_list.c

x52test_log_actions_SOURCES = util/log_actions.c
x52test_log_actions_CFLAGS = @X52_INCLUDE@
x52test_log_actions_LDADD = libusbx52.la

EXTRA_DIST = README.md libusbx52.h