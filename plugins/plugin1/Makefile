# Simple makefile for gcc written by stext editor.
CC=gcc
CFLAGS=-std=c11 -W -O -g -fPIC -shared -I../../libprs/include -I../../src
LDFLAGS=

BACKUPS=$(shell find . -iname "*.bak")
SRCDIR=$(shell basename $(shell pwd))
DESTDIR?=
PREFIX?=usr/local
VERSION=1.0

SOURCE=$(wildcard *.c)
OBJECTS=$(SOURCE:%.c=%.c.o)
TARGET=../plugin1.so

.PHONY: all clean  distclean
all: $(TARGET)

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

distclean: clean
ifneq ($(BACKUPS),)
	rm -f *.bak
endif
