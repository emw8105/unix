SOURCES = $(wildcard *.c)
EXECS = $(SOURCES:%.c=%)
CFLAGS = -std=c99 -g -lpthread -lm
CC=gcc

all: $(EXECS)

array: array.c const.h

clean: 
	rm $(EXECS)
