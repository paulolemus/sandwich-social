#include<ncurses.h>
#include<string>

using namespace std;

int main(int argc, char ** argv){

	initscr();
	noecho();
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW * menuwin = newwin(7, xMax-12, yMax-8, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	keypad(menuwin, true);

	string choices[5] = {"Post To Wall", "View Friend List", "Add Friend", "Edit Profile", "View Friend"};

	int choice;
	int highlight = 0;

	while(1){
		for(int i = 0; i < 5; i++){
			if(i == highlight){
				wattron(menuwin, A_REVERSE);
				mvwprintw(menuwin, i+1, 1, choices[i].c_str());
				wattroff(menuwin, A_REVERSE);
			}
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
	printw("Your choice was: %s", choices[highlight].c_str());
	endwin();
	}

}
