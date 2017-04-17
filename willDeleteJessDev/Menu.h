//intro stuff
//

#ifndef _MENU_H
#define _MENU_H

#include<ncurses.h>
#include<string>
using namespace std;

void print_menu(WINDOW *menu_win, int highLighter, int num_choices, string c[],int menuD){
	int x,y,i, min_depth, printRange; 
	x=2;
	y=3; 
	min_depth = num_choices + 4; //choices + header + box edges
	box(menu_win, 0, 0);
	mvwprintw(menu_win, 1, 1, "PRESS ENTER TO SELECT AN OPTION BELOW:"); 
	mvwprintw(menu_win, 2, 1, "--------------------------------------"); 

	if (menuD < min_depth)	printRange = menuD - 4;
	else printRange = menuD; 	
	for (i=0; i< num_choices; i++){
		
		if(highLighter == i+1){ //highlighter = present choice
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", c[i].c_str());
		        wattroff(menu_win, A_REVERSE); 
		}
		else mvwprintw(menu_win, y, x, "%s", c[i].c_str()); 
		y++; 
	}
	wrefresh(menu_win); 
}	


#endif // _MENU_H

/*
		for(int i = 0; i < printRange; i++){
			mvwprintw(menuwin, 1, 1, "PRESS ENTER TO SELECT AN OPTION BELOW:"); 
			mvwprintw(menuwin, 2, 1, "--------------------------------------"); 
			if(i == highlight){
				wattron(menuwin, A_REVERSE);
			}	
				mvwprintw(menuwin, i+3, 1, choices[i].c_str());
				wattroff(menuwin, A_REVERSE);
			}
		choice = wgetch(menuwin);

		switch(choice){
			case KEY_UP:
				highlight--;
				if(highlight == -1){
				highlight = 0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 5){
					highlight = 4;
				}
				break;
			default:
				break;
		
		
		}
		if(choice == 10){ //not sure what this does
			break;
		}
	}
*/
