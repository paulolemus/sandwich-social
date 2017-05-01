/* File: GUI.h
 * Name: Jessica Grazziotin & Paulo Lemus
 * Team: Sandwich
 * Date: 4/23/2017
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

    ~GUI(); 
    Type loginScreen();
    Type homeScreen();

    void postWallScreen();
    void viewFriendsScreen();
    void addFriendScreen();
    void viewFriendScreen();
    void editProfileScreen();
    void removeFriendScreen();
    void logoutScreen(); 

    void testFunc();
    void centerText(WINDOW *w, int yLoc, std::string text); //centers text in the input window
    int centerY(WINDOW *w); //returns the center y location of the window
    int centerX(WINDOW *w);  //returns the center x location of the window

    sandwich::User*& getCurrentUser(); 

    std::string payload(WINDOW* w, char s);
    void print_menu(WINDOW *w, int h, int n, std::string s[],int d); 
    int menu_selector(int n, int c, int* highlight, int a, int b);
    int menu_setup(WINDOW* w, int d); 
    std::string userInput (WINDOW* w, int max);
    Type submit_selection(WINDOW* w, int choice);

};

sandwich::User*& GUI::getCurrentUser(){
	return currUser;
}

GUI::GUI(std::unordered_map<std::string, sandwich::User*>& userMap,
        sandwich::Trie<sandwich::User*>&                  trie,
        sandwich::User*&                                  currUser) :
    userMap(userMap),
    trie(trie),
    currUser(currUser)
{ //initializes the window, noecho, and cbreak at construction    
    initscr(); 
    noecho();
    cbreak();
    start_color(); //makes colors availiable for the GUI
    init_pair(1,COLOR_BLACK,COLOR_CYAN);// black letters with Cyan background
    init_pair(2,COLOR_RED,COLOR_WHITE); //red letters with white background
}

GUI::~GUI() {
    endwin();// ends the window at destruction
}

GUI::Type GUI::loginScreen() {
 
    //create a start user for testing
    std::string username = "jack";
    sandwich::User* tester = new sandwich::User(username, "name", "bio"); 
    //create insert the username into the Map paired with the tester
    userMap.insert({tester->getLower(), tester});
    //store the user in the trie by its user name
    trie.store(tester->getLower(), tester); 

    int y,x; 
    getmaxyx(stdscr, y, x); //returns the max x & y values of the screen  

    WINDOW *mainWindow = newwin(y-4, x-14, 2, 7); 
    WINDOW *inputWindow = newwin(1, 30, centerY(mainWindow)+6, centerX(mainWindow)-7); 
    WINDOW *outerBox = newwin(y, x-10, 0, 5);
    box(outerBox,0,0);
    refresh(); 
    wrefresh(mainWindow); 
    wrefresh(outerBox);
    wrefresh(inputWindow); 
	
    wcolor_set (inputWindow,2, NULL); 	
    wbkgd(inputWindow,COLOR_PAIR(1)); 
    wmove(inputWindow, 0,0); 
    centerText(mainWindow, (y-4)*.25, "WELCOME TO SANDWICH SOCIAL"); 
    centerText(mainWindow, (y-4)*.5, "Input your username to login or start a new account"); 	
    refresh();  
    wrefresh(mainWindow); 
    wrefresh(outerBox); 
    wrefresh(inputWindow);
    wmove(inputWindow,0,0);
    
    std::string loginName = userInput(inputWindow, 28); 
    wrefresh(mainWindow); 
    refresh();

    if(trie.search(loginName)){

        for(unsigned int i = 0; i < loginName.size(); ++i) {
            if(loginName[i] >= 'A' && loginName[i] <= 'Z') loginName[i] = loginName[i] + 32;
        }
        currUser = userMap[loginName];
        return sandwich::GUI::Type::HOME;
    }
    else{
        werase(mainWindow);
        std::string newusrIntro = "Thanks for joining Sandwich Social ";

        if(sandwich::User::validateStr(loginName)){ 
            //std::cout << "validated";
        }
        newusrIntro += loginName;
        centerText(mainWindow, (y-4)*.25, newusrIntro); 
        centerText(mainWindow, ((y-4)*.25)+1, "Input your information below: "); 	

	mvwprintw(mainWindow, centerY(mainWindow)+2, centerX(mainWindow)-20, "Name: ");
 	WINDOW *nameWindow = newwin(1, 30, centerY(mainWindow)+4, centerX(mainWindow)-7);
        wbkgd(nameWindow, COLOR_PAIR(1)); 

	centerText(mainWindow, (y-4)*.75, "Short Bio (Max 150 characters): ");
        WINDOW *bioWindow = newwin(4, 50, ((y-4)*.75)+6, centerX(mainWindow)-15); 
        wbkgd(bioWindow, COLOR_PAIR(1)); 
        wrefresh(mainWindow); 
        wrefresh(nameWindow);
        wrefresh(bioWindow);

	wmove(nameWindow, 0,0);
        wrefresh(nameWindow); 
        std::string nameString= userInput(nameWindow, 28); 
        wrefresh(nameWindow); 
        //set name
        wrefresh(mainWindow); 
        wrefresh(nameWindow); 
        wmove(bioWindow, 0,0); 
        wrefresh(bioWindow); 
        std::string bioString = userInput(bioWindow, 100);
        //set bio

        if(sandwich::User::validateStr(loginName)    && 
                sandwich::User::validateStr(nameString) && 
                sandwich::User::validateStr(bioString)){ 

            erase();
            refresh(); 

            currUser = new sandwich::User(loginName, nameString, bioString);
            userMap[currUser->getLower()] = currUser;
            trie.store(currUser->getUsername(), currUser);
            trie.store(currUser->getName(), currUser);

            getch(); 
        }

        refresh();
        getch(); 

        return sandwich::GUI::Type::HOME; 	
    }	


    int a = getch(); 
}

    

/* The home screen contains two parts, the feed
 * and the menu. The menu consists of the following options:
 * 1. Post to Wall
 * 2. View Friends
 * 3. Add Friend
 * 4. View Friend
 * 5. Edit Profile
 * 6. Remove Friend
 * 7. Logout
 */
