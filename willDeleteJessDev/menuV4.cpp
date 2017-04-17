#include <iostream>
#include <ncurses.h>


#include "Menu.h"
using namespace std;

int main(int argc, char **argv){
	initscr(); 
//	noecho(); 
	cbreak(); //ncurses init stuff

	int yMax, xMax; 
	getmaxyx(stdscr, yMax, xMax); 


	
	WINDOW  *user; 
	WINDOW  *menu; 
//	homescreenSetup(user, menu); 
//	cout << "testing in main file" << endl; 
	homescreenSetup(user, menu, yMax, xMax); 
//	refresh(); 
	//box(user, 0, 0); 

	mvwprintw(user, 0, 0, "USER INFORMATION COMING SHORTLY...."); 

	refresh();
	wrefresh(user); 
	wrefresh(menu); 
//	refresh(); 
	getch(); 
	getch(); //ncurses end window stuff
	endwin(); 
	return 0; 	
}

/*
void print_menu(WINDOW *w, int h, int n, string s[],int d); 

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

	int choice;
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



void print_menu(WINDOW *w, int h, int n, string s[],int d){ 
	int x,y,i, min_depth, printRange, miniRange; 
	x=2;
	y=3; 
	min_depth = n + 4; //choices + header + box edges
	box(w, 0, 0); 
	mvwprintw(w, 1, 1, "PRESS ENTER TO SELECT AN OPTION BELOW:"); 
	mvwprintw(w, 2, 1, "--------------------------------------"); 

	if (d < min_depth)  printRange = d - 4;
	else printRange = d;    

	for (i=0; i< n; i++){
		if(h == i+1){ //highlighter = present choice
			wattron(w, A_REVERSE);
			mvwprintw(w, y, x, "%s", s[i].c_str());
			wattroff(w, A_REVERSE); 
		}   
		else mvwprintw(w, y, x, "%s", s[i].c_str()); 
		y++; 
	}   
	wrefresh(w); 
}

*/
