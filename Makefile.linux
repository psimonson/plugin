# Simple makefile for gcc written by stext editor.
CC=gcc
CFLAGS=-std=c11 -W -O -g -I./libprs/include -I./src
LDFLAGS=-ldl -L./libprs/build -L. -lprs

LIBPRS=$(shell find . -iname "libprs" -type d)
BACKUPS=$(shell find . -iname "*.bak")
SRCDIR=$(shell basename $(shell pwd))
DESTDIR?=
PREFIX?=usr/local
VERSION=1.0

SOURCE=$(wildcard *.c)
OBJECTS=$(SOURCE:%.c=%.c.o)
TARGET=plugin

SOURCE2=$(wildcard src/*.c)
OBJECTS2=$(SOURCE2:%.c=%.c.o)
TARGET2=libpluginmanager.so

.PHONY: all install uninstall clean  distclean dist
all: $(TARGET)
	cd plugins && $(MAKE) all

libprs:
	echo "Downloading dependency..."
	git clone https://github.com/psimonson/libprs.git && echo "Done." || echo "Failed."
	(cd libprs && ./build.sh) && echo "Done." || echo "Failed"

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/%.c.o: src/%.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

$(TARGET2): libprs $(OBJECTS2)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJECTS2) $(LDFLAGS)

$(TARGET): libprs $(TARGET2) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) ./$(TARGET2)

install: all
	install $(TARGET) $(DESTDIR)/$(PREFIX)/bin

uninstall:
	rm -f $(DESTDIR)/$(PREFIX)/bin/$(TARGET)

clean:
	cd plugins && $(MAKE) clean
	rm -f $(OBJECTS2) $(TARGET2) $(OBJECTS) $(TARGET)

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
