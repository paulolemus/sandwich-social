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
#include "FileIO.h"
#include "GUI.h"

int main(int argc, char** argv) {

    /* userMap will hold usernames as keys and User* as values.
     * The trie is used for autocompletion and User* retrieval.
     * The FileIO is used to parse in all data from text and 
     * to write all data to text.
     * The currUser is a pointer to the currernt user who is logged in.
     */
    std::unordered_map<std::string, sandwich::User*> userMap;
    sandwich::Trie<sandwich::User*>                  trie;
    sandwich::FileIO                                 fileIO;

    sandwich::User* currUser;


    // Must have launced program with data file arguments.
    // This can be changed, we can hardcore the strings for the
    // data files if we want
    if(argc < 4) {
        std::cout << "No provided user or friends data files" << std::endl;
        exit(1);
    }

    // TODO: READ IN USERS AND FRIENDS,
    //       POPULATE userMap AND trie

    // TODO: Initialize the NCURSES GUI
    sandwich::GUI gui(userMap, trie, currUser);

    // TODO: Login user, set the currUser.
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
                case sandwich::GUI::Type::LOGOUT:
                case sandwich::GUI::Type::QUIT:
                case default:
                    break;
            }

            nextScreen = gui.loginScreen();
        }

        // TODO: On exit / quit command, write user and friend data
        //       to a file then actually quit.
        // Back to login screen
    }
    return 0;
}
