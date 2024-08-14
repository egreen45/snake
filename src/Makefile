IDIR_USR = ../include
IDIR_SDL = /usr/local/Cellar/sdl2/2.0.22/include/
LDIR_SDL = /usr/local/Cellar/sdl2/2.0.22/lib/

CC = gcc
CFLAGS = -Wall -Wextra -I$(IDIR_USR) -I$(IDIR_SDL) 

ODIR = obj
LIBS = -L$(LDIR_SDL) -lSDL2-2.0.0

SRCS = snake.c snakefunc.c
_OBJS = snake.o snakefunc.o
OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

_DEPS = snake.h
DEPS = $(patsubst %, $(IDIR_USR)/%, $(_DEPS))

MAIN = snake

$(MAIN): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean

clean: 
	rm -f $(ODIR)/*.o *~ core $(MAIN)
