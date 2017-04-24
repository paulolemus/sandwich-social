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
    void center(WINDOW *w, int yLoc, std::string text);
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

GUI::~GUI() {
    endwin();
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
//	mvwprintw(w,(y-4)*.25, (x-14)/3, "WELCOME TO SANDWICH SOCIAL");
  //     	mvwprintw(w,(y-4)*.5, (x-14)*.25, "Input your username to login or start an account below: "); 	
	center(w, (y-4)*.25, "WELCOME TO SANDWICH SOCIAL"); 
        center(w, (y-4)*.5, "Input your username to login or start a new account"); 	
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
	return sandwich::GUI::Type::LOGOUT;
}

/* Post to wall screen allows user to write a text post
 * with a cap of 100 characters. This post will appear on
 * the user's feed, as well as all of his/her friend's feeds.
 */
void GUI::postWallScreen() {

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

void GUI::testFunc() {

    std::string username = "Test username";
    currUser = new User();
    currUser->setUsername(username);

    trie.store(currUser->getUsername(), currUser);
    userMap[currUser->getLower()] = currUser;
}
	

void GUI::center(WINDOW *w, int yLoc, std::string text){
	int len, indent, depth, width; 
	getmaxyx(stdscr, depth, width); 
	len = text.size();  
	indent = width -14 - len; 
	indent /=2;
        mvwprintw(w, yLoc, indent, text.c_str()); 	
//	mvaddstr(yLoc, indent, text.c_str()); 
//	refresh(); 
	
}

} // namespace sandwich

#endif // SANDWICH_GUI_H_
