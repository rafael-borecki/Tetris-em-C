TARGET=tetris
CC=gcc
DEBUG=-g
OPT=-O0
WARN=-Wall
CURSES=-lncurses
TINFO=-ltinfo
BOOT=boot.c
GAME=game.c
HISCORE=hiscore.c
CCFLAGS=$(DEBUG) $(OPT) $(WARN)
LD=gcc
OBJS=tetris.c
all: tetris.c
	$(LD) -o $(TARGET) $(OBJS) $(DEBUG) $(OPT) $(WARN) $(CURSES) $(BOOT) $(GAME) $(HISCORE) $(TINFO)
