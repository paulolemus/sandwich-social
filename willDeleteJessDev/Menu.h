// intro stuff
//
#include <ncurses.h>
#include <iostream>

/*
want to have class that determines the depth and width 
	of the window we want 
	based on the xMax and yMax values of the current screen

want to have a setup for the window


*/


int depthCalc(int a, int b){
	return a*b; 
}




void homescreenSetup(WINDOW* wTop, WINDOW* wBottom, int y, int x){
//this function will set up two windows 
// --- both centered (same x beginning location and width)
// --- the top will be the workspace 
// -------- it will be larger than the bottom 
// -------- so they have different depths and y beginning locations
// --- the bottom will be just for the menu
	int topD, bottomD, tyBeg, byBeg, xBeg, width ; 

	topD = y *(.625); // 5/8 of the screen (1/8 for blank space)
	bottomD = y *(.25); //  1/4 = 2/8 of the screen
	tyBeg = 0; //top duh
	byBeg = topD +1; //starts where top leaves off + room
	xBeg = 5; 
	width = x - 10; //width of start screen is passed in and - 2X xbeg
	
	wTop = newwin(topD, width, tyBeg, xBeg); //start new window
	box(wTop, 0, 0);  //sets up the box in the visual screen

	wBottom = newwin(bottomD, width, byBeg, xBeg); 
	box(wBottom, 0, 0); 

	mvwprintw(wTop, 2,2, "user stuff");


	refresh(); // SUPER IMPORTANT: this must be first 
	wrefresh(wBottom);	
	wrefresh(wTop); //prints the window	return; 	
}


