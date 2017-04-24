/*
 *
 *
 */

/*
 *
 *
 *
 */

#ifndef SANDWICH_GUI_H_
#define SANDWICH_GUI_H_

#include <ncurses.h>
#include <unordered_map>
#include "User.h"
#include "Trie.h"
#include <vector>
#include <string>
namespace sandwich {

class GUI {

    std::unordered_map<std::string, sandwich::User*>& userMap;
    sandwich::Trie<sandwich::User*>&                  trie;
    sandwich::User*&                                  currUser;

public:
    enum class Type : int {
        HOME,
        POST_TO_WALL,
        VIEW_FRIENDS,
        ADD_FRIEND,
        VIEW_FRIEND,
        REMOVE_FRIEND,
        EDIT_PROFILE,
        LOGOUT,
        QUIT
    };

    GUI(std::unordered_map<std::string, sandwich::User*>& userMap,
        sandwich::Trie<sandwich::User*>&                  trie,
        sandwich::User*&                                  currUser);

    
    Type loginScreen();
    Type homeScreen();

    void postWallScreen();
    void viewFriendsScreen();
    void addFriendScreen();
    void viewFriendScreen();
    void editProfileScreen();
    void removeFriendScreen();

    void testFunc();
};

GUI::GUI(std::unordered_map<std::string, sandwich::User*>& userMap,
         sandwich::Trie<sandwich::User*>&                  trie,
         sandwich::User*&                                  currUser) :
    userMap(userMap),
    trie(trie),
    currUser(currUser)
    { //initializes the window    
    	initscr(); 
	noecho();
	cbreak(); 
    }

GUI::Type GUI::loginScreen() {
	std::string username = "jack";
	sandwich::User* tester = new sandwich::User(); 
	tester->setUsername(username);
	
	//sandwich::User * tester = new sandwich::User("jack", "jackDaniels", "is Lit"); 
	trie.store(username, tester); 

	int y,x; 
	getmaxyx(stdscr, y, x); 
	WINDOW *b = newwin(y, x-10, 0, 5);
	box(b,0,0);
	refresh(); 
	wrefresh(b); 

	WINDOW *w = newwin(y-4, x-14, 2, 7); 
	mvwprintw(w,(y-4)/2, (x-14)/2, "type in your username\n"); 
	//refresh(); 
	wrefresh(w); 
	//int c = wgetch(w);
	char s=wgetch(w);
       	std::string temp; 	
	std::vector<char> v; 
	while(s!=10){
	        mvwprintw(w,14,14,"%c", s); 
		wrefresh(w); 	       
		temp+=s; 
		s = wgetch(w); 
	}	
	mvwprintw(w, 14, 14, "%s",temp.c_str()); 
	wrefresh(w); 
	refresh(); 	
	if(trie.search(temp)){
		
		std::cout << "\n\nfound " << temp << "\n\n"; 
	}
	else std::cout << "\n\ndidn't find " << temp << "\n\n";  


	int a = getch(); 
}
GUI::Type GUI::homeScreen() {
	return sandwich::GUI::Type::LOGOUT;
}

void GUI::postWallScreen() {

}
void GUI::viewFriendsScreen() {

}
void GUI::addFriendScreen() {

}
void GUI::viewFriendScreen() {

}
void GUI::editProfileScreen() {

}
void GUI::removeFriendScreen() {

}

void GUI::testFunc() {

    std::string username = "Test username";
    currUser = new User();
    currUser->setUsername(username);

    trie.store(currUser->getUsername(), currUser);
    userMap[currUser->getLower()] = currUser;
}


} // namespace sandwich

#endif // SANDWICH_GUI_H_
