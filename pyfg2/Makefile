#
# Makefile for libfg2 cython module
#

CFLAGS = -g -Wall
INCDIR = -I../include
LIBDIR = -L../lib

all: pyfg2.so

pyfg2.so:
	cython $(INCDIR) -o pyfg2.c -2 pyfg2.pyx
	gcc $(CFLAGS) $(INCDIR) -c -fPIC -I/usr/include/python2.7 pyfg2.c
	gcc $(CFLAGS) -shared pyfg2.o $(LIBDIR) -lfg2 -o pyfg2.so

clean:
	rm -f pyfg2.c
	rm -f pyfg2.o
	rm -f pyfg2.so
	
