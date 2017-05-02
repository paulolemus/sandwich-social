/* File: GUI.h
 * Name: Jessica Grazziotin & Paulo Lemus
 * Team: Sandwich
 * Date: 4/23/2017
 */

/* The GUI class. This class contains code for distinct screens
 * that make up our UI. Each screen is mostly independent, so 
 * we are able to launch each screen independent of any other.
 */

#ifndef SANDWICH_GUI_H_
#define SANDWICH_GUI_H_

#include <algorithm>
#include <ncurses.h>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <string>
#include "User.h"
#include "Trie.h"

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
    std::string mainMenu[7] = {"Post to Wall", "View Friend List", "Add Friend", "Edit Your Bio", "View Friend", "Delete Friend", "Logout"}; 
    int n_main = sizeof(mainMenu)/sizeof(std::string); 
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

    void testFunc();
    void centerText(WINDOW *w, int yLoc, std::string text); //centers text in the input window
    int centerY(WINDOW *w); //returns the center y location of the window
    int centerX(WINDOW *w);  //returns the center x location of the window

    std::string payload(WINDOW* w, char s);
    void print_menu(WINDOW *w, int h, int n, std::string s[],int d); 
    int menu_selector(int n, int c, int* highlight, int a, int b);
    int menu_setup(WINDOW* w, int d, std::string inputArray[], int n); 
    std::string userInput(WINDOW* w, int max, bool trieBool);
    Type submit_selection(WINDOW* w, int choice);

    void memberListSetup();
    void checkScreenSize(); 
    std::string trieAutoComplete(std::string s, WINDOW* w);

};


GUI::GUI(std::unordered_map<std::string, sandwich::User*>& userMap,
        sandwich::Trie<sandwich::User*>&                  trie,
        sandwich::User*&                                  currUser) :
    userMap(userMap),
    trie(trie),
    currUser(currUser)
{ 
    //initializes the window, noecho, and cbreak at construction    
    initscr(); 
    noecho();
    cbreak();
    start_color(); //makes colors availiable for the GUI
    init_pair(1,COLOR_BLACK,COLOR_CYAN);// black letters with Cyan background
    init_pair(2,COLOR_RED,COLOR_WHITE); //red letters with white background
}

GUI::~GUI() {
    if(isendwin() == FALSE) {
        endwin();
        std::cout << "Called endwin" << std::endl;
    }
}

