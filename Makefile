# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc
WASMCC := emcc

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2 -lm
WASMFLAGS := -s USE_SDL=2

# add header files here
HDRS := render.h player.h linkedlist.h

# add source files here
SRCS := main.c render.c player.c linkedlist.c

# generate names of object files
OBJS := $(SRCS:.c=.o)
OBJSWEB := $(SRCS:.c=.o)

# name of executable
EXEC := snake
WASM := snake.js

$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -c $(@:.o=.c) -o $@ $(CFLAGS)

ifeq (arg2, 'web')
$(OBJSWEB): $(@:.o=.c) $(HDRS) Makefile
	$(WASMCC) -c $(@:.o=.c) -o $@ $(WASMFLAGS)
endif

# default recipe
desktop: $(EXEC)
web: $(WASM)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

$(WASM): $(OBJSWEB) $(HDRS) Makefile
	$(WASMCC) $(OBJSWEB) -o $@ $(WASMFLAGS)

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f snake ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/snake

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
