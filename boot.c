#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "boot.h"
#include "game.h"
#include "hiscore.h"

#define SZ_X getmaxx(stdscr)
#define SZ_Y getmaxy(stdscr)

void boot_sequence(){
	time_t TIMER;
	srand((unsigned) time(&TIMER));
	curs_set(0);
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(4, COLOR_GREEN, COLOR_GREEN);
	init_pair(5, COLOR_RED, COLOR_RED);
	init_pair(6, COLOR_CYAN, COLOR_CYAN);
	init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(8, COLOR_WHITE, COLOR_WHITE);
	init_pair(9, COLOR_BLACK, COLOR_BLACK); 
	init_pair(11, COLOR_WHITE, COLOR_BLUE);
	init_pair(12, COLOR_WHITE, COLOR_GREEN);
	init_pair(13, COLOR_WHITE, COLOR_YELLOW);
	init_pair(14, COLOR_WHITE, COLOR_CYAN);
	init_pair(15, COLOR_WHITE, COLOR_MAGENTA);
	nodelay(stdscr, TRUE);
	noecho();
	cbreak();
}

void borders(){
	int random = 2 + rand() % 7;
	attron(COLOR_PAIR(random));
	int aux = 0;
	move(0,0);
	int y = SZ_Y, x = SZ_X;
	while(aux++ < x)
		addch('#');
	for(int i = 1;i < y - 1;i++){
		mvprintw(i, 0, "##");
		mvprintw(i, x - 1, "##");
		/*mvaddch(i,0,'#');
		  mvaddch(i,1,'#');
		  mvaddch(i,x-1,'#');
		  mvaddch(i,x-2,'#');*/
	}
	aux = 0;
	while(aux++ < x)
		addch('#');
	attroff(COLOR_PAIR(random));
}

void gameborders(){
	attron(A_DIM | COLOR_PAIR(2) | A_ALTCHARSET);

	for(int i = 0 ; i < 35; i++){
		for(int j = 0; j < 23; j++){
			if(i == 0 || i > 21)
				mvprintw(SZ_Y / 2 - 11 + j, SZ_X / 2 - 12 + i, "%c%c", 110, 110);
			if(i > 0 && i < 21){
				if(j == 0 || j > 20){
					mvprintw(SZ_Y / 2 - 11 + j, SZ_X / 2 - 12 + i, "%c%c", 110, 110);
				}
			}
		}
	}

	attroff(A_DIM | COLOR_PAIR(2) | A_ALTCHARSET);
}

void logoprint(int function){
	if(function){
		int crand = rand() % 5 + 2;
		attron(A_ALTCHARSET);
		crand = rand() % 5 + 2;
		attron(COLOR_PAIR(crand));
		for(int i = 1;i < 6; i++){
			mvprintw(SZ_Y/2-10,SZ_X/2-19+i,"a");
			mvprintw(SZ_Y/2-11+i, SZ_X/2-16,"a");
		}
		refresh();
		napms(20);
		attroff(COLOR_PAIR(crand));

		crand = rand() % 5 + 2;
		attron(COLOR_PAIR(crand));
		for(int i = 1;i < 6; i++){
			mvprintw(SZ_Y/2-10,SZ_X/2-12+i,"a");
			mvprintw(SZ_Y/2-8,SZ_X/2-12+i,"a");
			mvprintw(SZ_Y/2-6,SZ_X/2-12+i,"a");
			mvprintw(SZ_Y/2-11+i, SZ_X/2-11,"a");
		}
		refresh();
		napms(20);
		attroff(COLOR_PAIR(crand));

		crand = rand() % 5 + 2;
		attron(COLOR_PAIR(crand));
		for(int i = 1;i < 6; i++){
			mvprintw(SZ_Y/2-10,SZ_X/2-5+i,"a");
			mvprintw(SZ_Y/2-11+i, SZ_X/2-2,"a");
		}
		refresh();
		napms(20);
		attroff(COLOR_PAIR(crand));

		crand = rand() % 5 + 2;
		attron(COLOR_PAIR(crand));
		mvprintw(SZ_Y/2-10, SZ_X/2 + 3, "aaaa");
		mvprintw(SZ_Y/2-9, SZ_X/2 + 3, "a");
		mvprintw(SZ_Y/2-9, SZ_X/2 + 7, "a");
		mvprintw(SZ_Y/2-8, SZ_X/2 + 3, "aaaa");
		mvprintw(SZ_Y/2-7, SZ_X/2 + 3, "a");
		mvprintw(SZ_Y/2-7, SZ_X/2 + 7, "a");
		mvprintw(SZ_Y/2-9, SZ_X/2 + 3, "a");
		mvprintw(SZ_Y/2-6, SZ_X/2 + 3, "a");
		mvprintw(SZ_Y/2-6, SZ_X/2 + 7, "a");
		refresh();
		napms(20);
		attroff(COLOR_PAIR(crand));

		crand = rand() % 5 + 2;
		attron(COLOR_PAIR(crand));
		for(int i = 1; i<6; i++){
			mvprintw(SZ_Y/2-10, SZ_X/2 + 9 + i, "a");
			mvprintw(SZ_Y/2-6, SZ_X/2 + 9 + i, "a");
			mvprintw(SZ_Y/2-11+i, SZ_X/2 + 12, "a");
		}
		refresh();
		napms(20);
		attroff(COLOR_PAIR(crand));

		crand = rand() % 5 + 2;
		attron(COLOR_PAIR(crand));
		mvprintw(SZ_Y/2-10, SZ_X/2 + 17, "aaaaa");
		mvprintw(SZ_Y/2-9, SZ_X/2 + 17, "a");
		mvprintw(SZ_Y/2-8, SZ_X/2 + 17, "aaaaa");
		mvprintw(SZ_Y/2-7, SZ_X/2 + 21, "a");
		mvprintw(SZ_Y/2-6, SZ_X/2 + 17, "aaaaa");
		refresh();
		napms(20);
		attroff(COLOR_PAIR(crand));

		attroff(A_ALTCHARSET);
	}

	if(!function){
		mvprintw(SZ_Y/2-10,SZ_X/2-18, "                                    ");
		mvprintw(SZ_Y/2-9,SZ_X/2-18, "                                    ");
		mvprintw(SZ_Y/2-8,SZ_X/2-18, "                                    ");
		mvprintw(SZ_Y/2-7,SZ_X/2-18,"                                    ");
		mvprintw(SZ_Y/2-6,SZ_X/2-18,"                                    ");
	}
}

