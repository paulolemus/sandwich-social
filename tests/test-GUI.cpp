/* 
 *
 */

#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include "User.h"
#include "GUI.h"

TEST(GUI, compiles) {
    ASSERT_TRUE(true);
}

TEST(GUI, constructor) {

    std::unordered_map<std::string, sandwich::User*> userMap;
    sandwich::Trie<sandwich::User*> trie;
    sandwich::User* user;

    sandwich::GUI gui(userMap, trie, user);
}

TEST(GUI, testFunction) {

    std::unordered_map<std::string, sandwich::User*> userMap;
    sandwich::Trie<sandwich::User*> trie;
    sandwich::User* user;

    std::string username = "test username";

    sandwich::GUI gui(userMap, trie, user);
    gui.testFunc();

    ASSERT_EQ(user->getLower(), username);
    ASSERT_TRUE(trie.search(username));
    ASSERT_TRUE(userMap[user->getLower()] == user);
    
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
