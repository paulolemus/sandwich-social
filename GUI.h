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

#include <ncurses.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
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

    const std::string EXIT_STR = "EXIT_STR_NOW_SPECIAL#$%";
    const std::string mainMenu[7] = 
    {
        "Post to Wall", 
        "View Friend List", 
        "Add Friend", 
        "Edit Your Bio", 
        "View Friend", 
        "Remove Friend", 
        "Logout"
    }; 
    const int n_main = sizeof(mainMenu) / sizeof(std::string);

public:
    enum class Type : int {
        HOME,
        POST_TO_WALL,
        FRIEND_LIST,
        ADD_FRIEND,
        VIEW_FRIEND,
        REMOVE_FRIEND,
        EDIT_PROFILE,
        LOGOUT,
        QUIT
    };
	
    //findex
    GUI(std::unordered_map<std::string, sandwich::User*>& userMap, 	    //f01
        sandwich::Trie<sandwich::User*>&                  trie,
        sandwich::User*&                                  currUser);

    ~GUI();                         								    //f02
    void testFunc();				                    			    //f03
	
    //the main two types of screens
    Type loginScreen();							                        //f04
    Type homeScreen();						                    	    //f05

    //other screen options
    void postWallScreen();                                              //f06
    void friendListScreen();                                            //f07
    void addFriendScreen();					                    	    //f08
    void viewFriendScreen();						                    //f09
    void editProfileScreen();						                    //f10
    void removeFriendScreen();					                       	//f11

    //menu functions
    int menu_setup(WINDOW* w, const std::string inputArray[], int n);	//f12
    void print_menu(WINDOW* w, int h, int n, const std::string s[]);	//f13
    int menu_selector(int n, int c, int* highlight, int a, int b);	    //f14
    Type submit_selection(WINDOW* w, int choice);			            //f15
	
    //other functions
    void centerText(WINDOW* w, int yLoc, std::string text);             //f16
    int centerY(WINDOW *w);                                             //f17
    int centerX(WINDOW *w);                                             //f18
    std::string userInput(WINDOW* w, int max);                          //f19
	
    //functions for setup in the main driver	
    void memberListSetup();						                        //f20
    void checkScreenSize();						                        //f21
};

//f01
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
    init_pair(2,COLOR_BLACK,COLOR_GREEN); //red letters with white background
}
//f02
GUI::~GUI() {
    if(isendwin() == FALSE) {
        endwin();
        std::cout << "Called endwin" << std::endl;
    }
}

//f03
void GUI::testFunc() {

    std::string username = "Test username";
    currUser = new User(username, "name", "bio");
    trie.store(currUser->getUsername(), currUser);
    userMap[currUser->getLower()] = currUser;
}

