#include<ncurses.h>
#include<string>

using namespace std;

int main(int argc, char ** argv){

	initscr();
	noecho();
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	WINDOW * userInfoWin = newwin(20, xMax-12,  0, 5); 
	box(userInfoWin, 0, 0); 
	WINDOW * menuwin = newwin(9, xMax-12, yMax-10, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);
	wrefresh(userInfoWin); 
	keypad(menuwin, true);

	string choices[5] = {"Post To Wall", "View Friend List", "Add Friend", "Edit Profile", "View Friend"};

	mvwprintw(userInfoWin, 2, 2, "USER INFORMATION COMING SHORTLY...."); 
	wrefresh(userInfoWin); 

	int choice;
	int highlight = 0;


	while(1){
		for(int i = 0; i < 5; i++){
			mvwprintw(menuwin, 1, 1, "SELECT AN OPTION BELOW:"); 
			mvwprintw(menuwin, 2, 1, "-----------------------"); 
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
		if(choice == 10){
			break;
		}
	}
	getch(); 	
	endwin();
	return 0; 
}
