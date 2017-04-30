#include <iostream>
#include <ncurses.h>
#include "../Post.h"
#include "MenuV1.h"
using namespace std;
void print_menu(WINDOW *w, int h, int n, string s[],int d); 
int menu_selector(int n, int c, int* highlight, int a, int b);
string submit_selection(WINDOW* w, int choice);
int menu_setup(WINDOW* w, int n, string s[], int d); 
std::string userInput (WINDOW* w, int max);


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
	WINDOW * userInfoWin_BOX =  newwin(userDepth+4, userWidth+4,  userYbeg-2, userXbeg-2); 
	WINDOW * userInfoWin = newwin(userDepth, userWidth,  userYbeg, userXbeg);
        box(userInfoWin_BOX, 0, 0); 	
	wrefresh(userInfoWin_BOX); 

	box(userInfoWin, 0, 0); 
	WINDOW * menuwin = newwin(menuDepth, menuWidth, menuYbeg, menuXbeg);
	box(menuwin, 0,0);
	refresh();
	wrefresh(userInfoWin_BOX); 
	wrefresh(menuwin);
	wrefresh(userInfoWin); 
	keypad(menuwin, true);

	string choices[7] = {"Post To Wall", "View Friend List", "Add Friend", "Edit Profile", "View Friend", "Delete Friend", "Log Out"};
	int n_choices = sizeof(choices)/sizeof(string); 
	
	mvwprintw(userInfoWin, 2, 2, "USER INFORMATION COMING SHORTLY...."); 
	wrefresh(userInfoWin_BOX); 
	wrefresh(userInfoWin); 

	//print_menu(menuwin, highlight, n_choices, choices, menuDepth);

	int choice = menu_setup(menuwin, n_choices, choices, menuDepth); 
	/*
	int choice;
	int highlight = 1;

	print_menu(menuwin, highlight, n_choices, choices, menuDepth);
	while(1){
		int c = wgetch(menuwin); 
		choice = menu_selector(n_choices, c, &highlight, yMax-1, menuXbeg); 
		print_menu(menuwin, highlight, n_choices, choices, menuDepth); 
		if(choice!=0)break; //user make a choice, break loop
	}
	*/
	//mvwprintw(menuwin, 0,0, "debugging");
	
	wrefresh(menuwin);
	mvwprintw(stdscr, yMax-1, menuXbeg, "You chose item  %d with choice string %s", choice, choices[choice-1].c_str());

	string s1 =submit_selection(userInfoWin, choice);
	sandwich::Post post(s1);
	string t = post.getTime(); 
	string m = post.getMsg(); 
	mvwprintw(userInfoWin, 12, 2, "Post info: ");
       	mvwprintw(userInfoWin, 13, 2, "%s -- %s", t.c_str(), m.c_str()); 	
	wrefresh(userInfoWin_BOX); 
	wrefresh(userInfoWin); 
	clrtoeol(); // don't know what this does (clear to end of line maybe?)
	refresh();
       	getch(); 
	getch();
	getch(); 	
	endwin(); 
	return 0;
}


string submit_selection(WINDOW* w, int choice){
	int cMax=80; 
	char str[cMax];
	char s; 
	int y, x, c; 
//	string s1(std);
        string response; 	
//	sandwich::Post post(s1); ;

	switch(choice){
		case 1:
		       	wclear(w); 
			//box(w, 0, 0); 
			mvwprintw(w, 2,2, "NEW POST: ");
			mvwprintw(w, 3,2, "Tell us about your favorite Sandwhich... ");
			c=0; 
			response = userInput(w, 50); 
			wrefresh(w);	
			mvwprintw(w, 8,2, "You said:  ");
			mvwprintw(w, 9,2," %s", response.c_str());
			wrefresh(w);
			break; 
		case 2: 
		       	wclear(w); 
			box(w, 0, 0); 
			mvwprintw(w, 2,2, "VIEW FRIEND LIST ");
			mvwprintw(w, 3,2, "Your List of Friends: ");
			wrefresh(w); 
			break; 
		case 3: 
		       	wclear(w); 
			box(w, 0, 0); 
			mvwprintw(w, 2,2, "ADD FRIEND: ");
			mvwprintw(w, 3,2, "Suggested Friends to Add: ");
			wrefresh(w); 
			break; 
		case 4: 
		       	wclear(w); 
			box(w, 0, 0); 
			mvwprintw(w, 2,2, "EDIT PROFILE: ");
			mvwprintw(w, 3,2, "Choose a section to edit: ");
			wrefresh(w); 
			break; 
		case 5: 
		       	wclear(w); 
			box(w, 0, 0); 
			mvwprintw(w, 2,2, "VIEW A FRIEND: ");	
			mvwprintw(w, 3,2, "Select a friend to view: ");
			wrefresh(w); 
			break; 
		
		case 6: 
		       	wclear(w); 
			box(w, 0, 0); 
			mvwprintw(w, 2,2, "DELETE A FRIEND: ");	
			mvwprintw(w, 3,2, "Select a friend to DELETE: ");
			wrefresh(w); 
			break; 
		
		case 7: 
		       	wclear(w); 
			box(w, 0, 0); 
			mvwprintw(w, 2,2, "Are you sure you want to leave Sandwich Social?: ");	
			mvwprintw(w, 3,2, "YES or NO?: ");
			wrefresh(w); 
			break; 
		
		
		
		default: 
			mvwprintw(w, 8,8, "Press enter to select");
			wrefresh(w); 
			break; 
	}
	//string temp(str); 
	return response; 
}

int menu_selector(int n, int c, int* highlight, int a, int b){
	int choice= 0; 
	int n_choices = n; 
	switch(c){
		case KEY_UP:
			if(*highlight ==1) *highlight = n_choices; 
			else (*highlight) --; 
			break; 
		case KEY_DOWN: 
			if(*highlight == n_choices) *highlight = 1; 	
			else (*highlight) ++; 
			break; 
		case 10: // 10 = int for enter
			choice =* highlight; 
			return choice; 
		default:
			mvwprintw(stdscr, a, b,  "Press enter to select");
			refresh(); 
			break; 
	}
	return 0; 
}

		


std::string userInput (WINDOW* w, int max){
	char str[max];
	char s; 
	int y, x, c; 
	while(s!=10 && c<max){
		s =wgetch(w);
		getyx(w, y, x); 
		while(s == 127){
			s= ' ';
			x --;
			c--;   
			mvwprintw(w, y, x, "%c",s);
			wmove(w,y,x); 
			refresh(); 
			s=wgetch(w);
		}
		mvwprintw(w, y, x, "%c", s);
		if(c==max-1){
			mvwprintw(w,y+2, 2, "Characters are full, Max = %d",max); 
		}
		else str[c]=s;
		refresh(); 
		c++; 
		wrefresh(w);
	}	
	if (s == 10 || c ==max){
		str[c]='*'; 
	}
	string temp = string (str); 
	return temp;
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

int menu_setup(WINDOW* w, int n, string s[], int d){ 
	int choice;
	int h = 1;
	int y, x; 
	getmaxyx(stdscr, y, x); 
	print_menu(w, h, n, s, d); 
	//print_menu(menuwin, highlight, n_choices, choices, menuDepth);
	while(1){
		int c = wgetch(w); 
		//choice = menu_selector(n_choices, c, &highlight, yMax-1, menuXbeg); 
		choice = menu_selector(n, c, &h, y-1, 5);  
		print_menu(w, h, n, s, d); 
		//print_menu(menuwin, highlight, n_choices, choices, menuDepth); 
		if(choice!=0)break; //user make a choice, break loop
	}
	return choice; 
}
