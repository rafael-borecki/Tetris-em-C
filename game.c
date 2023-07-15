#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hiscore.h"
#include "boot.h"
#include "game.h"

#define SZ_Y getmaxy(stdscr)
#define SZ_X getmaxx(stdscr)

#define RX (SZ_X/2 - 11)
#define RY (SZ_Y/2 - 11)

int gridvar[22][22];

void initGrid(int gridvar[][22]){
	for(int i = 0; i < 22; i++){
		for(int j = 0; j < 22; j++){
			if(i == 0 || i == 21 || j == 0 || j == 21)
				gridvar[i][j] = 1;
			else
				gridvar[i][j] = 0;
		}
	}
}


tetromino line_0  = {{{4,4,4,4},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 2};
tetromino line_90 = {{{4,0,0,0},{3,0,0,0},{2,0,0,0},{1,0,0,0}}, 2};
tetromino cube    =	{{{4,4,0,0},{3,3,0,0},{0,0,0,0},{0,0,0,0}}, 3};
tetromino t_0     =	{{{4,0,0,0},{3,3,0,0},{2,0,0,0},{0,0,0,0}}, 4};
tetromino t_90    =	{{{4,4,4,0},{0,3,0,0},{0,0,0,0},{0,0,0,0}}, 4};
tetromino t_180   =	{{{0,4,0,0},{3,3,0,0},{0,2,0,0},{0,0,0,0}}, 4};
tetromino t_270   =	{{{0,4,0,0},{3,3,3,0},{0,0,0,0},{0,0,0,0}}, 4};
tetromino l_0     =	{{{4,0,0,0},{3,0,0,0},{2,2,0,0},{0,0,0,0}}, 5};
tetromino l_90    =	{{{4,4,4,0},{3,0,0,0},{0,0,0,0},{0,0,0,0}}, 5};
tetromino l_180   =	{{{4,4,0,0},{0,3,0,0},{0,2,0,0},{0,0,0,0}}, 5};
tetromino l_270   =	{{{0,0,4,0},{3,3,3,0},{0,0,0,0},{0,0,0,0}}, 5};
tetromino z_0     =	{{{0,4,4,0},{3,3,0,0},{0,0,0,0},{0,0,0,0}}, 6};
tetromino z_90    =	{{{4,0,0,0},{3,3,0,0},{0,2,0,0},{0,0,0,0}}, 6};


int kbhit(){
	int ch = getch();
	if(ch != ERR){
		ungetch(ch);
		return 1;
	} else {
		return 0;
	}
}


int readInput(){
	int input;
	int update = 0;
	if(kbhit()){
		input = getch();
		if(input == 'd' || input == 'D')
			update += 1;
		if(input == 'a' || input == 'A')
			update -= 1;
		if(input == ' ')
			update = 2;
		if(input == 'r' || input == 'R')
			update = 3;
		if(input == 'x' || input == 'X')
			update = 4;
	}
	return update;
}


void printTetr(int y, int x, tetromino falling){
	attron(COLOR_PAIR(falling.id));
	if(y > 0){
		for(int i = 0; i < 4; i++){
			for(int j = 0;j < 4; j++){
				if(falling.pixel[j][i]){
					mvprintw(j + y + RY, 2 * i + x + RX, "##"); 
				}
			}
		}
	}
	attroff(COLOR_PAIR(falling.id));
}


void delPrev(int y, int x, tetromino falling){
	if(y > 0){
		for(int i = 0; i < 4; i++){
			for(int j = 0;j < 4; j++){
				if(falling.pixel[j][i]){
					mvprintw(j + y + RY, 2*i + x + RX, ".."); 
				}
			}
		}	
	}
}


tetromino chooseTet(int choose){
	tetromino falling;
	if(choose == 0){
		falling = line_0;
	}
	if(choose == 1){
		falling = cube;
	}
	if(choose == 2){
		falling = t_0;
	}
	if(choose == 3){
		falling = l_0;
	}
	if(choose == 4){
		falling = z_0;
	}
	return falling;
}


tetromino rotate(int rotation, tetromino falling){
	if(falling.id == 2){
		if(rotation % 2 == 0)
			falling = line_0;
		else
			falling = line_90;
	}
	if(falling.id == 3){
		falling = cube;
	}
	if(falling.id == 4){
		if(rotation % 4 == 0)
			falling = t_0;
		if(rotation % 4 == 1)
			falling = t_90;
		if(rotation % 4 == 2)
			falling = t_180;
		if(rotation % 4 == 3)
			falling = t_270;
	}
	if(falling.id == 5){
		if(rotation % 4 == 0)
			falling = l_0;
		if(rotation % 4 == 1)
			falling = l_90;
		if(rotation % 4 == 2)
			falling = l_180;
		if(rotation % 4 == 3)
			falling = l_270;
	}
	if(falling.id == 6){
		if(rotation % 2 == 0)
			falling = z_0;
		if(rotation % 2 == 1)
			falling = z_90;
	}
	return falling;
};


void grid(int gridvar[][22]){
	for(int i = 0; i < 22; i++){
		for(int j = 0; j < 22; j++){
			//			mvprintw(j + RY,RX-3,"%d",j); CONTADOR DE LINHAS RELATIVAS
			if(gridvar[j][i] < 1)
				mvprintw(j + RY, i + RX, "%c", gridvar[j][i] + 46);
			if(gridvar[j][i] > 1){
				attron(COLOR_PAIR(gridvar[j][i]));
				mvprintw(j + RY, i + RX,"##");
				attroff(COLOR_PAIR(gridvar[j][i]));
			}
		}
	}
};


void saveGrid(int current_y, int current_x, tetromino falling, int gridvar[][22]){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(falling.pixel[j][i] != 0){
				gridvar[current_y + j][current_x + 2 * i] = falling.id;
				gridvar[current_y + j][current_x + 2 * i + 1] = falling.id;
			}	
		}
	}
};