// Login screen is done. All that is left is minor optimizations and a bit 
// of cleaning, but all the functionality is there. 
GUI::Type GUI::loginScreen() {

    // Guard against small screen, create initial member
    checkScreenSize(); 
    memberListSetup(); 

    int y, x; 
    getmaxyx(stdscr, y, x); //returns the max x & y values of the screen  
    curs_set(1);

    WINDOW* mainWindow  = newwin(y - 4, x - 14, 2, 7); 
    WINDOW* inputWindow = newwin(1, 30, centerY(mainWindow) + 6, centerX(mainWindow) - 7); 
    WINDOW* outerBox    = newwin(y, x - 10, 0, 5);
    box(outerBox, 0, 0);

    wcolor_set(inputWindow, 2, NULL);
    wbkgd(inputWindow,COLOR_PAIR(1));
    centerText(mainWindow, (y - 4) * 0.25, "WELCOME TO SANDWICH SOCIAL"); 
    centerText(mainWindow, (y - 4) * 0.5, "Input your username to login or start a new account"); 	

    refresh();  
    wrefresh(outerBox); 
    wrefresh(mainWindow); 
    wmove(inputWindow, 0, 0);

    std::string loginName = userInput(inputWindow, 26, false); 
    wrefresh(mainWindow); 
    refresh();

    // variable to hold return option
    sandwich::GUI::Type returnOption;

    // verify login is correct
    if(!sandwich::User::validateStr(loginName)) {
        returnOption = sandwich::GUI::Type::LOGOUT;
    }
    // Check if the user exists in the map or the tree
    else if(userMap.find(sandwich::User::lowercaseify(loginName)) != userMap.end()) {

        currUser = userMap[sandwich::User::lowercaseify(loginName)];
        returnOption = sandwich::GUI::Type::HOME;
    }
    // If not found, then allow user to create an account
    else {
        // Initialize new windows used in the account creation screen
        werase(mainWindow);
        WINDOW* nameWindow = newwin(1, 30, centerY(mainWindow) + 4, centerX(mainWindow) - 7);
        WINDOW* bioWindow  = newwin(4, 50, (y - 4) * 0.75 + 6, centerX(mainWindow) - 15); 
        wbkgd(nameWindow, COLOR_PAIR(1)); 
        wbkgd(bioWindow,  COLOR_PAIR(1)); 

        // Draw all account creations strings to screen
        std::string newusrIntro = "Thanks for joining Sandwich Social " + loginName;
        centerText(mainWindow, (y - 4) * 0.25, newusrIntro); 
        centerText(mainWindow, (y - 4) * 0.25 + 1, "Input your information below: "); 	
        centerText(mainWindow, (y - 4) * 0.75, "Short Bio (Max 100 characters): ");
        mvwprintw(mainWindow, centerY(mainWindow) + 2, centerX(mainWindow) - 20, "Name: ");
        wmove(nameWindow, 0, 0);

        // Update terminal
        wrefresh(mainWindow); 
        wrefresh(bioWindow);
        wrefresh(nameWindow);

        // Get name from user input
        std::string nameString = userInput(nameWindow, 26, false); 
        wrefresh(mainWindow);
        wrefresh(nameWindow);
        wmove(bioWindow, 0, 0);

        // Get bio from user input
        std::string bioString = userInput(bioWindow, 104, false);

        // Add a new user with the obtained information
        if(sandwich::User::validateStr(loginName)  && 
                sandwich::User::validateStr(nameString) ) {

            currUser = new sandwich::User(loginName, nameString, bioString);
            userMap[currUser->getLower()] = currUser;
            trie.store(currUser->getUsername(), currUser);
            trie.store(currUser->getName(), currUser);

            returnOption = sandwich::GUI::Type::HOME;
        }
        else {
            returnOption = sandwich::GUI::Type::LOGOUT;
        }
        delwin(nameWindow);
        delwin(bioWindow);
    } // end else

    // cleanup
    erase();
    delwin(mainWindow);
    delwin(inputWindow);
    delwin(outerBox);
    return returnOption;
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
    curs_set(0);

    //top and bottom windows based on the get max returns
    WINDOW* topDisplay        = newwin(y * 0.625 - 4, x - 14, 2, 7); 
    WINDOW* bottomMenuDisplay = newwin(y * 0.25, x - 10, y * 0.625 + 3, 5); 
    WINDOW* topBox            = newwin(y * 0.625, x - 10, 0, 5); 
    // Box, enable arrow keys, draw strings
    box(topBox, 0, 0); 
    box(bottomMenuDisplay, 0, 0); 
    keypad(bottomMenuDisplay, true); 
    centerText(topDisplay, 3, "Welcome to your Homescreen");

    // Draw all changes to screen
    wrefresh(topBox); 
    wrefresh(bottomMenuDisplay); 
    wrefresh(topDisplay); 
    refresh();  

    int choice = menu_setup(bottomMenuDisplay, y * 0.25, mainMenu, n_main);
    return submit_selection(bottomMenuDisplay, choice); 
}


/* Post to wall screen allows user to write a text post
 * with a cap of 100 characters. This post will appear on
 * the user's feed, as well as all of his/her friend's feeds.
 */
