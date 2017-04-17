#include "Menu.h"
using namespace std;
void print_menu(WINDOW *menu_win, int highLighter, int num_choices, string c[]);

int main(int argc, char ** argv){

	initscr();
	noecho();
	cbreak();

	int yMax, xMax, userXbeg, userYbeg,menuXbeg, menuYbeg, userDepth, menuDepth, userWidth, menuWidth;
	getmaxyx(stdscr, yMax, xMax); //get max sizes of the full window

	userDepth = yMax *(.625); // 5/8
	menuDepth = yMax *(.25);  // 1/4 = 2/8
	userWidth = menuWidth = xMax - 10; 
	userXbeg = menuXbeg = 5; 
	userYbeg = 0;  
	menuYbeg = userDepth+1;
	
	//start out the window pointers and their boxes (classic style)
	WINDOW * userInfoWin = newwin(userDepth, userWidth,  userYbeg, userXbeg); 
	box(userInfoWin, 0, 0); 
	WINDOW * menuwin = newwin(menuDepth, menuWidth, menuYbeg, menuXbeg);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);
	wrefresh(userInfoWin); 
	keypad(menuwin, true);

	string choices[5] = {"Post To Wall", "View Friend List", "Add Friend", "Edit Profile", "View Friend"};
	int n_choices = sizeof(choices)/sizeof(string); 
	
	mvwprintw(userInfoWin, 2, 2, "USER INFORMATION COMING SHORTLY...."); 
	wrefresh(userInfoWin); 

	int choice, printRange;
	int highlight = 1;

	print_menu(menuwin, highlight, n_choices, choices, menuDepth);
	while(1){
		int c = wgetch(menuwin); 
		switch(c){
			case KEY_UP:
				if(highlight ==1) highlight = n_choices; 
				else highlight --; 
				break; 
			case KEY_DOWN: 
				if(highlight == n_choices) highlight = 1; 	
				else highlight ++; 
				break; 
			case 10: // 10 = int for enter
				choice = highlight; 
				break; 
			default:
				mvwprintw(stdscr, yMax-1, menuXbeg, "Press enter to select");
				refresh(); 
				break; 
		}
		print_menu(menuwin, highlight, n_choices, choices, menuDepth); 
		if(choice!=0)break; //user make a choice, break loop
	}

	mvwprintw(stdscr, yMax-1, menuXbeg, "You chose item  %d with choice string %s", choice, choices[choice-1].c_str());
	clrtoeol(); // don't know what this does (clear to end of line maybe?)
	refresh();
       	getch(); 	
	endwin(); 
	return 0;
}




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
