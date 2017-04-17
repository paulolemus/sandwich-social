//intro stuff
//

#ifndef _MENU_H
#define _MENU_H

#include<ncurses.h>
#include<string>
using namespace std;



myMenus::myMenus(){
	yMax = xMax = Depth = Width = 10;
	yBeg = xBeg = 0; 
	Fraction = 1; 
}


void myMenus::setyBeg(int a, int b){
	yBeg = a + b; // top window (both inputs =0), other (depth + difference)
}

void myMenus::setxBeg(int a, int b){
	xBeg = a + b; // all in line (0, constant), other (width + difference)
}

void myMenus::setDepth(int a, int b){
	Depth = a*b; //a usually = yMax, b usually = fraction 
}

void myMenus::setWidth(int a, int b){
	Width = a - b; // a usually = xMax
}

void myMenus::setFraction(int a){
	Fraction = a;
}

void myMenus::setmenuTemplate(){
	menuTemplate = newwin(Depth, Width, yBeg, xBeg); 
}




void myMenus::print_menu(WINDOW *w, int h, int n, string s[],int d){
	int x,y,i, min_depth, printRange, miniRange; 
	x=2;
	y=3; 
	min_depth = n + 4; //choices + header + box edges
	box(w, 0, 0);
	mvwprintw(w, 1, 1, "PRESS ENTER TO SELECT AN OPTION BELOW:"); 
	mvwprintw(w, 2, 1, "--------------------------------------"); 

	if (d < min_depth)	printRange = d - 4;
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


#endif // _MENU_H