int checkCollision(int current_y, int current_x, tetromino falling, int gridvar[][22]){
	int collision = 0;
	for(int i = 3; i > -1; i--){
		for(int j = 0; j < 4; j++){
			if((gridvar[current_y + j + 1][current_x + 2 * i] != 0) && falling.pixel[j][i]){
				collision = 1;
				break;
			}
		}
	}
	return collision;
};


int checkCollision_X(int current_y, int current_x, tetromino falling,int gridvar[][22], int move){
	int collision = 0;
	for(int i = 3; i > -1; i--){
		for(int j = 0; j < 4; j++){
			if((gridvar[current_y + j][current_x + 2*i + move] != 0) && falling.pixel[j][i]){
				collision = 1;
				break;
			}
		}
	}
	return collision;
}


int validateRotation(int current_y, int current_x, int rotation, tetromino falling){
	int validation = 0;
	rotation += 1;
	falling = rotate(rotation, falling);
	if(!(checkCollision(current_y, current_x,falling, gridvar)))
		validation = 1;
	return validation;
};


int hardDrop(int y, int x, tetromino falling, int gridvar[][22]){
	int drop = 0;
	for(int i = y; i < 22; i++){
		if(checkCollision(i, x, falling, gridvar)){
			drop = i;
			break;
		}
	}
	return drop;
};

int clearLine(int gridvar[][22], int *contador){
	int counter = 1, line_cleared, lines = 0;
	for(int i = 20; i > 0; i--){
		for(int j = 20; j > 0; j--){
			if(gridvar[i][j] == 0){
				counter = 1;
				break;
			}
			if(gridvar[i][j] > 1){
				counter++;
			}
			if(counter == 20){
				line_cleared = i;
				break;
			}
		}
		if(counter == 20){
			break;
		}
	}

	if(counter % 20 == 0){
		for(int i = line_cleared; i > 2; i--){
			for(int j = 20; j > 0; j--){
				gridvar[i][j] = gridvar[i-1][j]; 
			}
		}
		lines++;
		*contador = *contador + 1;
		napms(10);
	}
	while(lines != 0){
		lines = clearLine(gridvar, &*contador);
	}
	return lines;
};

int checkEnd(int gridvar[][22]){
	int end = 0;
	for(int i = 1;i < 21; i++){
		if(gridvar[1][i] > 1){
			end = 1;
			break;
		}
	}
	return end;
}