int menu(){
	clear();
	int mselect = 0, counter = 4;
	int tmp_x  = SZ_X, tmp_y = SZ_Y;
	borders();

	while(mselect != 10){
		int y = SZ_Y;
		int x = SZ_X;
		if(tmp_x != x || tmp_y != y){
			tmp_x = x;
			tmp_y = y;
			erase();
			borders();
		}
		logoprint(1);
		attron(COLOR_PAIR(1));
		mvprintw(y/2-4,x/2-3,"JOGAR");
		mvprintw(y/2-2,x/2-3,"RECORDES");
		mvprintw(y/2,x/2-3,"INSTRUCOES");
		mvprintw(y/2+2,x/2-3,"CREDITOS");
		mvprintw(y/2+4,x/2-3,"SAIR");

		attroff(COLOR_PAIR(1));
		mvaddch(y/2 - counter - 2, x/2 - 5, ' '); 
		mvaddch(y/2 - counter + 2, x/2 - 5, ' ');
		attron(COLOR_PAIR(1));

		attron(A_BLINK);
		mvaddch(y/2 - counter, x/2 - 5, '>');
		attroff(A_BLINK);

		mselect = getch();
		flushinp();
		if((mselect == 's' || mselect == 'S') && counter > -4)
			counter -= 2;
		if((mselect == 'w' || mselect == 'A') && counter < 4)
			counter += 2;
		attroff(COLOR_PAIR(1));
		refresh();	
	}
	logoprint(0);
	return counter;
}

void instrucoes(){
	clear();
	borders();
	attron(COLOR_PAIR(1));
	mvprintw(SZ_Y/2-5,SZ_X/2-10,"COMANDOS: A - ESQUERDA     ");
	mvprintw(SZ_Y/2-4,SZ_X/2-10,"          D - DIREITA      ");
	mvprintw(SZ_Y/2-3,SZ_X/2-10,"          R - ROTACAO      ");
	mvprintw(SZ_Y/2-2,SZ_X/2-10,"          SPACE - HARD DROP");

	mvprintw(SZ_Y/2+1, SZ_X/2-10, "REGRAS: COMPLETE UMA LINHA PARA");
	mvprintw(SZ_Y/2+2, SZ_X/2-10, "LIMPA-LA E RECEBER 200 PONTOS. ");
	mvprintw(SZ_Y/2+3, SZ_X/2-10, "CASO CHEGUE NO TOPO: GAME OVER ");
	//	mvprintw(SZ_Y/2+2, SZ_X/2, "");
	//	mvprintw(SZ_Y/2+3, SZ_X/2, "");	
	attroff(COLOR_PAIR(1));	
	attron(A_BLINK);
	mvprintw(SZ_Y/2+8, SZ_X/2-10, "QUALQUER TECLA PARA CONTINUAR");
	attroff(A_BLINK);

	while(!kbhit()){
	};
	flushinp();
	refresh();
};

void creditos(){
	clear();
	borders();
	attron(COLOR_PAIR(1));
	mvprintw(SZ_Y/2-2,SZ_X/2-22,"FEITO POR: RAFAEL CARVALHO");
	mvprintw(SZ_Y/2-1, SZ_X/2-22, "N_USP: 14604271");
	mvprintw(SZ_Y/2, SZ_X/2-22, "COMPILADOR: gcc (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0");
	mvprintw(SZ_Y/2+1, SZ_X/2-22, "EDITOR DE TEXTO: NVIM v0.9.0");
	attroff(COLOR_PAIR(1));
	attron(A_BLINK);
	mvprintw(SZ_Y/2+8, SZ_X/2-15, "QUALQUER TECLA PARA CONTINUAR");
	attroff(A_BLINK);
	while(!kbhit()){
	};
	flushinp();
	refresh();
};

void recordes(){
	clear();
	mvprintw(5,5,"recordes");
	refresh();
	sortHiscore();
	printHiscore();
	borders();
	attron(A_BLINK);
	mvprintw(SZ_Y/2+8, SZ_X/2-15, "QUALQUER TECLA PARA CONTINUAR");
	attroff(A_BLINK);
	while(!kbhit()){
	};
	flushinp();
}
