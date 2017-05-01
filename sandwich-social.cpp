
/* File: sandwich-social.cpp
 * Name:
 * Team: Sandwich
 * Date: 4/22/2017
 */

/* The main driver program for the sandwich social 
 * social networking client.
 */

#include <iostream>
#include <unordered_map>
#include <vector>

#include <ncurses.h>

#include "Trie.h"
#include "Post.h"
#include "User.h"
//#include "FileIO.h"
#include "GUI.h"
//#include "tempGui.h"
int main(int argc, char** argv) {

    /* userMap will hold usernames as keys and User* as values.
     * The trie is used for autocompletion and User* retrieval.
     * The FileIO is used to parse in all data from text and 
     * to write all data to text.
     * The currUser is a pointer to the currernt user who is logged in.
     */
    std::unordered_map<std::string, sandwich::User*> userMap;
    sandwich::Trie<sandwich::User*>                  trie;
    //sandwich::FileIO                                 fileIO;

    sandwich::User* currUser;


    sandwich::GUI gui(userMap, trie, currUser);

    sandwich::GUI::Type nextScreen = gui.loginScreen();

    while(nextScreen != sandwich::GUI::Type::QUIT) {

        while(nextScreen != sandwich::GUI::Type::LOGOUT ||
              nextScreen != sandwich::GUI::Type::QUIT) {

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
                    gui.logoutScreen(); 
//                case sandwich::GUI::Type::QUIT:
                    break; 
                default:
                    std::cout << "enum not working\n\n"; 
            }
        }
        if(nextScreen == sandwich::GUI::Type::LOGOUT) {
            nextScreen = gui.loginScreen();
        }
    }
    getch(); 
    return 0;
}
