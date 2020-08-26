# Simple makefile for gcc written by stext editor.
CC=gcc
CFLAGS=-std=c11 -W -O -g -fPIC -shared
LDFLAGS=

BACKUPS=$(shell find . -iname "*.bak")
SRCDIR=$(shell basename $(shell pwd))
DESTDIR?=
PREFIX?=usr/local
VERSION=1.0

.PHONY: all clean  distclean
all:
	cd plugin1 && $(MAKE) all
	cd plugin2 && $(MAKE) all

clean:
	cd plugin1 && $(MAKE) clean
	cd plugin2 && $(MAKE) clean

distclean: clean
	cd plugin1 && $(MAKE) distclean
	cd plugin2 && $(MAKE) distclean
ifneq ($(BACKUPS),)
	rm -f *.bak
endif
