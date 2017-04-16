#include<ncurses.h>
#include<string>

using namespace std;

int main(int argc, char ** argv){

	initscr();
	noecho();
	cbreak();

	int yMax, xMax, userXbeg, userYbeg,menuXbeg, menuYbeg, userDepth, menuDepth, userWidth, menuWidth;
	getmaxyx(stdscr, yMax, xMax);

	userDepth = yMax *(.625); // 5/8
	menuDepth = yMax *(.25);  // 1/4 = 2/8
	userWidth = xMax - 10; 
	menuWidth = xMax - 10; 
	userXbeg = 5; 
	menuXbeg = 5; 
	userYbeg = 0;  
	menuYbeg = userDepth+1;

	WINDOW * userInfoWin = newwin(userDepth, userWidth,  userYbeg, userXbeg); 
	box(userInfoWin, 0, 0); 
	WINDOW * menuwin = newwin(menuDepth, menuWidth, menuYbeg, menuXbeg);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);
	wrefresh(userInfoWin); 
	keypad(menuwin, true);

	string choices[5] = {"Post To Wall", "View Friend List", "Add Friend", "Edit Profile", "View Friend"};

	mvwprintw(userInfoWin, 2, 2, "USER INFORMATION COMING SHORTLY...."); 
	wrefresh(userInfoWin); 

	int choice, printRange;
	int highlight = 0;

	if(menuDepth < 9){ //the depth is less than the amt of choices
		printRange = menuDepth - 4;//-box(2)-heading(2) = -4
	}
	else{
		printRange = 5; 
	}
	while(1){
		for(int i = 0; i < printRange; i++){
			mvwprintw(menuwin, 1, 1, "SELECT AN OPTION BELOW:"); 
			mvwprintw(menuwin, 2, 1, "---------------%d------", printRange); 
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
	getch(); 	
	endwin();
	return 0; 
}
