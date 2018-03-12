# This Makefile requires GNU make, which is called gmake on Solaris systems
#
# 'make'        : builds and runs the project
# 'make clean'  : remove build products

PROG = bin/*

OBJS = obj/*

ARCH = $(shell uname -m)
OS   = $(shell uname -s)

CC = g++

LDLIBS  = -L/usr/lib -lm -ljpeg -pthread
INCLUDE = -ITools

.PHONY: clean Prac2Parallel run
all:    clean Prac2Parallel

clean:
	rm -f -r $(PROG) $(OBJS)

Prac2Parallel:
	$(CC) $(INCLUDE) -c Prac2Parallel.cpp -o obj/Prac2Parallel.o
	$(CC) $(INCLUDE) -c Tools/JPEG.cpp -o obj/JPEG.o
	$(CC) $(INCLUDE) -c Tools/Timer.cpp -o obj/Timer.o
	$(CC) -o bin/Prac2Parallel obj/Prac2Parallel.o obj/JPEG.o obj/Timer.o $(LDLIBS)

run:
	bin/Prac2Parallel