//f04
// 1. Get a username from user.
// 2. If the username belongs to an existing user, set currUser to it.
// 3. Else, create a new user then set curr user as it.
GUI::Type GUI::loginScreen() {

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

    std::string loginName = userInput(inputWindow, 26); 
    wrefresh(mainWindow); 
    refresh();

    // variable to hold return option
    sandwich::GUI::Type returnOption;

    // Check for exit string
    if(loginName == EXIT_STR) {
        returnOption = sandwich::GUI::Type::QUIT;
    }
    // verify login is correct
    else if(!sandwich::User::validateStr(loginName)) {
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
        std::string nameString = userInput(nameWindow, 26);
        if(nameString == EXIT_STR) {
            delwin(mainWindow);
            delwin(inputWindow);
            delwin(outerBox);
            return sandwich::GUI::Type::LOGOUT;
        }
        wrefresh(mainWindow);
        wrefresh(nameWindow);
        wmove(bioWindow, 0, 0);

        // Get bio from user input
        std::string bioString = userInput(bioWindow, 104);
        if(bioString == EXIT_STR) {
            delwin(mainWindow);
            delwin(inputWindow);
            delwin(outerBox);
            return sandwich::GUI::Type::LOGOUT;
        }

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
//f05
GUI::Type GUI::homeScreen() {
//The homescreen will show the latest post from all of the user's friends

    erase();
    refresh();
    int x, y; 
    getmaxyx(stdscr, y, x); 
    curs_set(0);

    // Create windows to be used for user input and display

    //top and bottom windows based on the get max returns
    WINDOW* topDisplay        = newwin(y * 0.625 - 4, x - 14, 2, 7); 
    WINDOW* bottomMenuDisplay = newwin(y * 0.25, x - 10, y * 0.625 + 3, 5); 
    WINDOW* topBox            = newwin(y * 0.625, x - 10, 0, 5); 
    // Box, enable arrow keys, draw strings
    box(topBox, 0, 0); 
    box(bottomMenuDisplay, 0, 0); 
    keypad(bottomMenuDisplay, true); 
	//keypad(topDisplay,        true);

    // Draw all changes to screen
    wrefresh(topBox); 
    wrefresh(bottomMenuDisplay); 
    wrefresh(topDisplay); 
    refresh();  

    print_menu(bottomMenuDisplay, 1, n_main, mainMenu); 
    wrefresh(bottomMenuDisplay);


    auto friends = currUser->getFriends();
    //pulled from delet a friend
    std::vector<std::string> postInfo;        
    std::vector<sandwich::Post> posts;
    int xTop = getmaxx(topDisplay);
    std::string border;
    for(int i = 0; i < xTop; ++i) border += '-';

    // Locate friend in the friends vector
    const sandwich::User* theFriend = nullptr;
    for(unsigned int i = 0; i < friends.size(); ++i) {
        theFriend = friends[i];
        posts = theFriend->getPosts();
        if(posts.size() > 0) {
            int j = posts.size() - 1;
            postInfo.push_back("At " + posts[j].getTime() + ", " + theFriend->getUsername() + " said:");
            postInfo.push_back(posts[j].getMsg());
            postInfo.push_back(border); 
        }
    }
    posts = currUser->getPosts();
    if(posts.size() > 0) {
        postInfo.push_back("At " + posts[posts.size() - 1].getTime() + ", you said:");
        postInfo.push_back(posts[posts.size() - 1].getMsg());
        postInfo.push_back(border);
    }

    curs_set(0);
    keypad(topDisplay, true);
    

    y = getmaxy(topDisplay); 
    int input, index = 0;
    int yMax = postInfo.size() > y - 7 ? y - 7 : postInfo.size();
    int choice;
    do { 
        do {
            // Print everything to screen
            werase(topDisplay);
            wattron(topDisplay, A_REVERSE);
            wattron(topDisplay, COLOR_PAIR(2)); 
            centerText(topDisplay, 0, "Use arrows to scroll or press 'q' to switch between the top and bottom menu");
            centerText(topDisplay, 3, "Welcome to your Homescreen");
            centerText(topDisplay, 4, "-------------------- Posts  --------------------");
            mvwprintw(topDisplay, 5, 0, border.c_str());
            wattroff(topDisplay, COLOR_PAIR(2)); 
            wattron(topDisplay, COLOR_PAIR(1)); 
            for(int i = 0; i < yMax; ++i) {
                mvwprintw(topDisplay, i + 7, 0, "%s", postInfo[index + i].c_str());
            }
            wattroff(topDisplay, COLOR_PAIR(1));
            wattroff(topDisplay, A_REVERSE);
                    
            // initialize some information to be used in loop
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
        choice = menu_setup(bottomMenuDisplay, mainMenu, n_main);
    } while(choice == 'q');



    wmove(bottomMenuDisplay, 0,0);
    refresh();

    
    // Cleanup
    delwin(topDisplay);
    delwin(bottomMenuDisplay);
    delwin(topBox);

    return submit_selection(bottomMenuDisplay, choice); 
}

/* Post to wall screen allows user to write a text post
 * with a cap of 100 characters. This post will appear on
 * the user's feed, as well as all of his/her friend's feeds.
 */
//f06
void GUI::postWallScreen() {

    int x, y; 
    getmaxyx(stdscr, y, x); 
    curs_set(0);

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
    curs_set(1);
    wrefresh(postWin);

    std::string postInput = userInput(postWin, 104);
    if(postInput != EXIT_STR) {
        sandwich::Post post(postInput);
        currUser->addPost(post);

        mvwprintw(topDisplay,(y - 4) * 0.25 + 6, 2, "At %s, you posted: ", post.getCTime());
        mvwprintw(topDisplay,(y - 4) * 0.25 + 7, 2, "%s", post.getCMsg()); 
        mvwprintw(topDisplay,(y - 4) * 0.25 + 9, 2, "Press any key to continue"); 
        curs_set(0);
        wrefresh(topDisplay);
        refresh();
        getch();
    }
}


/* view friends screen lets the user view all of his/her
 * friends names and usernames
 */
//f07
void GUI::friendListScreen() {

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
        } while(input != 'q' && input != 27);
    }
    // clean up
    delwin(topDisplay);
    delwin(topBox);
}

/* Add friend screen allows the user to search through friends
 * and add them based on username. It will reactively display 
 * all the possible friends that match the string the user is typing.
 */
//f08
void GUI::addFriendScreen() {

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
    
	centerText(topWindow, 0, "Enter friend's USERNAME below");
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

    // Populate a stranger Trie with all users that are not your friends.
    // Iterate through each user in the userMap. Check if it exists in the
    // friendTrie. If it does not, then add it to the strangerTrie.
    sandwich::Trie<const sandwich::User*> strangerTrie;
    for(auto userPair : userMap){

        auto userPtr = userPair.second;
        auto matches = friendTrie.getComplete(userPair.first);

        if (std::find(matches.begin(), matches.end(), userPtr) == matches.end()) {
            strangerTrie.store(userPtr->getUsername(), userPtr);
            strangerTrie.store(userPtr->getName(),     userPtr);
        }
    }

    wrefresh(topWindow);
    
    // Get all user input and populate the topWindow with user matches    
    std::string usernameInput;
    std::string border;
    for(int i = 0; i < getmaxx(dataWindow); ++i) border += '-';
    int xMin = 0, xMax = 79, xCurr = 0;

    int ch = 0;
    do {
        // User input begin
        if(ch == 27) { // esc
            delwin(topWindow);
            delwin(inputWindow);
            delwin(dataWindow);
            return;
        }
        else if(ch == 127) { // delete 127
            if(xCurr > xMin) {
                mvwaddch(inputWindow, 0, --xCurr, ' ');
                if(usernameInput.size() > 0) usernameInput.pop_back();
            }
        }
        else if(isalpha(ch) || ch == ' ') {
            if(xCurr < xMax) {
                mvwaddch(inputWindow, 0, xCurr++, ch);
                usernameInput += ch;
            }
        }
        // User input end
        
        // Match search begin
        werase(dataWindow);
        auto matches = strangerTrie.getComplete(usernameInput);
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
    } while(ch != 10); // 10 == enter

    // ADD friend if exists
    wclear(dataWindow);
    auto possibleUsers = strangerTrie.get(usernameInput);
    if(possibleUsers.size() < 1) {
        centerText(dataWindow, getmaxy(dataWindow) / 2, "Could not find the friend");
    }
    else {
        // Convert usernameInput to lowercase
        usernameInput = sandwich::User::lowercaseify(usernameInput);

        // ADD the friend
        bool isAdded = false;
        for(auto friendPtr : possibleUsers) {
            if(friendPtr->getLower() == usernameInput) {
                currUser->addFriend(friendPtr);
                isAdded = true;
            }
        }
        if(isAdded){
            centerText(dataWindow, getmaxy(dataWindow) / 2, usernameInput + " is now your Friend!");
        }
        else {
            centerText(dataWindow, getmaxy(dataWindow) / 2, "Something went wrong");
        }
    }
    centerText(dataWindow, getmaxy(dataWindow) / 2 + 1, "Press any key to continue");
   	curs_set(0);

    wrefresh(dataWindow);
    refresh();
    wgetch(dataWindow);
    
    // cleanup
    delwin(topWindow);
    delwin(inputWindow);
    delwin(dataWindow);
}


/* View friend screen allows you to view a particular friend entirely.
* This will display the friend's name, username, and entire history
* of posts.
*/
//f09
void GUI::viewFriendScreen() {

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

	centerText(topWindow, 0, "Enter friend's USERNAME below");
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

    int ch = 0;
    do {

        // User input begin
        if(ch == 27) { // esc
            delwin(topWindow);
            delwin(inputWindow);
            delwin(dataWindow);
            return;
        }
        else if(ch == 127) { // delete
            if(xCurr > xMin) {
                mvwaddch(inputWindow, 0, --xCurr, ' ');
                if(usernameInput.size() > 0) usernameInput.pop_back();
            }
        }
        else if(isalpha(ch) || ch == ' ') {
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
        wrefresh(dataWindow);
        wrefresh(inputWindow);
        ch = wgetch(inputWindow);
    } while(ch != 10); // != enter

    // Get the user pointer
    usernameInput = sandwich::User::lowercaseify(usernameInput);
    const sandwich::User* theFriend = nullptr;
    auto possibleFriends = friendTrie.get(usernameInput);
    for(unsigned int i = 0; i < possibleFriends.size(); ++i) {
        if(possibleFriends[i]->getLower() == usernameInput) {
            theFriend = possibleFriends[i];
            i = possibleFriends.size();
        }
    }

    // Display corresponding results
    if(theFriend == nullptr) {
        centerText(dataWindow, y * 0.7, "Friend not found :(");
        centerText(dataWindow, y * 0.7 + 1, "Press any key to continue");
        wrefresh(dataWindow);
        getch();
    }
    else {
        // initialize some information to be used in loop
        curs_set(0);
        keypad(topWindow, true);

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
            werase(topWindow);
            wattron(topWindow, COLOR_PAIR(2));
            wattron(topWindow, A_REVERSE);
            centerText(topWindow, 0, "Use arrows to scroll, 'q' to quit");
            centerText(topWindow, 2, "-------------------- User Info  --------------------");
            mvwprintw(topWindow, 3, 0, border.c_str());
            wattroff(topWindow, COLOR_PAIR(2));
            wattron(topWindow, COLOR_PAIR(1));
            mvwprintw(topWindow, 4, 0, "Username: %s", theFriend->getUsername().c_str());
            mvwprintw(topWindow, 5, 0, "Name    : %s", theFriend->getName().c_str());
            mvwprintw(topWindow, 6, 0, "Bio     : %s", theFriend->getBio().c_str());
            wattroff(topWindow, COLOR_PAIR(1));
            wattron(topWindow, COLOR_PAIR(2));
            centerText(topWindow, 8, "-------------------- Posts  --------------------");
            mvwprintw(topWindow, 9, 0, border.c_str());
             wattroff(topWindow, COLOR_PAIR(2));
            wattron(topWindow, COLOR_PAIR(1));
            for(int i = 0; i < yMax; ++i) {
                mvwprintw(topWindow, i + 11, 0, "%s", postInfo[index + i].c_str());
            }
            wattroff(topWindow, COLOR_PAIR(1));
            wattroff(topWindow, A_REVERSE);
            wrefresh(topWindow);

            // Get next character for scrolling
            input = wgetch(topWindow);
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
    delwin(topWindow);
    delwin(inputWindow);
    delwin(dataWindow);
}

/* This screen will allow you to edit your bio to fit your liking
*/
//f10
void GUI::editProfileScreen() {

    erase(); 
    refresh(); 
    int x, y; 
    getmaxyx(stdscr, y, x); 
    //top and bottom windows based on the get max returns
    WINDOW* topDisplay        = newwin(y * 0.625 - 4, x - 14, 2, 7); 
    WINDOW* bottomMenuDisplay = newwin(y * 0.25, x - 10, y * 0.625 + 3, 5); 
    WINDOW* topBox            = newwin(y * 0.625, x - 10, 0, 5); 
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

    bioString = userInput(bioWindow, 104);

    if(bioString != EXIT_STR) {
        currUser->setBio(bioString);
        std::string newBioString = currUser->getBio();
        mvwprintw(topDisplay, 12, 0, "New Bio: %s", newBioString.c_str());  
        wrefresh(topBox);
        wrefresh(topDisplay);
        refresh();
    }
    // Clear
    delwin(topDisplay);
    delwin(bottomMenuDisplay);
    delwin(topBox);
    delwin(bioWindow);
}

/* This screen allows you to remove a friend by username
*/
//f11
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

	centerText(topWindow, 0, "Enter friend's USERNAME below");
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

    int ch = 0;
    do {

        // User input begin
        if(ch == 27) { // esc
            delwin(topWindow);
            delwin(inputWindow);
            delwin(dataWindow);
            return;
        }
        else if(ch == 127) { // delete
            if(xCurr > xMin) {
                mvwaddch(inputWindow, 0, --xCurr, ' ');
                if(usernameInput.size() > 0) usernameInput.pop_back();
            }
        }
        else if(isalpha(ch) || ch == ' ') {
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
    } while(ch != 10); // != enter

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
    curs_set(0);
    refresh();
    wgetch(dataWindow);
    
    // cleanup
    delwin(topWindow);
    delwin(inputWindow);
    delwin(dataWindow);
}

//f12
int GUI::menu_setup(WINDOW* w, const std::string inputArray[], int n){ 
    int choice = 0;
    int h = 1;
    int y, x; 
    getmaxyx(stdscr, y, x); 
    print_menu(w, h, n, inputArray);
    while(choice == 0){
        int c  = wgetch(w); 
        choice = menu_selector(n, c, &h, y - 1, 5);  
        print_menu(w, h, n, inputArray);
    }
    return choice; 
}

//f13
void GUI::print_menu(WINDOW *w, int h, int n, const std::string s[]) {

    int x = 2, y = 3;
    box(w, 0, 0); 
    mvwprintw(w, 1, 1, "PRESS ENTER TO SELECT AN OPTION BELOW:"); 
    mvwprintw(w, 2, 1, "--------------------------------------"); 

    for (int i = 0; i < n; ++i){
        if(h == i + 1) { //highlighter = present choice
            wattron(w, A_REVERSE);
            mvwprintw(w, y, x, "%s", s[i].c_str());
            wattroff(w, A_REVERSE); 
        }   
        else mvwprintw(w, y, x, "%s", s[i].c_str()); 
        y++; 
    }
    wrefresh(w); 
}

//f14
int GUI::menu_selector(int n, int c, int* highlight, int a, int b){
    int choice = 0; 
    switch(c) {
        case KEY_UP:
            if(*highlight == 1) *highlight = n; 
            else (*highlight)--; 
            break; 
        case KEY_DOWN: 
            if(*highlight == n) *highlight = 1; 	
            else (*highlight)++; 
            break; 
        case 10: // 10 = int for enter
            choice = *highlight; 
            return choice; 
        case 'q':
            return 'q';
        default:
            mvwprintw(stdscr, a, b,  "Press enter to select");
            refresh(); 
            break; 
    }
    return 0; 
}

//f15
GUI::Type GUI::submit_selection(WINDOW* w, int choice){
    switch(choice){
        case 1:
            return sandwich::GUI::Type::POST_TO_WALL;
            break;	
        case 2: 
            return sandwich::GUI::Type::FRIEND_LIST;
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
            mvwprintw(w, 10, 8, "Press enter to select");
            wrefresh(w); 
            break; 
    }
    return sandwich::GUI::Type::HOME; 
}

//centers text in the input window
//f16
void GUI::centerText(WINDOW* w, int yLoc, std::string text){
    int indent = getmaxx(w) - text.size();
    indent /= 2;
    mvwprintw(w, yLoc, indent, text.c_str()); 	
}


//returns the center y location of the window
//f17
int GUI::centerY(WINDOW *w){
    return getmaxy(w) / 2;
}

//returns the center x location of the window
//f18
int GUI::centerX(WINDOW *w){
    return getmaxx(w) / 2;
}

//f19
std::string GUI::userInput(WINDOW* w, int max) {

    std::string inputStr;
    char ch   = 0;
    int yCurr = 0, xCurr = 0;
    int xMax  = getmaxx(w);
    int yMax  = getmaxy(w);

    while(ch != 10) {
        ch = wgetch(w);
        if(ch == 27) { // ESC
            return EXIT_STR;
        }
        else if(ch == 127) { // backspace
            
            xCurr--;
            if(xCurr < 0 && yCurr > 0) {
                xCurr = xMax - 1;
                yCurr--;
            }
            if(xCurr < 0) xCurr = 0;
            if(yCurr < 0) yCurr = 0;
            mvwprintw(w, yCurr, xCurr, " ");
            wmove(w, yCurr, xCurr);
            if(inputStr.size() > 0) inputStr.pop_back();
        }
        else if(inputStr.size() >= max);
        else if(xCurr < xMax && yCurr < yMax){
            mvwprintw(w, yCurr, xCurr++, "%c", ch);
            if(xCurr >= xMax) {
                xCurr = 0;
                yCurr++;
            }
            wmove(w, yCurr, xCurr);
            inputStr += ch;
        }
        wrefresh(w);
    }
    inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), '\n'), inputStr.end());
    return inputStr; 
}

	
//f20
void GUI::memberListSetup(){
    //create a start user for testing
    std::string username = "jack";
    sandwich::User* tester = new sandwich::User("jack", "name", "bio"); 
    //create insert the username into the Map paired with the tester
    userMap.insert({tester->getLower(), tester});
    //store the user in the trie by its user name
    trie.store("jack", tester); 
    //trie.store(tester->getName(),     tester); 

    sandwich::User* friend1 = new sandwich::User("fred", "Freddy G", "I love singing!");
    userMap.insert({friend1->getLower(), friend1});
    trie.store(friend1->getUsername(), friend1);

    sandwich::User* friend2 = new sandwich::User("leroy", "LeRoy B", "I'm the real OG");
    userMap.insert({friend2->getLower(), friend2});
    trie.store(friend2->getUsername(), friend2);

    sandwich::User* tester2 = new sandwich::User("becky", "Rebecca L", "Becky with the good hair"); 
    userMap.insert({tester2->getLower(), tester2});
    trie.store("becky", tester2); 

    sandwich::User* friend3 = new sandwich::User("benny", "Benjamin F", "OG of electriCity"); 
    userMap.insert({friend3->getLower(), friend3}); 
    trie.store(friend3->getUsername(), friend3);

    tester2->addFriend(friend1);
    tester2->addFriend(friend3);


    // LOTS OF RANDOM non-friends FOR THE NETWORK
    sandwich::User* user1 = new sandwich::User("carol", "Carolina Smith", "I secretly a cat lady");
    userMap.insert({user1->getLower(), user1});
    trie.store(user1->getUsername(), user1);

    sandwich::User* user2 = new sandwich::User("jemima", "Aunt Jemima", "I'll creep on your page and tell you parents about everything you post but I make delicious pancakes");
    userMap.insert({user2->getLower(), user2});
    trie.store(user2->getUsername(), user2);

    sandwich::User* user3 = new sandwich::User("thepitt", "Brad Pitt", "I'm getting old but I'm still a  #totalbabe");
    userMap.insert({user3->getLower(), user3});
    trie.store(user3->getUsername(), user3);

    sandwich::User* user4 = new sandwich::User("saltbae", "Nusaret", "I'm instafamous #saltlife");
    userMap.insert({user4->getLower(), user4});
    trie.store(user4->getUsername(), user4);


    sandwich::User* user5 = new sandwich::User("thedonald", "Donald J. Trump", "Little keyboards are greeeaat for my little hands");
    userMap.insert({user5->getLower(), user5});
    trie.store(user5->getUsername(), user5);

    sandwich::User* user6 = new sandwich::User("billyg", "Bill Gate", "I'm riiiiiiiiich "); 
    userMap.insert({user6->getLower(), user6});
    trie.store(user6->getUsername(), user6);

    sandwich::User* user7 = new sandwich::User("biebs", "Justin Bieber", "I'm a belieber"); 
    userMap.insert({user7->getLower(), user7});
    trie.store(user7->getUsername(), user7);

    sandwich::User* user8 = new sandwich::User("yonce", "Queen Bey", "If you like it then you shoulda putta ring on it");    
    userMap.insert({user8->getLower(), user8});
    trie.store(user8->getUsername(), user8);
    
    tester->addFriend(friend1);
    tester->addFriend(friend2);
    tester->addFriend(user1);
    tester->addFriend(user2);
    tester->addFriend(user3);
    tester->addFriend(user4);
    tester->addFriend(user5);
    tester->addFriend(user6);
    tester->addFriend(user7);
    tester->addFriend(user8);


    //giving the users some posts
    std::string postInput = "My first default Post" ;
    sandwich::Post post(postInput);
    //currUser->addPost(post);    
    sandwich::User* tempUser;
    for (auto it = userMap.begin(); it != userMap.end(); it++){
        tempUser = userMap[it->first];
        tempUser->addPost(post);
    }
    
    time_t now = time(NULL);
    time_t now2 = time(NULL);

    //delay script
    while (difftime(now2, now) == 0)  now2 = time(NULL);
    
    sandwich::Post post1("OMG I like tacos and pizza");
    friend1->addPost(post1);

    while (difftime(now2, now) == 0)  now2 = time(NULL);
    sandwich::Post post2("I can't believe it's not butter");
    friend2->addPost(post2);

    while (difftime(now2, now) == 0)  now2 = time(NULL);
    sandwich::Post post3("Soccer game at 10! See you there!");
    friend1->addPost(post3); 


}

//f21
void GUI::checkScreenSize(){
    int y, x;
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
