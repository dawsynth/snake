TARGETS := snake snake.js

all: desktop
desktop: snake
web: snake.js

desktop: CC = gcc
web: CC = emcc

desktop: CFLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2 -lm
web: CFLAGS = -s USE_SDL=2

HDRS := render.h player.h linkedlist.h

SRCS := main.c render.c player.c linkedlist.c

OBJS := $(SRCS:.c=.o)

$(OBJS) : $(@:.o=.c) $(HDRS) Makefile
	$(CC) -c $(@:.o=.c) -o $@ $(CFLAGS)

$(TARGETS) : $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(TARGETS) $(OBJS) *.wasm

.PHONY: all desktop web clean
