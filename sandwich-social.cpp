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
    

    // TODO: Login user, set the currUser.
    
    // TODO: Get each menu working
    
    // TODO: On exit / quit command, write user and friend data
    //       to a file then actually quit.

    return 0;
}
