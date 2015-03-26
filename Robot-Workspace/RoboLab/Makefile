# Target specific macros
TARGET = main
TARGET_SOURCES = src/main.c src/algorithms.c src/heap.c src/basics.c src/orchester.c
TOPPERS_OSEK_OIL_SOURCE = ./main.oil

BMP_SOURCES = \
    src/kappa.bmp

# Don't modify below part
O_PATH ?= build

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	INC=/Applications/robolab/nxtOSEK/toppers_osek/kernel
	include /Applications/robolab/nxtOSEK/ecrobot/ecrobot.mak
else
	INC=/cygdrive/C/cygwin/nxtOSEK/toppers_osek/kernel
	include /cygdrive/C/cygwin/nxtOSEK/ecrobot/ecrobot.mak
endif
