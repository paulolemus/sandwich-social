/*
 *
 *
 */

/*
 *
 *
 *
 */

#ifndef SANDWICH_GUI_H_
#define SANDWICH_GUI_H_

#include <ncurses.h>
#include <unordered_map>
#include "User.h"
#include "Trie.h"

namespace sandwich {

class GUI {

    std::unordered_map<std::string, sandwich::User*>& userMap;
    sandwich::Trie<sandwich::User*>&                  trie;
    sandwich::User*&                                  currUser;

public:
    enum class Type : int {
        HOME,
        POST_TO_WALL,
        VIEW_FRIENDS,
        ADD_FRIEND,
        VIEW_FRIEND,
        REMOVE_FRIEND,
        EDIT_PROFILE,
        LOGOUT,
        QUIT
    };

    GUI(std::unordered_map<std::string, sandwich::User*>& userMap,
        sandwich::Trie<sandwich::User*>&                  trie,
        sandwich::User*&                                  currUser);

    
    Type loginScreen();
    Type homeScreen();

    void postWallScreen();
    void viewFriendsScreen();
    void addFriendsScreen();
    void viewFriendScreen();
    void editProfileScreen();
    void removeFriendScreen();

    void testFunc();
};

GUI::GUI(std::unordered_map<std::string, sandwich::User*>& userMap,
         sandwich::Trie<sandwich::User*>&                  trie,
         sandwich::User*&                                  currUser) :
    userMap(userMap),
    trie(trie),
    currUser(currUser) {}

GUI::Type GUI::loginScreen() {

}
GUI::Type GUI::homeScreen() {

}

void GUI::postWallScreen() {

}
void GUI::viewFriendsScreen() {

}
void GUI::addFriendsScreen() {

}
void GUI::viewFriendScreen() {

}
void GUI::editProfileScreen() {

}
void GUI::removeFriendScreen() {

}

void GUI::testFunc() {

    std::string username = "Test username";
    currUser = new User();
    currUser->setUsername(username);

    trie.store(currUser->getUsername(), currUser);
    userMap[currUser->getLower()] = currUser;
}


} // namespace sandwich

#endif // SANDWICH_GUI_H_