GUI::Type GUI::homeScreen() {
    erase(); 
    refresh(); 
    int x, y; 
    getmaxyx(stdscr, y, x); 
    //top and bottom windows based on the get max returns
    WINDOW * topDisplay = newwin((y*.625)-4, x-14, 2, 7); 
    WINDOW * bottomMenuDisplay = newwin(y*.25, x-10, (y*.625)+3, 5); 
    //box for the top window
    WINDOW * topBox = newwin((y*.625), x-10,0, 5); 
    //create boxes for the box windows
    box(topBox, 0,0); 
    box(bottomMenuDisplay, 0,0); 
    //setup keypad and refresh all windows
    keypad(bottomMenuDisplay, true); 
    
    sandwich::User*& cUser = getCurrentUser(); 
    centerText(topDisplay, 3, "Welcome to your Homescreen");
    //std::string nAAAme = cUser->getUsername(); 
    //mvwprintw(topDisplay,((y-4)*.25)+7,2, "%s ",nAAAme.c_str() ); 
   
    wrefresh(topBox); 
    wrefresh(bottomMenuDisplay); 
    wrefresh(topDisplay); 
    refresh();  
    int choice = menu_setup(bottomMenuDisplay, y*.25);
    //std::cout << cUser->getName()<< "\n"; 
    //int s = getch(); 	
    //return sandwich::GUI::Type::LOGOUT;
    return submit_selection(bottomMenuDisplay, choice); 
}


/* Post to wall screen allows user to write a text post
 * with a cap of 100 characters. This post will appear on
 * the user's feed, as well as all of his/her friend's feeds.
 */
