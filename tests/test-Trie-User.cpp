/* File: test-Trie-User.cpp
 * Name: Paulo Lemus
 * Team: Sandwich
 * Date: 4/12/2017
 */

#include <gtest/gtest.h>
#include <algorithm>
#include <string>
#include <vector>
#include "Trie.h"
#include "User.h"

TEST(Trie_User, assert_gtest_compiles_and_runs) {
    ASSERT_TRUE(true);
}

TEST(Trie_User, store_and_search_valid) {
    sandwich::Trie<int> trie;

    std::string name     = "Johnny Appleseed";
    std::string expected = "johnny appleseed";
    int age              = 27;

    ASSERT_FALSE( trie.search(name) );
    ASSERT_TRUE ( trie.store(name, age) );
    ASSERT_TRUE ( trie.search(name) );

    auto words = trie.complete("jo");
    ASSERT_EQ( words.size(), 1 );
    ASSERT_EQ( words[0], expected );

    auto content = trie.get(name);
    ASSERT_EQ( content.size(), 1 );
    ASSERT_EQ( content[0], age );
}

TEST(Trie_User, init_vector_with_User) {
    sandwich::Trie<sandwich::User*> trie;
}

TEST(Trie_User, store_user_ptrs) {
    sandwich::Trie<sandwich::User*> trie;

    std::string username0 = "Joco";
    std::string username1 = "the MAX";
    std::string username2 = "epidurmis";
    std::string username3 = "Shooshoo";

    sandwich::User* user0 = new sandwich::User();
    sandwich::User* user1 = new sandwich::User();
    sandwich::User* user2 = new sandwich::User();
    sandwich::User* user3 = new sandwich::User();
    user0->setUsername(username0);
    user1->setUsername(username1);
    user2->setUsername(username2);
    user3->setUsername(username3);

    ASSERT_TRUE( trie.store( username0, user0 ) );
    ASSERT_TRUE( trie.search(username0) );
    ASSERT_TRUE( trie.store( username1, user1 ) );
    ASSERT_TRUE( trie.search(username1) );
    ASSERT_TRUE( trie.store( username2, user2 ) );
    ASSERT_TRUE( trie.search(username2) );
    ASSERT_TRUE( trie.store( username3, user3 ) );
    ASSERT_TRUE( trie.search(username3) );
}

TEST(Trie_User, store_and_get_users) {

    sandwich::Trie<sandwich::User*> trie;

    std::string username = "Mr koo";
    sandwich::User* user = new sandwich::User();
    user->setUsername(username);
    
    auto users = trie.get(user->getUsername());
    
    ASSERT_EQ( users.size(), 0 );
    ASSERT_TRUE( trie.store(user->getUsername(), user) );

    users = trie.get( user->getUsername() );

    ASSERT_EQ( users.size(), 1 );
    ASSERT_EQ( users[0], user );
}

TEST(Trie_User, getCompleteBasic) {

    sandwich::Trie<sandwich::User*> trie;

    std::string username0 = "YamaSama";
    std::string username1 = "pauloasdf";
    std::string username2 = "jessieG";
    sandwich::User* user0 = new sandwich::User();
    sandwich::User* user1 = new sandwich::User();
    sandwich::User* user2 = new sandwich::User();
    user0->setUsername(username0);
    user1->setUsername(username1);
    user2->setUsername(username2);
    trie.store(user0->getUsername(), user0);
    trie.store(user1->getUsername(), user1);
    trie.store(user2->getUsername(), user2);

    auto users = trie.getComplete();
    ASSERT_EQ(users.size(), 3);
    ASSERT_TRUE( std::find(users.begin(), users.end(), user0) != users.end() );
    ASSERT_TRUE( std::find(users.begin(), users.end(), user1) != users.end() );
    ASSERT_TRUE( std::find(users.begin(), users.end(), user2) != users.end() );
}

TEST(Trie_User, getCompleteString) {

    sandwich::Trie<sandwich::User*> trie;

    std::string username0 = "YamaSama";
    std::string username1 = "pauloasdf";
    std::string username2 = "jessieG";
    sandwich::User* user0 = new sandwich::User();
    sandwich::User* user1 = new sandwich::User();
    sandwich::User* user2 = new sandwich::User();
    user0->setUsername(username0);
    user1->setUsername(username1);
    user2->setUsername(username2);
    trie.store(user0->getUsername(), user0);
    trie.store(user1->getUsername(), user1);
    trie.store(user2->getUsername(), user2);

    auto users = trie.getComplete("y");
    ASSERT_EQ(users.size(), 1);
    ASSERT_TRUE( std::find(users.begin(), users.end(), user0) != users.end() );
}

TEST(Trie_User, getCompleteStringMany) {

    sandwich::Trie<sandwich::User*> trie;

    std::string username0 = "YamaSama";
    std::string username1 = "pauloasdf";
    std::string username2 = "jessieG";
    std::string username3 = "Yama";
    std::string username4 = "Yamamoto";
    sandwich::User* user0 = new sandwich::User();
    sandwich::User* user1 = new sandwich::User();
    sandwich::User* user2 = new sandwich::User();
    sandwich::User* user3 = new sandwich::User();
    sandwich::User* user4 = new sandwich::User();
    user0->setUsername(username0);
    user1->setUsername(username1);
    user2->setUsername(username2);
    user3->setUsername(username3);
    user4->setUsername(username4);
    trie.store(user0->getUsername(), user0);
    trie.store(user1->getUsername(), user1);
    trie.store(user2->getUsername(), user2);
    trie.store(user3->getUsername(), user3);
    trie.store(user4->getUsername(), user4);

    auto users = trie.getComplete("y");
    ASSERT_EQ(users.size(), 3);
    ASSERT_TRUE( std::find(users.begin(), users.end(), user0) != users.end() );
    ASSERT_TRUE( std::find(users.begin(), users.end(), user3) != users.end() );
    ASSERT_TRUE( std::find(users.begin(), users.end(), user4) != users.end() );

    users = trie.getComplete();
    ASSERT_EQ(users.size(), 5);
    ASSERT_TRUE( std::find(users.begin(), users.end(), user0) != users.end() );
    ASSERT_TRUE( std::find(users.begin(), users.end(), user1) != users.end() );
    ASSERT_TRUE( std::find(users.begin(), users.end(), user2) != users.end() );
    ASSERT_TRUE( std::find(users.begin(), users.end(), user3) != users.end() );
    ASSERT_TRUE( std::find(users.begin(), users.end(), user4) != users.end() );
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
