#include <ncurses.h>
#include <stdlib.h>
#include "boot.h"
#include "game.h"

int main(){
	int option;

	while(1){
		boot_sequence();
		curs_set(0);
		option = menu();
		if(option == 4)
			runGame();
		if(option == 2)
			recordes();
		if(option == 0)
			instrucoes();
		if(option == -2)
			creditos();
		if(option == -4)
			break;
	}
	endwin();
	return 0;
}