int runGame(){
	initGrid(gridvar);
	int end = 0;
	int level = 1;
	int score = 0;
	int contador = 0;
	double speed;
	gameborders();

	int choose_tet, next_tet = rand() % 5;
	//	int choose_tet, next_tet = 0;

	while(!end){
		end = checkEnd(gridvar);
		clearLine(gridvar, &contador);
		if(contador){
			score = score + 200 * contador;
			level = level + contador;
			contador = 0;
		}
		speed = 500 - 300 * ((double)level - 1) / (double)level;

		grid(gridvar);
		gameborders();
		refresh();

		choose_tet = next_tet;
		next_tet = rand() % 5;
		//		next_tet = 0;
		tetromino falling = chooseTet(choose_tet);
		tetromino prev_falling = falling;
		tetromino next_falling = chooseTet(next_tet);

		attron(A_BOLD | COLOR_PAIR(1));
		mvprintw(SZ_Y/2 - 9, SZ_X / 2 + 12, "SCORE");
		mvprintw(SZ_Y/2 - 8, SZ_X / 2 + 12, "     ");
		mvprintw(SZ_Y/2 - 8, SZ_X / 2 + 12, "%d", score);
		mvprintw(SZ_Y/2 - 6, SZ_X / 2 + 12, "LINES");
		mvprintw(SZ_Y/2 - 5, SZ_X / 2 + 12, "     ");
		mvprintw(SZ_Y/2 - 5, SZ_X / 2 + 12, "%d", level - 1);
		mvprintw(SZ_Y/2 - 3, SZ_X / 2 + 12, "NEXT");
		attroff(A_BOLD | COLOR_PAIR(1));

		attron(COLOR_PAIR(9));
		for(int i = 0; i < 5; i++)
			mvprintw(10 + i + RY, 22 + RX,"##########");
		attroff(COLOR_PAIR(9));

		printTetr(11 , 23, next_falling);

		int current_y = 1; 
		int current_x = 9; 
		int move;
		int rotation = 0;
		int prev_y = current_y;
		int prev_x = current_x;

		struct timespec t1, t2;

		while(1){
			printTetr(current_y, current_x, falling);

			double loop_timer = 1, elapsed = 0;
			while(loop_timer < speed){
				clock_gettime(CLOCK_MONOTONIC, &t1);
				prev_x = current_x;
				move = readInput();
				flushinp();
				napms(5);

				if(move == -1 || move == 1){
					if(!(checkCollision_X(current_y, current_x + move, falling, gridvar, move))){
						current_x += 2*move;
						delPrev(current_y, prev_x, falling);
						printTetr(current_y, current_x, falling);
						refresh();
					}
				}
				if(move == 2){
					prev_falling = falling;
					delPrev(current_y, current_x, prev_falling);
					current_y = hardDrop(current_y, current_x, falling, gridvar);
					printTetr(current_y, current_x, falling);
					refresh();
				}
				if(move == 3 && validateRotation(current_y, current_x, rotation, falling)){
					delPrev(current_y, prev_x, falling);
					rotation++;
					falling = rotate(rotation, falling);
					printTetr(current_y, current_x, falling);
					prev_falling = falling;
					refresh();
				}
				if(move == 4){
					goto kill;
				}
				clock_gettime(CLOCK_MONOTONIC, &t2);
				if(t1.tv_nsec > t2.tv_nsec){
					elapsed = elapsed + (1000000000 - (double)t1.tv_nsec + (double)t2.tv_nsec) / 1000000.0;
				}
				else{
					elapsed = elapsed + ((double)t2.tv_nsec - (double)t1.tv_nsec) / 1000000.0;
				}
				loop_timer = elapsed;
			}
			if(!checkCollision(current_y, current_x, falling, gridvar)){
				prev_y = current_y;
				current_y++;
				delPrev(prev_y, current_x, falling);
				printTetr(current_y, current_x, falling);
				refresh();
				napms(10);
			}
			else{
				saveGrid(current_y, current_x, falling, gridvar);
				break;
			}
			napms(5);
		}
		if((checkCollision(0,10, next_falling, gridvar))){
			end = 1;
		}
	}

kill:{
		 hiscore(score);
	 }

	 napms(25);
	 return end;
}
