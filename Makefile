CC := gcc
web: CC = emcc

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2 -lm
web: CFLAGS = -s USE_SDL=2

HDRS := render.h player.h linkedlist.h

SRCS := main.c render.c player.c linkedlist.c

OBJS := $(SRCS:.c=.o)

EXEC := snake
web: EXEC = snake.js

$(OBJS) : $(@:.o=.c) $(HDRS) Makefile
	$(CC) -c $(@:.o=.c) -o $@ $(CFLAGS)

all: $(EXEC)
web: $(EXEC)

$(EXEC) : $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)


clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all web clean