void GUI::postWallScreen() {

    int x, y; 
    getmaxyx(stdscr, y, x); 
    curs_set(1);

    //top and bottom windows based on the get max returns
    WINDOW* topDisplay = newwin(y * 0.625 - 4, x - 14, 2, 7); 
    WINDOW* postWin    = newwin(4, 50, (y - 4) * 0.25, centerX(topDisplay) - 15);
    wbkgd(postWin, COLOR_PAIR(1)); 
    wclear(topDisplay);

    centerText(topDisplay, 3, "Write your new post (Max characters: 100):");
    wmove(postWin, 0, 0);

    wrefresh(topDisplay);
    wrefresh(postWin); 
    refresh();

    std::string postInput = userInput(postWin, 104, false); 
    sandwich::Post post(postInput);
    currUser->addPost(post);

    mvwprintw(topDisplay,(y - 4) * 0.25 + 6, 2, "At %s, you posted: ", post.getCTime());
    mvwprintw(topDisplay,(y - 4) * 0.25 + 7, 2, "%s", post.getCMsg()); 
    mvwprintw(topDisplay,(y - 4) * 0.25 + 9, 2, "Press any key to continue"); 
    wrefresh(topDisplay);
    refresh();
    getch();
}


/* view friends screen lets the user view all of his/her
 * friends names and usernames
 */
void GUI::viewFriendsScreen() {

    int x, y;
    getmaxyx(stdscr, y, x);
    curs_set(0);

    // Window initialization - enable keys, set up box, clear
    WINDOW* topDisplay = newwin(y * 0.625 - 4, x - 14, 2, 7);
    WINDOW* topBox     = newwin(y * 0.625, x - 10, 0, 5);
    wclear(topDisplay);
    box(topBox, 0, 0);
    keypad(topDisplay, true);

    centerText(topDisplay, 0, "Friends List");
    centerText(topDisplay, 1, "Use arrows to scroll, 'q' to quit");

    // Grab all current friends from user
    std::vector<const sandwich::User*> friendList = currUser->getFriends();

    // if User has no friends
    if(friendList.size() < 1) {
        centerText(topDisplay, y / 4, "You have no friends");
        centerText(topDisplay, y / 4 + 1, "Press any key to return");
        wrefresh(topDisplay);
        wgetch(topDisplay);
    }
    // populate all friends to screen
    else {
        unsigned int yDisp, xDisp, index, yMax;
        getmaxyx(topDisplay, yDisp, xDisp);
        std::vector<std::string> userData;
        std::string borderStr;
        for(unsigned int i = 0; i < xDisp; ++i) {
            borderStr += '-';
        }

        // Fill userData will strings for each user
        for(auto friendPtr : friendList) {
            userData.push_back(borderStr);
            userData.push_back("Username: " + friendPtr->getUsername());
            userData.push_back("Name    : " + friendPtr->getName());
            userData.push_back("Bio     : " + friendPtr->getBio());
        }

        int input;
        index = 0;
        yMax  = userData.size() > yDisp - 2 ? yDisp - 2 : userData.size();
        do {
            // Print everything to screen
            werase(topDisplay);
            centerText(topDisplay, 0, "Friends List");
            centerText(topDisplay, 1, "Use arrows to scroll, 'q' to quit");
            for(unsigned int i = 0; i < yMax; ++i) {
                mvwprintw(topDisplay, i + 2, 0, "%s", userData[index + i].c_str());
            }
            refresh();
            wrefresh(topDisplay);

            // Get next character for scrolling
            input = wgetch(topDisplay);
            switch(input) {
                case KEY_UP: // key up
                    if(index > 0) index--; 
                    break;
                case KEY_DOWN: // key down
                    if(index + yMax < userData.size()) index++;
                    break;
                default:
                    break;
            }
        } while(input != 'q');
    }
    // clean up
    delwin(topDisplay);
    delwin(topBox);
}

/* Add friend screen allows the user to search through friends
 * and add them based on username. It will reactively display 
 * all the possible friends that match the string the user is typing.
 */
