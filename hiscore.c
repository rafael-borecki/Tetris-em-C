#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "boot.h"
#include "game.h"
#include "hiscore.h"

#define SZ_Y getmaxy(stdscr)
#define SZ_X getmaxx(stdscr)

void hiscore(int score){
	nodelay(stdscr, FALSE);
	curs_set(1);
	echo();
	clear();
	mvprintw(SZ_Y/2 - 1,SZ_X/2,"DIGITE SUAS INICIAIS:");
	refresh();
	char player[5];
	mvgetnstr(SZ_Y/2, SZ_X/2, player, 3);
	
	FILE *hiscore;
	hiscore = fopen("hiscore.txt", "a+");
	if(hiscore != NULL){
		rewind(hiscore);	
		fprintf(hiscore, "%s   ", player);
		fprintf(hiscore, "%d\n", score);
	}
	fclose(hiscore);
	curs_set(0);
	noecho();
	nodelay(stdscr, TRUE); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void sortHiscore(){
	FILE *hiscore;
	FILE *sorths;
	hiscore = fopen("hiscore.txt", "r");
	sorths = fopen("sorths.txt", "w");
	rewind(hiscore);
	rewind(sorths);
	//int tempscore[50] = {0};
	int *tempscore;
	int counter = 0;
//	char tempname[50][5];
	char **tempname;
	if(hiscore == NULL){
		mvprintw(SZ_Y/2-5, SZ_X/2-10, "ERRO NA LEITURA DE HISCORE.TXT");
		refresh();
		napms(1000);
		exit(1);
	}
	if(hiscore != NULL){
		while(!feof(hiscore)){
			if(fgetc(hiscore) == '\n')
				counter++;
				}
		mvprintw(5,5,"%d", counter);
		refresh();
		tempscore = malloc((counter + 10)*sizeof(int));
		tempname = malloc((counter + 10) * sizeof(char*));
		for(int i = 0; i < counter; i++)
			tempname[i] = malloc((5)*sizeof(char));

		rewind(hiscore);
		int index = 0;
		while(!feof(hiscore)){
			fscanf(hiscore, "%s", tempname[index]);
			fscanf(hiscore, "%d", &tempscore[index]);
			index++;
		}
	}
	int aux;
	char auxs[5];
	for(int i = 1; i < counter; i++){
		for(int i = 1; i < counter; i++){
			if(tempscore[i] > tempscore[i-1]){
				aux = tempscore[i-1];
				tempscore[i-1] = tempscore[i];
				tempscore[i] = aux;
				strcpy(auxs,tempname[i-1]);
				strcpy(tempname[i-1],tempname[i]);
				strcpy(tempname[i], auxs);
			}
		}
	}
	for(int i = 0; i < counter - 1; i++){
		fprintf(sorths,"%s    ", tempname[i]);
		fprintf(sorths, "%d\n", tempscore[i]);
	}

	for(int i = 0; i < counter; i++)
		free(tempname[i]);
	free(tempscore);
	fclose(hiscore);
	fclose(sorths);
}

void printHiscore(){
	clear();
	FILE *hiscore;
	hiscore = fopen("sorths.txt", "r+");
	rewind(hiscore);
	if(hiscore == NULL){
		mvprintw(SZ_Y/2-5, SZ_X/2-10, "ERRO NA LEITURA DE HISCORE.TXT");
		refresh();
		napms(1000);
		exit(1);
	}
	if(hiscore != NULL){
		char temp_string[30];
		int counter = 0;
		while(!feof(hiscore)){
			counter++;
			if(counter == 14)
				break;
			fgets(temp_string, 20, hiscore);
			attron(COLOR_PAIR(1));
			mvprintw(SZ_Y/2-10+counter, SZ_X/2-6, temp_string);
			attroff(COLOR_PAIR(1));
		}
		refresh();
	}
	fclose(hiscore);
}

