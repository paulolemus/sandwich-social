/* File: FileIO.h
 * Name:
 * Team: Sandwich
 * Date: 4/22/2017
 */

/* This file contains a class that is used to read
 * from and write to a file all the information of the
 * users. It will allow us to populate the program with
 * users upon creation with a dat file, and then save all
 * users and changes back to the dat file upon exit.
 *
 * FORMAT:
 *
 *
 */

#ifndef SANDWICH_FILEIO_H_
#define SANDWICH_FILEIO_H_

#include <fstream>
#include <string>
#include <vector>
#include "User.h"

namespace sandwich {

class FileIO {

    std::string userFileName;
    std::string friendsFileName;

public:

    FileIO();
    FileIO(std::string userFileName, std::string friendsFileName);

    // Getters / Setters for filenames
    std::string getUserFileName()    const;
    std::string getFriendsFileName() const;
    void        setUserFileName   (const std::string userFileName);
    void        setFriendsFileName(const std::string friendsFileName);

    /* Read User:
     * Creates new users and populates it with
     * information from the file. It then returns 
     * a vector of pointers to the newly created users.
     */
    std::vector<sandwich::User*> readUsers();
    /* readFriends:
     * Returns a vector of strings with the user
     * who the friends belong to, followed by the user's
     * friends
     */
    std::vector<std::string> readFriends();

    /* This takes a pointer to a user and then writes
     * all of its information to a text file.
     */
    void writeUser(const sandwich::User* const user);
    /* Given a user, write all its friends usernames to
     * a text file
     */
    void writeFriends(const sandwich::User* const user);
};


FileIO::FileIO() {}

FileIO::FileIO(std::string userFileName, std::string friendsFileName) :
    userFileName(userFileName), friendsFileName(friendsFileName) {}


// Getters / Setters for filenames
std::string FileIO::getUserFileName() const { return userFileName; }
std::string FileIO::getFriendsFileName() const { return friendsFileName; }

void FileIO::setUserFileName(const std::string userFileName) {
    this->userFileName = userFileName;
}
void FileIO::setFriendsFileName(const std::string friendsFileName) {
    this->friendsFileName = friendsFileName;
}

std::vector<sandwich::User*> FileIO::readUsers() {
    
    std::vector<sandwich::User*> users;
    std::string s1;
    ifstream() myfile("users.dat");

    getline(myfile, s1);
    while(s1 != END_FILE){
	    if(s1 == "START_POSTS"){//post branch ends when END_POSTS
	    	getline();
		while(s1 != END_POSTS){
			
		}
	    }
	    else{
		//save usernam
		//save name
		//save bio
		//push onto vector
		//getline()    
	    }
	    getline();
    }

    sandwich::User* user = new User();
    return users;
}

std::vector<std::string> FileIO::readFriends() {

    std::vector<std::string> friendList;
    return friendList;
}

void FileIO::writeUser(const sandwich::User* const user) {

}
void FileIO::writeFriends(const sandwich::User* const user) {

}


} // namespace sandwich

#endif // SANDWICH_FILEIO_H_
