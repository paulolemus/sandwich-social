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
#include <queue>
#include "User.h"
#include <iostream>

namespace sandwich {

class FileIO {

    std::string userFileName;
    std::string friendsFileName;
    const std::string validusername = "username: ";
    const std::string validname     = "name    : ";
    const std::string validbio      = "bio     : ";
    const std::string validpost     = "POST: ";
    const std::string validtime     = "TIME: ";
    const std::string endpostflag   = "END_POSTS";
    const char fuserflag            = ':';

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
     * Returns a vector of vectors of strings with the user
     * who the friends belong to, followed by the user's
     * friends
     */
    std::vector<std::vector<std::string>> readFriends();

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
    std::queue<std::string> que;
    std::ifstream myfile(userFileName);

    if(myfile){//if file exists
    while(!myfile.eof() || !que.empty()){//getline until end of file
	
	if(que.empty()){
	getline(myfile, s1);
	}else{
	s1 = que.front();//get from queue
	que.pop();
	}

	if(s1.substr(0,validusername.size()) == validusername){
	    
	    if(que.empty()){
	    getline(myfile, s2);
	    }else{
	    s2 = que.front();//get from queue
	    que.pop();
	    }

	    if(s2.substr(0,validname.size()) == validname){
	        
		if(que.empty()){
		getline(myfile, s3);
		}else{
		s3 = que.front();//get from stack
		que.pop();
		}

		if(s3.substr(0,validbio.size()) == validbio){//valid user
		  
		    s1 = s1.substr(validusername.size());//extract substrings
	    	    s2 = s2.substr(validname.size());
		    s3 = s3.substr(validbio.size());	    
		    sandwich::User* U = new User(s1, s2, s3);
		    users.push_back(U);//create new user and add to vector 
		    
		    while(s1 != endpostflag){//post loop
		        
			if(que.empty()){
			getline(myfile, s1);
			}else{
			s1 = que.front();
			que.pop();
			}

			if(s1.substr(0,validpost.size()) == validpost){
			    
			    if(que.empty()){
			    getline(myfile, s2);
			    }else{
			    s2 = que.front();
			    que.pop();
			    }

			    if(s2.substr(0,validtime.size()) == validtime){//valid post

			        s1 = s1.substr(validpost.size());//extract substrings
				s2 = s2.substr(validtime.size());
				U->addPost({s1,s2});//new post
				
			    }else{
			    	que.push(s2);
			    }
			}
		    }
		}else{
		    que.push(s2);//enqueue both
	    	    que.push(s3);	    
		}
	    }else{
	 	que.push(s2);//enqueue
	    }
	}
	 }
	 myfile.close();//close file
    }    
	
    else{
    	std::cout << "ERROR: FILE NOT FOUND" << std::endl;
    
    }
    return users;
}

std::vector<std::vector<std::string>> FileIO::readFriends() {

    std::vector<std::vector<std::string>> friendList;
    std::vector<std::string> friendtemp;
    std::string s1;
    std::ifstream myfile(friendsFileName);
   friendtemp.clear(); 

    if(myfile){
	while(!myfile.eof()){
	    getline(myfile, s1);
	    if(s1.size()){//skip blank lines
	    	if(s1[s1.size() - 1] == fuserflag){//new user
		     if(friendtemp.size()){//if friendtemp is not empty
		     	friendList.push_back(friendtemp);//push temp vector of strings
		     }
		     friendtemp.clear();//clear temp vector
		     s1 = s1.substr(0, s1.size() - 1);//get rid of : at end
		     friendtemp.push_back(s1);//push onto temp vector
	    	}else{
		     friendtemp.push_back(s1);//puhs onto temp vect
	    	}
	    }
	}
	if(friendtemp.size()){//if temp vector is not empty
		friendList.push_back(friendtemp);
	}
    

	myfile.close();
    }else{
    	std::cout << "ERROR: FILE NOT FOUND" << std::endl;
    }
    
    return friendList;
}

void FileIO::writeUser(const sandwich::User* const user) {
    
     std::ofstream myfile;

     if(myfile){
     
     }else{
     	std::cout << "ERROR: FILE NOT FOUND" << std::endl;
     }
}

void FileIO::writeFriends(const sandwich::User* const user) {

}


} // namespace sandwich

#endif // SANDWICH_FILEIO_H_
