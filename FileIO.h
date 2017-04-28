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
#include <iostream>

namespace sandwich {


bool validuser(std::string a, std::string b, std::string c){
    if(a.substr(0,10) == "username: "){
	if(b.substr(0,10) == "name    : "){
            if(c.substr(0,10) == "bio     : "){
	     	return 1;
	    }
	}
    }
    return 0;
}

std::vector<std::string> extract(std::string a, std::string b, std::string c){
	std::vector<std::string> v1;
	std::string vs1, vs2, vs3;
	
    vs1 = a.substr(10);
    vs2 = b.substr(10);
    vs3 = c.substr(10);
    v1.push_back(vs1);
    v1.push_back(vs2);
    v1.push_back(vs3);
    
    return v1;
}


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
    std::string s1, s2, s3;
    std::vector<std::string> v1;
    std::ifstream myfile("users.dat");

    if(myfile){//if file exists
    while(getline(myfile, s1)){//getline until end of file
	if(s1.empty() == 0){//skip empty lines
	    /*if(s1 == "START_POSTS"){//post branch ends when END_POSTS
	    	
		while(s1 != END_POSTS){
		}
	    }*/
	   //	 else{//reading user fields
		     getline(myfile, s2);
		     getline(myfile, s3);
		     if(validuser(s1, s2, s3)){
		     	v1 = extract(s1,s2,s3);
			sandwich::User* U = new User(v1[0],v1[1],v1[2]);
			users.push_back(U);
		     }else{
		     	std::cout << "ERROR: INVALID USER DATA" << std::endl;
		     }	     
			// }
			//check valid username
			//check valid name
			//check valid bio
			//make user
			//push onto vector    
	      }
	 }
	 myfile.close();//close file
    }    
	
    else{
    	std::cout << "ERROR: FILE NOT FOUND" << std::endl;
    
    }
    return users;
}

std::vector<std::string> FileIO::readFriends() {

    std::vector<std::string> friendList;
    return friendList;
}

void FileIO::writeUser(const sandwich::User* const user) {

    // 1. Open new file or open a file to overwrite.
    // 2. For each pointer in the vector of pointers:
    //      a. cat the username on the end of a string "username: <username>"
    //      b. do the same for name and bio
    //      c. Write those for file.
    //      d. Write the string START_POSTS:
    //      e. Get the user's vector of posts.
    //      f. For each post, write the contents and timestamp.
    //      g. Write END_POSTS\n\n
    // 3. Repeat from 1 until all users have been written.
    //    This should actually be easier than read.

}
void FileIO::writeFriends(const sandwich::User* const user) {

    // 1. For each user in vector:
    // 2. Write username followed by a : and newline
    // 3. Get the vector of friends
    // 4. For each friend in the vector of friends:
    //      a. Write their usernames on newlines.
    // 5. Write a newline to file.
    // 6. Repeat from 2 until all users have been written.
}


} // namespace sandwich

#endif // SANDWICH_FILEIO_H_