void GUI::postWallScreen() {
    erase(); 
    refresh(); 
    int x, y; 
    getmaxyx(stdscr, y, x); 
    //top and bottom windows based on the get max returns
    WINDOW * topDisplay = newwin((y*.625)-4, x-14, 2, 7); 
    WINDOW * bottomMenuDisplay = newwin(y*.25, x-10, (y*.625)+3, 5); 
    //box for the top window
    WINDOW * topBox = newwin((y*.625), x-10,0, 5); 
    //create boxes for the box windows
    box(topBox, 0,0); 
    box(bottomMenuDisplay, 0,0); 
    //setup keypad and refresh all windows
    keypad(bottomMenuDisplay, true); 

    centerText(topDisplay, 3, "Write your new post (Max characters: 100):");
    WINDOW *postWin = newwin(4, 50, (y-4)*.25, centerX(topDisplay)-15); 
    wbkgd(postWin, COLOR_PAIR(1)); 

    wrefresh(topBox);
    wrefresh(topDisplay);
    wrefresh(bottomMenuDisplay); 
    wrefresh(postWin); 
    refresh();
    int choice = menu_setup(bottomMenuDisplay, y*.25);
    
    std::string postInput = userInput(postWin, 100); 
    sandwich::Post post(postInput); 
    std::string t = post.getTime();
    std::string m = post.getMsg(); 
    mvwprintw(topDisplay,((y-4)*.25)+6,2, "You Posted: ");
    mvwprintw(topDisplay,((y-4)*.25)+7,2, "%s ---- %s", t.c_str(), m.c_str()); 
    wrefresh(topBox);
    wrefresh(topDisplay);
    refresh();
    getch();
    getch();
}

/* view friends screen lets the user view all of his/her
 * friends names and usernames
 */
void GUI::viewFriendsScreen() {

    // Code for viewing list of friends
    //
    // auto friendList = currUser->getFriends();
    // if(friendList.size() < 1) {
    //      display "You have no friends"
    // }
    // for(auto friendPtr : friendList) {
    //      display friendPtr->getUsername().c_str()
    //      display friendPtr->getName().c_str()
    //      display friendPtr->getBio().c_str()
    //      draw line to deparate users
    // }
    erase(); 
    refresh(); 
    int x, y; 
    getmaxyx(stdscr, y, x); 
    //top and bottom windows based on the get max returns
    WINDOW * topDisplay = newwin((y*.625)-4, x-14, 2, 7); 
    WINDOW * bottomMenuDisplay = newwin(y*.25, x-10, (y*.625)+3, 5); 
    //box for the top window
    WINDOW * topBox = newwin((y*.625), x-10,0, 5); 
    //create boxes for the box windows
    box(topBox, 0,0); 
    box(bottomMenuDisplay, 0,0); 
    //setup keypad and refresh all windows
    keypad(bottomMenuDisplay, true); 
    wrefresh(topBox); 
    wrefresh(bottomMenuDisplay); 
    refresh(); 
    wrefresh(topDisplay); 
    int choice = menu_setup(bottomMenuDisplay, y*.25);

    centerText(topDisplay, (y-4)*.25, "View Friend List");
    wrefresh(topBox);
    wrefresh(topDisplay);
    refresh();

  //  std::string name = currUser->getUsername(); 
   // auto friendList = currUser->getFriends(); 
  
//	    mvwprintw(topDisplay,((y-4)*.25)+7,2, "%s ", name.c_str()); 
//	    centerText(topDisplay, ((y-4)*.25)+3, "Sorry you have no friends");
    


    wrefresh(topBox);
    wrefresh(topDisplay);
    refresh();

    getch();
    getch();



}

/* Add friend screen allows the user to search through friends
 * and add them based on username. It will reactively display 
 * all the possible friends that match the string the user is typing.
 */
