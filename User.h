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

    const std::string username;
    const std::string name;
    std::string bio;
    
    std::vector<sandwich::Post>        posts;
    std::vector<const sandwich::User*> friends;

public:
    // Constructor
    User(const std::string& username, 
         const std::string& name,
         const std::string& bio);

    // Getters / Setters
    const std::string& getUsername() const;
    const std::string& getName()     const;
    const std::string& getBio()      const;
    std::string        getLower()    const;

    void setBio(std::string& bio);
    
    // Post operations
    void addPost   (const std::string& post);
    void addPost   (const Post& post);
    void removePost(const Post& post);
    std::vector<sandwich::Post> getPosts();

    // Friend operations
    bool addFriend   (const User* user);
    bool removeFriend(const User* user);
    bool hasFriend   (const User* user);
    std::vector<const sandwich::User*> getFriends();

    // Special
    static bool validateStr(const std::string& str);
    bool operator== (const User& other) const;
    bool operator<  (const User& other) const;

};

////////////////////////////////////////////////////////
//                  IMPLEMENTATIONS                   //
////////////////////////////////////////////////////////

User::User(
    const std::string& username,
    const std::string& name,
    const std::string& bio
    ) : username(username), name(name), bio(bio) {}

const std::string& User::getUsername() const { return username; }
const std::string& User::getName()     const { return name; }
const std::string& User::getBio()      const { return bio; }
std::string        User::getLower()    const {

    std::string lower = username;
    // Convert to lower case
    for(unsigned int i = 0; i < lower.size(); ++i) {
        if(lower[i] >= 'A' && lower[i] <= 'Z') {
            lower[i] = lower[i] + 32;
        }
    }
    return lower;
}

void User::setBio(std::string& str) {
    bio = str;
}


void User::addPost(const std::string& post) {
    posts.push_back(Post(post));
}
void User::addPost(const Post& post) {
    posts.push_back(post);
}

void User::removePost(const Post& post) {

    for(unsigned int i = 0; i < posts.size(); ++i) {
        if(posts[i] == post) {
            posts.erase( posts.begin() + i );
        }
    }
}

std::vector<sandwich::Post> User::getPosts() { return posts; }


// Check if we already have this friend. If we do,
// then we do not add user. Otherwise, add user.
bool User::addFriend(const User* user) {
    for(auto ptr : friends) {
        if(*ptr == *user) return false;
    }
    friends.push_back(user);
    return true;
}

bool User::removeFriend(const User* user) {
    
    bool isRemoved = false;
    for(unsigned int i = 0; i < friends.size(); ++i) {
        if(*user == *friends[i]) {
            friends.erase( friends.begin() + i );
            isRemoved = true;
        }
    }
    return isRemoved;
}

bool User::hasFriend(const User* user) {
    for(auto ptr : friends) {
        if(*ptr == *user) return true;
    }
    return false;
}

std::vector<const sandwich::User*> User::getFriends() {
    return friends;
}


// validateString:
// Given a string, it will return true if the string only
// contains alpha characters and/or spaces
bool User::validateStr(const std::string& str) {
    for(unsigned int i = 0; i < str.size(); ++i) {
        if(!isalpha(str[i]) && str[i] != ' ') return false;
    }
    return true;
}

// Used to check if two accounts are equal to each other
bool User::operator== (const User& other) const {

    if( this->username.size() != other.username.size() ) {
        return false;
    }
    else {

        char left, right;
        for(unsigned int i = 0; i < other.username.size(); ++i) {
            left  = this->username[i];
            right = other.username[i];
            if(left  >= 'A' && left  <= 'Z') left  += 32;
            if(right >= 'A' && right <= 'Z') right += 32;

            if(left != right) {
                return false;
            }
        }
        return true;

    }
}

bool User::operator< (const User& other) const {

    if(this->username.size() < other.username.size()) {
        return true;
    }
    else if(this->username.size() > other.username.size()) {
        return false;
    }
    else {
        char left, right;
        for(unsigned int i = 0; i < this->username.size(); ++i) {
            left  = this->username[i];
            right = other.username[i];
            if(left  >= 'A' && left  <= 'Z') left  += 32;
            if(right >= 'A' && right <= 'Z') right += 32;

            if(left > right) return false;
        }
        return true;
    }
}


} // namespace sandwich

#endif // EE205_FINAL_USERS_H_
