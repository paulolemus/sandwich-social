/* File paulo-test.cpp
 *
 * A test driver for program
 */

#include <iostream>
#include <unordered_map>
#include <vector>

#include <ncurses.h>

#include "GUI.h"
#include "Trie.h"
#include "Post.h"
#include "User.h"

int main(int argc, char** argv) {

    std::unordered_map<std::string, sandwich::User*> userMap;
    sandwich::Trie<sandwich::User*>                  trie;

    sandwich::User* currUser;

    sandwich::GUI gui(userMap, trie, currUser);

    // Login screen to begin program
    sandwich::GUI::Type nextScreen = gui.loginScreen();

    while(nextScreen != sandwich::GUI::Type::QUIT) {

        while(nextScreen != sandwich::GUI::Type::LOGOUT) {
            nextScreen = gui.homeScreen();
            switch(nextScreen) {

                case sandwich::GUI::Type::POST_TO_WALL:
                    gui.postWallScreen();
                    break;
                case sandwich::GUI::Type::VIEW_FRIENDS:
                    gui.viewFriendsScreen();
                    break;
                case sandwich::GUI::Type::ADD_FRIEND:
                    gui.addFriendScreen();
                    break;
                case sandwich::GUI::Type::EDIT_PROFILE:
                    gui.editProfileScreen();
                    break;
                case sandwich::GUI::Type::VIEW_FRIEND:
                    gui.viewFriendScreen();
                    break;
                case sandwich::GUI::Type::REMOVE_FRIEND:
                    gui.removeFriendScreen();
                    break;
                case sandwich::GUI::Type::HOME:
                case sandwich::GUI::Type::LOGOUT:
                case sandwich::GUI::Type::QUIT:
                    break; 
                default:
                    std::cout << "enum not working\n\n"; 
            } // homescreen loop
        } // loginscreen loop
        if(nextScreen == sandwich::GUI::Type::LOGOUT) {
            nextScreen = gui.loginScreen();
        }
    }
    getch(); 
    return 0;
}