void GUI::addFriendScreen() {

    // Code for searching for friends:
    // Note: Put this in a loop so that every time the user 
    // enters or deletes a character, the following code can be ran
    // and all the possible friends can be displayed.
    //
    // std::string prefix; // This is the string you update
    // auto friendList = trie.getComplete(prefix);
    // if(friendList.size() < 1) {
    //      display "No matching users. Please broaden your search"
    // }
    //          // clear the currently displayed friends here
    // for(auto friendPtr : friendList) {
    //      display friendPtr->getUsername().c_str()
    //      display friendPtr->getName().c_str()
    //      display friendPtr->getBio().c_str()
    //      draw line to deparate users
    // }
    //
    erase(); 
    refresh(); 
    int x, y; 
    getmaxyx(stdscr, y, x); 
    //top and bottom windows based on the get max returns
    WINDOW * topDisplay = newwin((y*.625)-4, x-14, 2, 7); 
    WINDOW * bottomMenuDisplay = newwin(y*.25, x-10, (y*.625)+3, 5); 
    //box for the top window
    WINDOW * topBox = newwin((y*.625), x-10,0, 5); 
    //create boxes for the box windows
    box(topBox, 0,0); 
    box(bottomMenuDisplay, 0,0); 
    //setup keypad and refresh all windows
    keypad(bottomMenuDisplay, true); 
    wrefresh(topBox); 
    wrefresh(bottomMenuDisplay); 
    refresh(); 
    wrefresh(topDisplay); 
    int choice = menu_setup(bottomMenuDisplay, y*.25);

    centerText(topDisplay, (y-4)*.25, "List of Friends to add");
    wrefresh(topBox);
    wrefresh(topDisplay);
    refresh();
    getch();
    getch();

}

/* View friend screen allows you to view a particular friend entirely.
 * This will display the friend's name, username, and entire history 
 * of posts.
 */
void GUI::viewFriendScreen() {


    // std::string friendUsername; // populate this
    // sandwich::User* friend = nullptr;
    //
    // auto friendList = currUser->getFriends();
    //
    // if(friendList.size() < 1) {
    //      display "No friends"
    // }
    //
    // for(unsigned int i = 0; i < friendList.size(); ++i) {
    //      if(friendList[i].getUsername() == friendUsername) {
    //          friend = friendList[i];
    //          i = friendList.size();
    //      }
    // }
    //
    // if(friend == nullptr) {
    //      "Could not find friend"
    // }
    // else {
    //      display friend->getUsername().c_str();
    //      display friend->getName().c_str();
    //      display friend->getBio().c_str();
    //
    //      auto posts = friend->getPosts();
    //      for(auto post : posts) {
    //          display "at " + post.getCTime() ", friend->getUsername.c_str() said:"
    //          display post.getCMsg();
    //          display post dividing line
    //      }
    // }
    //
}

/* This screen will allow you to edit your bio to fit your liking
*/
void GUI::editProfileScreen() {

    // Pseudocode
    // 1. Display currUser username, name, and bio, then draw line
    // 2. Display currUser's posts
    // 3. Prompt user to enter a new bio or to press esc to quit
}

/* This screen allows you to remove a friend by username
*/
void GUI::removeFriendScreen() {

    // Pseudocode
    // 1. Enter search bar
    // 2. on enter, get users vector of friends and see if any
    //    have a matching username.
    // 3. if there is a match, ask for confirmation and then remove.
    //    Otherwise, do nothing.
}

void GUI::logoutScreen(){
     erase(); 
    refresh(); 
    int x, y; 
    getmaxyx(stdscr, y, x); 
    //top and bottom windows based on the get max returns
    WINDOW * mainDisplay = newwin(y-4, x-14, 2, 7); 
    centerText(mainDisplay, (y-4)*.25, "Goodbye");

    wrefresh(mainDisplay); 
    refresh(); 
 
}


void GUI::testFunc() {

    std::string username = "Test username";
    currUser = new User(username, "name", "bio");

    trie.store(currUser->getUsername(), currUser);
    userMap[currUser->getLower()] = currUser;
}


