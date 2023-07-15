#ifndef _game_h
#define _game_h

typedef struct p{
	int pixel[4][4]; 
	int id;
	int offset;
}tetromino;

int kbhit();

int readInput();

tetromino rotate();

void saveGrid();

int checkColision();

int runGame();

int game();

void fallingTetro();

void grid();

void saveGrid();

void delPrev();
#endif