void GUI::addFriendScreen() {

    int x, y; 
    getmaxyx(stdscr, y, x); 
    //top and bottom windows based on the get max returns
    WINDOW * topDisplay = newwin((y*.625)-4, x-14, 2, 7); 
    //box for the top window
    WINDOW * topBox = newwin((y*.625), x-10,0, 5); 
    //create boxes for the box windows
    box(topBox, 0,0); 
    //setup keypad and refresh all windows

    centerText(topDisplay, 2, "List of Friends to add");
    int i =0;
    for (auto it = userMap.begin(); it != userMap.end(); it++){
        mvwprintw(topDisplay, i+4, 0, "Username: %s", it->first.c_str()); 
        mvwprintw(topDisplay, i+4, 30, "Name: %s", it->second->getName().c_str()); 
        i ++; 
    }

    WINDOW* nameWindow = newwin(1, 30, centerY(topDisplay) + 4, centerX(topDisplay) - 7);
    wbkgd(nameWindow, COLOR_PAIR(1)); 
    wmove(nameWindow, 0, 0);
    wrefresh(topBox);
    wrefresh(topDisplay);


    wrefresh(nameWindow);
    refresh(); 
    std::string nameString = userInput(nameWindow, 26, false); 

    for (unsigned int i =0; i<nameString.size(); i++){
        if(nameString[i] >= 'A' && nameString[i] <= 'Z'){
            nameString[i] = nameString[i] +32;
        }
    }


    int ymax, xmax, ybeg, xbeg=0;
    getmaxyx(nameWindow, ymax, xmax); 
    getbegyx(nameWindow, ybeg, xbeg); 
    // WINDOW* trieWindow = newwin(5, xmax, ybeg+1, xbeg); 

    std::string prefix;
    // auto friendList = trie.getComplete(prefix);
    // int t_size = temp.size();
    // for(auto friendPtr : friendList) {

    //	    mvwprintw(friendPtr->getUsername().c_str();
    //	friendPtr->getName().c_str();
    //	friendPtr->getBio().c_str();
    //      draw line to deparate users
    // }


    sandwich::User* friendCopy;

    if(trie.search(nameString)){
        //	auto temp = trie.getComplete(prefix);
        //	auto tempString = temp.pop_back();
        mvwprintw(topDisplay, i+12, 0, "User: %s found!", nameString.c_str());   
        auto friendList = trie.getComplete(nameString);
        if(friendList.size() < 1) {
            //      display "No matching users. Please broaden your search"
        }
        // clear the currently displayed friends here
        for(auto friendPtr : friendList) {
            if(friendPtr->getUsername() == nameString){
                mvwprintw(topDisplay, i+20, 0,"%s is almost your friend", friendPtr->getUsername().c_str());
                i++;
                friendCopy = friendPtr;
            }
        }
        //      display friendPtr->getName().c_str()
        //      display friendPtr->getBio().c_str()
        //      draw line to deparate users
        // }
        currUser->addFriend(friendCopy);
        wrefresh(topDisplay); 
    } 
    getch();
    delwin(topDisplay);
    delwin(nameWindow);
    delwin(topBox);
}

