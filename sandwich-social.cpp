
/* File: sandwich-social.cpp
 * Name: Paulo L, Jessie G, Matt Y
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

#include "FileIO.h"
#include "Trie.h"
#include "Post.h"
#include "User.h"
#include "GUI.h"
#include "FileIO.h"

int main() {

    /* userMap will hold usernames as keys and User* as values.
     * The trie is used for autocompletion and User* retrieval.
     * The FileIO is used to parse in all data from text and 
     * to write all data to text.
     * The currUser is a pointer to the currernt user who is logged in.
     */
    std::unordered_map<std::string, sandwich::User*> userMap;
    sandwich::Trie<sandwich::User*>                  trie;
    sandwich::FileIO                                 fileIO("users.dat", "friends.dat");

    // Loop to populate map and trie with users from file
    {
        std::vector<sandwich::User*>          IOusers   = fileIO.readUsers();
        std::vector<std::vector<std::string>> IOfriends = fileIO.readFriends();

        // Add to map
        for(auto userPtr : IOusers) {
            userMap[userPtr->getLower()] = userPtr;
            trie.store(userPtr->getUsername(), userPtr);
            trie.store(userPtr->getName(),     userPtr);
        }

        // Update all user's friends
        for(unsigned int i = 0; i < IOfriends.size(); ++i) {
            std::string topUsername = sandwich::User::lowercaseify(IOfriends[i][0]);
            sandwich::User* topUser = nullptr;

            // Get the current user to add the friends to
            auto topUserMatches = trie.get(topUsername);
            for(unsigned int j = 0; j < topUserMatches.size(); ++j) {
                if(topUserMatches[j]->getLower() == topUsername) {
                    topUser = topUserMatches[j];
                    j = topUserMatches.size();
                }
            }

            // If the top user exists and has friends, add all of them to user's friend list
            if(topUser != nullptr && IOfriends[i].size() > 1) {
                for(unsigned int j = 1; j < IOfriends[i].size(); ++j) {
                    std::string friendUsername = sandwich::User::lowercaseify(IOfriends[i][j]);
                    sandwich::User* friendPtr  = nullptr;
                    auto friendMatches = trie.get(friendUsername);

                    for(unsigned int k = 0; k < friendMatches.size(); ++k) {
                        if(friendMatches[k]->getLower() == friendUsername) {
                            friendPtr = friendMatches[k];
                            k = friendMatches.size();
                        }
                    }
                    if(friendPtr != nullptr) {
                        topUser->addFriend(friendPtr);
                    }
                }
            }
        }
    }

    // Current user who is logged in
    sandwich::User* currUser;

    sandwich::GUI gui(userMap, trie, currUser);
    gui.checkScreenSize();

    // This is the start of the GUI. This login screen is the initial login that
    // sets the current user or creates a new one if needed.
    // The while loop is what will loop through each window until the user decided to 
    // quit the program.
    sandwich::GUI::Type nextScreen = gui.loginScreen();
    while(nextScreen != sandwich::GUI::Type::QUIT) {

        while(nextScreen != sandwich::GUI::Type::LOGOUT &&
              nextScreen != sandwich::GUI::Type::QUIT) {

            nextScreen = gui.homeScreen();
            switch(nextScreen) {

                case sandwich::GUI::Type::POST_TO_WALL:
                    gui.postWallScreen();
                    break;
                case sandwich::GUI::Type::FRIEND_LIST:
                    gui.friendListScreen();
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
            }
        }
        if(nextScreen == sandwich::GUI::Type::LOGOUT) {
            nextScreen = gui.loginScreen();
        }
    }
    // TODO: Write all users and friends to file:
    
    {
        auto IOusers = trie.getComplete();
        
        std::ofstream outfile("users.dat", std::ofstream::out);
        outfile.close();
        outfile.open("friends.dat", std::ofstream::out);
        outfile.close();

        for(unsigned int counter = 0; counter < IOusers.size(); counter++){
            fileIO.writeUser(IOusers[counter]);
        fileIO.writeFriends(IOusers[counter]);
        }
    }

    return 0;
}
