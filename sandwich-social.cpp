
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
    std::vector<sandwich::User*>		     IOusers = fileIO.readUsers();
    std::vector<std::vector<std::string>> 	     IOfriends = fileIO.readFriends();


    //puts friend data into users
    for(unsigned int IOcounter = 0; IOcounter < IOfriends.size(); IOcounter++){				 //iterate vct strings
    	for(unsigned int IOcounter2 = 0; IOcounter2 < IOusers.size(); IOcounter2++){			 //iterate vct users
	    if(IOfriends[IOcounter][0] == IOusers[IOcounter2]->getUsername()){				 //username matches first string
	     	for(unsigned int IOcounter3 = 1; IOcounter3 < IOfriends[IOcounter].size(); IOcounter3++){//iterate friends
		    for(unsigned int IOcounter4 = 0; IOcounter4 < IOusers.size(); IOcounter4++){	 //iterate users
			if(IOfriends[IOcounter][IOcounter3] == IOusers[IOcounter4].getUsername()){	 //friend matches username
			     IOusers[IOcounter2]->addFriend(IOusers[IOcounter4]);			 //IOfriends[IOcounter][IOcounter3] is a string
		     	}
		    }
	        }
	    }
        }
    }

    userMap.insert({->getLower(), });//adds users into map

    for(IOcounter = 0;IOcounter < IOusers.size(); IOcounter++){//adds users into trie
    	trie.add(IOusers[IOcounter]->getUsername());
	trie.add(IOusers[IOcounter]->getName());
	trie.store(IOusers[IOcounter]->getUsername(), IOusers[IOcounter]);
	trie.store(IOusers[IOcounter]->getName(), IOusers[IOcounter]);
    }



    sandwich::User* currUser;

    sandwich::GUI gui(userMap, trie, currUser);
    gui.checkScreenSize();
    gui.memberListSetup();

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
    
    return 0;
}