/* View friend screen allows you to view a particular friend entirely.
* This will display the friend's name, username, and entire history
* of posts.
*/
void GUI::viewFriendScreen() {

	int x, y; 
	getmaxyx(stdscr, y, x); 
	curs_set(1);

	// Create windows to be used for user input and display
	WINDOW* topDisplay = newwin(y * 0.625 - 4, x - 14, 2, 7); 
	WINDOW* nameWindow = newwin(1, 30, centerY(topDisplay) + 4, centerX(topDisplay) - 7);
	wbkgd(nameWindow, COLOR_PAIR(1)); 
	wmove(nameWindow, 0, 0);
	keypad(topDisplay, true);

	centerText(topDisplay, (y - 4) * 0.25, "Enter friend's username below");
	refresh();
	wrefresh(topDisplay);
	wrefresh(nameWindow);

    // Get user input and check if we are friends with the user
    auto friends = currUser->getFriends();
    std::string inputUsername = userInput(nameWindow, 26, false);

    // Convert the username string to lowercase
    for(unsigned int i = 0; i < inputUsername.size(); ++i) {
        if(inputUsername[i] >= 'A' && inputUsername[i] <= 'Z') {
            inputUsername[i] = inputUsername[i] + 32;
        }
    }
    
    // Locate friend in the friends vector
    const sandwich::User* theFriend = nullptr;
    for(unsigned int i = 0; i < friends.size(); ++i) {
        if(friends[i]->getLower() == inputUsername) {
            theFriend = friends[i];
            i = friends.size();
        }
    }

    getmaxyx(topDisplay, y, x);

    // Display corresponding results
    if(theFriend == nullptr) {
        centerText(topDisplay, y * 0.7, "Friend not found :(");
        centerText(topDisplay, y * 0.7 + 1, "Press any key to continue");
        wrefresh(topDisplay);
        wrefresh(nameWindow);
        getch();
    }
    else {
        // initialize some information to be used in loop
        curs_set(0);
        keypad(topDisplay, true);

        std::string border;
        for(int i = 0; i < x; ++i) border += '-';

        std::vector<std::string> postInfo;
        std::vector<sandwich::Post> posts = theFriend->getPosts();

        for(int i = posts.size() - 1; i >= 0; --i) {
            postInfo.push_back("At " + posts[i].getTime() + ", " + theFriend->getUsername() + " said:");
            postInfo.push_back(posts[i].getMsg());
            postInfo.push_back(border);
        }

        int input, index = 0;
        int yMax = postInfo.size() > y - 5 ? y - 5 : postInfo.size();
        do {
            // Print everything to screen
            werase(topDisplay);
            centerText(topDisplay, 0, "Use arrows to scroll, 'q' to quit");
            mvwprintw(topDisplay, 1, 0, border.c_str());
            mvwprintw(topDisplay, 2, 0, "Username: %s", theFriend->getUsername().c_str());
            mvwprintw(topDisplay, 3, 0, "Name    : %s", theFriend->getName().c_str());
            mvwprintw(topDisplay, 4, 0, "Bio     : %s", theFriend->getBio().c_str());
            mvwprintw(topDisplay, 5, 0, border.c_str());
            for(int i = 0; i < yMax; ++i) {
                mvwprintw(topDisplay, i + 5, 0, "%s", postInfo[index + i].c_str());
            }
            refresh();
            wrefresh(topDisplay);

            // Get next character for scrolling
            input = wgetch(topDisplay);
            switch(input) {
                case KEY_UP: // key up
                    if(index > 0) index--; 
                    break;
                case KEY_DOWN: // key down
                    if(index + yMax < postInfo.size()) index++;
                    break;
                default:
                    break;
            }
        } while(input != 'q');
    }
    // Cleanup
    delwin(topDisplay);
    delwin(nameWindow);
}

/* This screen will allow you to edit your bio to fit your liking
*/
void GUI::editProfileScreen() {

    erase(); 
    refresh(); 
    int x, y; 
    getmaxyx(stdscr, y, x); 
    //top and bottom windows based on the get max returns
    WINDOW* topDisplay        = newwin(y * 0.625 - 4, x - 14, 2, 7); 
    WINDOW* bottomMenuDisplay = newwin(y * 0.25, x - 10, y * 0.625 + 3, 5); 
    //box for the top window
    WINDOW* topBox = newwin(y * 0.625, x - 10, 0, 5); 
    //create boxes for the box windows
    box(topBox, 0, 0); 
    box(bottomMenuDisplay, 0, 0); 
    //setup keypad and refresh all windows
    keypad(bottomMenuDisplay, true); 
    wrefresh(topBox); 
    wrefresh(bottomMenuDisplay); 
    refresh(); 
    wrefresh(topDisplay); 

    std::string nameString = currUser->getUsername(); 
    std::string bioString  = currUser->getBio(); 

    centerText(topDisplay, 0, "Edit your bio");
    mvwprintw(topDisplay, 2, 0, "Name: %s", nameString.c_str());
    mvwprintw(topDisplay, 3, 0, "Bio: %s", bioString.c_str());
    centerText(topDisplay, 5, "Edit your bio in the box below (Max characters:100)");

    WINDOW* bioWindow = newwin(4, 50, 9, centerX(topDisplay) - 15); 
    wbkgd(bioWindow, COLOR_PAIR(1)); 
    wmove(bioWindow, 0, 0); 
    wrefresh(bioWindow); 
    wrefresh(topBox);
    wrefresh(topDisplay);
    refresh();

    bioString = userInput(bioWindow, 104, false);
    currUser->setBio(bioString);
    std::string newBioString = currUser->getBio();
    mvwprintw(topDisplay, 12, 0, "New Bio: %s", newBioString.c_str());  
    wrefresh(topBox);
    wrefresh(topDisplay);
    refresh();

    // Pseudocode
    // 1. Display currUser username, name, and bio, then draw line
    // 2. Display currUser's posts
    // 3. Prompt user to enter a new bio or to press esc to quit
}

