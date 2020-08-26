# Simple makefile for gcc written by stext editor.
CC=gcc
CFLAGS=-std=c11 -W -O -g -I./libprs/include
LDFLAGS=-ldl -L./libprs/build -lprs

LIBPRS=$(shell find . -iname "libprs" -type d)
BACKUPS=$(shell find . -iname "*.bak")
SRCDIR=$(shell basename $(shell pwd))
DESTDIR?=
PREFIX?=usr/local
VERSION=1.0

SOURCE=$(wildcard *.c)
OBJECTS=$(SOURCE:%.c=%.c.o)
TARGET=plugin

.PHONY: all install uninstall clean  distclean dist
all: $(TARGET)
	cd plugins && $(MAKE) all

libprs:
	echo "Downloading dependency..."
	git clone https://github.com/psimonson/libprs.git && echo "Done." || echo "Failed."
	(cd libprs && ./build.sh) && echo "Done." || echo "Failed"

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): libprs $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

install: all
	install $(TARGET) $(DESTDIR)/$(PREFIX)/bin

uninstall:
	rm -f $(DESTDIR)/$(PREFIX)/bin/$(TARGET)

clean:
	cd plugins && $(MAKE) clean
	rm -f $(OBJECTS) $(TARGET)

distclean: clean
	cd plugins && $(MAKE) distclean
ifneq ($(LIBPRS),)
	rm -rf $(LIBPRS)
endif
ifneq ($(BACKUPS),)
	rm -f *.bak
endif

dist: distclean
	cd .. && tar -cv --exclude=.git ./$(SRCDIR) | xz -9 > $(SRCDIR)-$(VERSION).tar.xz
