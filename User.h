/* File: User.h
 * Name: Paulo Lemus
 * Date: 4/13/2017
 * Team: Sandwich
 * Members: Paulo L, Jessie G, Matt Y
 */

/* User class is used to store all information about a user.
 * They have several fields:
 * 1. Username
 * 2. Name
 * 3. Bio
 * 4. Post History
 * 5. Friends
 */

/* posts:
 * We are going under the assumption that posts are never deleted.
 * The last post is always the most recent.
 */

/* Friends:
 * We are going to assume that friends cannot delete their accounts.
 * They always, exist, so we do not have to worry about a pointer to
 * a deleted user.
 * When adding a friend, we pass in the friend. If the friend 
 * already exists, we do not add him/her.
 */

#ifndef EE205_FINAL_USERS_H_
#define EE205_FINAL_USERS_H_


#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>
#include "Post.h"

namespace sandwich {

class User {

    std::string username;
    std::string name;
    std::string bio;
    
    std::vector<sandwich::Post>  posts;
    std::vector<sandwich::User*> friends;

public:
    // Constructor
    User();
    User(const std::string& username, 
         const std::string& name,
         const std::string& bio);

    // Getters / Setters
    std::string& getUsername() const;
    std::string& getName()     const;
    std::string& getBio()      const;
    bool setUsername(std::string& username);
    bool setName    (std::string& name);
    bool setBio     (std::string& bio);
    
    // Post operations
    bool addPost   (const std::string& post);
    bool addPost   (const Post& post);
    bool removePost(const Post& post);

    // Friend operations
    bool addFriend   (const User* user);
    bool removeFriend(const User* user);
    bool hasFriend   (const User* user);

    // Special
    static bool validateUsername(const std::string& name);
    bool operator== (const User& left, const User& right) const;

};

/////////////////////////////////////////////////////////

User::User() {}
User::User(
    const std::string& username,
    const std::string& name,
    const std::string& bio
    ) : username(username), name(name), bio(bio) {}

std::string& User::getUsername() const { return username; }
std::string& User::getName()     const { return name; }
std::string& User::getBio()      const { return bio; }

bool User::setUsername(std::string& str) {

    // Guard invalid && convert to lower
    for(unsigned int i = 0; i < str.size(); ++i) {
        if(!isalpha( str[i] ) && str[i] != ' ') return false;
        else if(str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    }
    username = str;
    return true;
}

bool User::setName(std::string& str) {
    
    // Guard invalid && conver to lower
    for(unsigned int i = 0; i < str.size(); ++i) {
        if(!isalpha( str[i] ) && str[i] != ' ') return false;
        else if(str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    }
    name = str;
    return true;
}

bool User::setBio(std::string& str) {
    
    // Guard invalid && conver to lower
    for(unsigned int i = 0; i < str.size(); ++i) {
        if(!isalpha( str[i] ) && str[i] != ' ') return false;
        else if(str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    }
    bio = str;
    return true;
}


bool User::addPost(const std::string& post) {
    posts.push_back(Post(post));
}
bool User::addPost(const Post& post) {
    post.push_back(post);
}


// Check if we already have this friend. If we do,
// then we do not add user. Otherwise, add user.
bool User::addFriend(const User* user) {
    for(auto ptr : friends) {
        if(*ptr == *user) return false;
    }
    friends.push_back(user);
    return true;
}

bool removeFriend(const User* user) {
    
    bool isRemoved = false;
    for(unsigned int i = 0; i < friends.size(); ++i) {
        if(*user == *friends[i]) {
            friends.erase( friends.begin() + i );
            isRemoved = true;
        }
    }
    return isRemoved;
}

bool hasFriend(const User* user) {
    for(auto ptr : friends) {
        if(*ptr == *user) return true;
    }
    return false;
}



// validateString:
// Given a string, it will return true if the string only
// contains alpha characters and/or spaces
static bool validateString(const std::string& key) {
    for(unsigned int i = 0; i < key.size(); ++i) {
        if(!isalpha(key[i]) && key[i] != ' ') return false;
    }
    return true;
}

// Used to check if two accounts are equal to each other
bool User::operator== (const User& left, const User& right) const {
    if((left.username == right.username) &&
        left.name     == right.name) {
        return true;
    }
    else return false;
}

} // namespace sandwich

#endif // EE205_FINAL_USERS_H_
