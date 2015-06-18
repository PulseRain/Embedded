AUTOMAKE_OPTIONS = foreign subdir-objects
bin_PROGRAMS = demo
SUBDIRS = .
demo_SOURCES = src/align/align.c src/common/about.c src/common/CRC32.c src/state_machine/state_machine.c src/main/main.c
CFLAGS = -I$(top_srcdir)/src/common/include
CFLAGS += -I$(top_srcdir)/src/align
CFLAGS += -I$(top_srcdir)/src/state_machine
CFLAGS += -I$(top_srcdir)/src/main

CFLAGS += -g -W -DDEBUG  -DCONSOLE_PRINT=printf 
CFLAGS += -DVMAJOR=1 -DVMINOR=3g
CFLAGS += -DPRODUCT_NAME="A SUPER Product"

CFLAGS += -DCONFIG_CHECK_ABOUT_SIGNATURE
CFLAGS += -DCONFIG_ENABLE_ALIGNMENT_MODULE
CFLAGS += -DCONFIG_ENABLE_STATE_MACHINE_MODULE