void GUI::centerText(WINDOW *w, int yLoc, std::string text){
    int len, indent, depth, width; 
    getmaxyx(w, depth, width); 
    len = text.size();  
    indent = width - len; 
    indent /=2;
    mvwprintw(w, yLoc, indent, text.c_str()); 	
    //	mvaddstr(yLoc, indent, text.c_str()); 
    //	refresh(); 

}

int GUI::centerY(WINDOW *w){
    int y, x; 
    getmaxyx(w, y, x); 
    return y/2;
}

int GUI::centerX(WINDOW *w){
    int y, x; 
    getmaxyx(w, y, x); 
    return x/2;
}

std::string GUI::payload(WINDOW* w, char s){
    std::string temp; 
    int xinput=0;
    while(s!=10){
        mvwprintw(w,0,xinput,"%c", s); 
        xinput++; 
        wrefresh(w); 	       
        temp+=s; 
        s = wgetch(w); 
    }	
    return temp; 
}

int GUI::menu_selector(int n, int c, int* highlight, int a, int b){
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

		


std::string GUI::userInput (WINDOW * w, int max){
	std::string str;
	//char str[max];
	char s=0; 
	int y, x, c=0; 
	while(s!=10 && c<max){
		s =wgetch(w);
		getyx(w, y, x); 
		while(s == 127){
			s= ' ';
			x --;
			c--;  
		        str.erase(str.end()-1);	
			mvwprintw(w, y, x, "%c",s);
			wmove(w,y,x); 
			refresh(); 
			s=wgetch(w);
		}
		mvwprintw(w, y, x, "%c", s);
		if(c==max-1){
			mvwprintw(w,y+2, 2, "Characters are full, Max = %d",max); 
		}
		//else str[c]=s;
		else str +=s; 
		refresh(); 
		c++; 
		wrefresh(w);
	}	
	//if (s == 10 || c ==max){
	//	str += ' '; //str[c]='*'; 
	//}
	//std::string temp = std::string (str); 
	//return temp;
	//str.erase(str.end()-1, str.end()); 
	return str; 
}






void GUI::print_menu(WINDOW *w, int h, int n, std::string s[],int d){ 
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

int GUI::menu_setup(WINDOW* w, int d){ 
        std::string s[8] = {"Post to Wall", "View Friend List", "Add Friend", "Edit Profile", "View Friend", "Delete Friend","Home", "Logout"}; 
        int n = sizeof(s)/sizeof(std::string); //makes sure this automatically updates if something is added to the list of choices
    

	int choice;
	int h = 1;
	int y, x; 
	getmaxyx(stdscr, y, x); 
	print_menu(w, h, n, s, d); 
	while(1){
		int c = wgetch(w); 
		choice = menu_selector(n, c, &h, y-1, 5);  
		print_menu(w, h, n, s, d);  
		if(choice!=0)break; //user make a choice, break loop
	}
	return choice; 
}
	
GUI::Type GUI::submit_selection(WINDOW* w, int choice){
	switch(choice){
		case 1:
		        return sandwich::GUI::Type::POST_TO_WALL;
			break;	
		case 2: 
			return sandwich::GUI::Type::VIEW_FRIENDS;
			break;
		case 3: 
			return sandwich::GUI::Type::ADD_FRIEND;
			break; 
		case 4: 
			return sandwich::GUI::Type::EDIT_PROFILE;
			break;
		case 5: 
			return sandwich::GUI::Type::VIEW_FRIEND;
			break;
		case 6: 
			return sandwich::GUI::Type::REMOVE_FRIEND;
			break;
		case 7: 		
			return sandwich::GUI::Type::HOME;
			break;	
		case 8:
			return sandwich::GUI::Type::LOGOUT;
			break;		
		default: 
			mvwprintw(w, 12,8, "Press enter to select");
			wrefresh(w); 
			break; 
	}
	return sandwich::GUI::Type::HOME; 
}




} // namespace sandwich


#endif // SANDWICH_GUI_H_