/* This screen allows you to remove a friend by username
*/
void GUI::removeFriendScreen() {

	int x, y; 
	getmaxyx(stdscr, y, x); 
	curs_set(1);

	// Create Configure the top box which is used to take user input
	WINDOW* topWindow   = newwin(y * 0.625 - 4, x - 14, 2, 7);
	WINDOW* inputWindow = newwin(1, 80, 3, centerX(topWindow) - 35);
    WINDOW* dataWindow  = newwin(y * 0.625 - 8, x - 14, 2 + 4, 7);
    getmaxyx(topWindow, y, x);
	wbkgd(inputWindow, COLOR_PAIR(1));
	wmove(inputWindow, 0, 0);

	centerText(topWindow, 0, "Enter friend's name below");
	refresh();
	wrefresh(topWindow);
	wrefresh(inputWindow);

    // Populate a new Trie with the friends of just this user
    sandwich::Trie<const sandwich::User*> friendTrie;
    auto friendList = currUser->getFriends();
    for(auto person : friendList) {
        friendTrie.store(person->getUsername(), person);
        friendTrie.store(person->getName(),     person);
    }

    // Get all user input and populate the topWindow with user matches    
    std::string usernameInput;
    std::string border;
    for(int i = 0; i < getmaxx(dataWindow); ++i) border += '-';
    int xMin = 0, xMax = 79, xCurr = 0;

    int ch = wgetch(inputWindow);
    while(ch != 10) { // 10 == "Enter"

        // User input begin
        if(ch == 27) { // esc
            // TODO
        }
        else if(ch == 127) { // delete
            if(xCurr > xMin) {
                mvwaddch(inputWindow, 0, --xCurr, ' ');
                if(usernameInput.size() > 0) usernameInput.pop_back();
            }
        }
        else {
            if(xCurr < xMax) {
                mvwaddch(inputWindow, 0, xCurr++, ch);
                usernameInput += ch;
            }
        }
        // User input end
        
        // Match search begin
        werase(dataWindow);
        auto matches = friendTrie.getComplete(usernameInput);
        if(matches.size() < 1) {
            centerText(dataWindow, getmaxy(dataWindow) / 2, "No matches for your search!");
        }
        else {

            // Print all user data to screen
            int          line   = 0;
            unsigned int mIndex = 0;
            while(line < getmaxy(dataWindow) && mIndex < matches.size()) {
                mvwprintw(dataWindow, line, 0, border.c_str());
                line++;
                if(line < getmaxy(dataWindow) && mIndex < matches.size()) {
                    mvwprintw(dataWindow, line, 0, "Username: %s", matches[mIndex]->getUsername().c_str());
                }
                line++;
                if(line < getmaxy(dataWindow) && mIndex < matches.size()) {
                    mvwprintw(dataWindow, line, 0, "Name    : %s", matches[mIndex]->getName().c_str());
                }
                line++;
                if(line < getmaxy(dataWindow) && mIndex < matches.size()) {
                    mvwprintw(dataWindow, line, 0, "Bio     : %s", matches[mIndex]->getBio().c_str());
                }
                line++;
                mIndex++;
            }
        }
        // Match search end
        wmove(inputWindow, 0, xCurr);
        refresh();
        wrefresh(dataWindow);
        wrefresh(inputWindow);
        ch = wgetch(inputWindow);
    } // end while

    // Delete friend if exists
    wclear(dataWindow);
    auto possibleUsers = friendTrie.get(usernameInput);
    if(possibleUsers.size() < 1) {
        centerText(dataWindow, getmaxy(dataWindow) / 2, "Could not find the friend");
    }
    else {
        // Convert usernameInput to lowercase
        usernameInput = sandwich::User::lowercaseify(usernameInput);

        // Delete the friend
        bool isDeleted = false;
        for(auto friendPtr : possibleUsers) {
            if(friendPtr->getLower() == usernameInput) {
                currUser->removeFriend(friendPtr);
                isDeleted = true;
            }
        }
        if(isDeleted) {
            centerText(dataWindow, getmaxy(dataWindow) / 2, usernameInput + " has been removed");
        }
        else {
            centerText(dataWindow, getmaxy(dataWindow) / 2, "Something went wrong");
        }
    }
    centerText(dataWindow, getmaxy(dataWindow) / 2 + 1, "Press any key to continue");
    wrefresh(dataWindow);
    wgetch(dataWindow);
    
    // cleanup
    delwin(topWindow);
    delwin(inputWindow);
    delwin(dataWindow);
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
    switch(c){
        case KEY_UP:
            if(*highlight ==1) *highlight = n; 
            else (*highlight) --; 
            break; 
        case KEY_DOWN: 
            if(*highlight == n) *highlight = 1; 	
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

std::string GUI::userInput(WINDOW * w, int max, bool trieBool){
    std::string str;
    char s=0; 
    int y, x, ylast, xlast,c=0; 
    getmaxyx(w, ylast, xlast);
    getbegyx(w, y, x);
    // mvwprintw(w,0,0, "ybeg: %d and xbeg %d", y, x);
    while(s!=10){
        s =wgetch(w);
        if (s == 27){
            werase(w);
            mvwprintw(w,0,0, "Press ESC to Select from the Menu or Enter to continue");
            s = wgetch(w);
            if (s == 27) return "back";
            else if (s == 10){
                wclear(w);
                wmove(w,0,0);
                wrefresh(w);
                refresh();
                str.clear();
                s = wgetch(w);
            }
        }
        getyx(w, y, x); 

        while(s == 127){
            if(c==0) s= wgetch(w);
            else{
                s= ' ';
                x --;
                c--;  
                str.erase(str.end()-1);	
                mvwprintw(w, y, x, "%c",s);
                wmove(w,y,x); 
                refresh(); 
                if(c==max-3){
                    mvwprintw(w,y,xlast-4, "     ");
                    refresh();	            
                }
                s=wgetch(w);
            }
        }
        if(c>max-3){
            mvwprintw(w,y, xlast-4, "-MAX");
            refresh();
            s = ' ';
            c--;	
            str.erase(str.end()-1);
            mvwprintw(w,y,x, "%c", s);
            wmove(w,y,x);
            refresh();
        }
        else mvwprintw(w, y, x, "%c", s);
        str +=s; 
        if (trieBool){
            str = trieAutoComplete(str, w); 
        }
        refresh(); 
        c++; 
        wrefresh(w);
    }	
    str.erase(std::remove(str.begin(),str.end(), '\n'), str.end());
    return str; 
}


std::string GUI::trieAutoComplete(std::string s, WINDOW* w){
	int xmax, ymax, xbeg, ybeg = 0; 
	getmaxyx(w, ymax, xmax); 
	getbegyx(w, ybeg, xbeg);
	WINDOW* trieWindow = newwin(5, xmax, ybeg+1, xbeg); 
	wbkgd(trieWindow, COLOR_PAIR(2)); 
	wattron(trieWindow,COLOR_PAIR(1));
	//keypad(trieWindow, true);
	wrefresh(trieWindow);
	refresh();
	int j=3;
	std::string prefix= "WORDS";
	mvwprintw(trieWindow, ybeg+1+j, 0, "%s", prefix.c_str()); 
 	wrefresh(trieWindow);
	refresh();
//	getch();
	auto friendList = trie.getComplete(s);
	for(auto friendPtr : friendList) {
		int i =0;
    		while(trie.search(s) && i<5){
			mvwprintw(trieWindow, ybeg+1+i, 0,"%s", friendPtr->getUsername().c_str());
			wrefresh(trieWindow);
    		}
   	}

	wrefresh(trieWindow);
	//refresh(); 
	//getch();
	//delwin(trieWindow);
	std::string tester = "bec";
	return tester; 
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

    int GUI::menu_setup(WINDOW* w, int d, std::string inputArray[], int n){ 
    int choice = 0;
    int h = 1;
    int y, x; 
    getmaxyx(stdscr, y, x); 
    print_menu(w, h, n, inputArray, d); 
    while(1){
        int c = wgetch(w); 
        choice = menu_selector(n, c, &h, y-1, 5);  
        print_menu(w, h, n, inputArray, d);  
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
            return sandwich::GUI::Type::LOGOUT;
            break;		
        default: 
            mvwprintw(w, 10,8, "Press enter to select");
            wrefresh(w); 
            break; 
    }
    return sandwich::GUI::Type::HOME; 
}

void GUI::memberListSetup(){
    //create a start user for testing
    std::string username = "jack";
    sandwich::User* tester = new sandwich::User(username, "name", "bio"); 
    //create insert the username into the Map paired with the tester
    userMap.insert({tester->getLower(), tester});
    //store the user in the trie by its user name
    trie.store(tester->getUsername(), tester); 
    trie.store(tester->getName(),     tester); 

    sandwich::User* friend1 = new sandwich::User("fred", "Freddy G", "I love singing!");
    userMap.insert({friend1->getLower(), friend1});
    trie.store(friend1->getUsername(), friend1);

    sandwich::User* friend2 = new sandwich::User("leroy", "LeRoy B", "I'm the real OG");
    userMap.insert({friend2->getLower(), friend2});
    trie.store(friend2->getUsername(), friend2);


    tester->addFriend(friend1);
    tester->addFriend(friend2);
    tester->addFriend(new sandwich::User("test1", "tester1", "sdgsdfbsdf"));
    tester->addFriend(new sandwich::User("test2", "tester2", "sddfdfbsdf"));
    tester->addFriend(new sandwich::User("test3", "tester3", "sdgsdfbdsv"));
    tester->addFriend(new sandwich::User("test4", "tester4", "sdgsdfbsds"));
    tester->addFriend(new sandwich::User("test5", "tester5", "sdgsdfbdgs"));
    tester->addFriend(new sandwich::User("test6", "tester6", "sdsasdfbsdf"));

    sandwich::User* tester2 = new sandwich::User("becky", "Rebecca L", "Becky with the good hair"); 
    userMap.insert({tester2->getLower(), tester2});
    trie.store("becky", tester2); 

    sandwich::User* friend3 = new sandwich::User("benny", "Benjamin F", "OG of electriCity"); 
    userMap.insert({friend3->getLower(), friend3}); 
    trie.store(friend3->getUsername(), friend3);

    tester2->addFriend(friend1);
    tester2->addFriend(friend3); 
}

void GUI::checkScreenSize(){
    int y,x;
    getmaxyx(stdscr, y, x); 
    if (y < 50 || x < 75){
        endwin();
        std::cout << "Please Enlarge Your Screen and Start Program Again\n";
        std::cout << "Proper dimensions are y > 50 and x > 75\n";
        exit(1); 
    } 
}

} // namespace sandwich


#endif // SANDWICH_GUI_H_
