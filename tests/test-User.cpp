/* File: test-User.cpp
 * Name: Paulo Lemus
 * Date: 4/12/2017
 */

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "User.h"

TEST(User, assert_gtest_compiles_and_runs) {
    ASSERT_TRUE(true);
}

TEST(User, user_constructor) {

    sandwich::User user;
    ASSERT_TRUE(true);
}

TEST(User, user_constructor_copy) {

    std::string username = "supadoopa";
    std::string name     = "John Goodman";
    std::string bio      = "Yonjuu ni hyaku moyasee!!";

    sandwich::User user(username, name, bio);
    ASSERT_TRUE(true);
}

TEST(User, validateString) {

    std::string validUsername   = "Mr Hankey";
    std::string validName       = "Johnathan Hankey";
    std::string invalidUsername = "mr. hankey";
    std::string invalidName     = "K31$HA";

    ASSERT_TRUE(  sandwich::User::validateStr(validUsername) );
    ASSERT_TRUE(  sandwich::User::validateStr(validName) );
    ASSERT_FALSE( sandwich::User::validateStr(invalidUsername) );
    ASSERT_FALSE( sandwich::User::validateStr(invalidName) );
}

TEST(User, getters_setters) {

    std::string username = "the man";
    std::string name     = "Adam Driver";
    std::string bio      = "All hail DARTH VADER!";

    sandwich::User user;

    ASSERT_TRUE( user.setUsername(username) );
    ASSERT_TRUE( user.setName(name) );
    user.setBio(bio);

    ASSERT_EQ( user.getUsername(), username );
    ASSERT_EQ( user.getName(),     name );
    ASSERT_EQ( user.getBio(),      bio );
}

TEST(User, add_str_post) {

    sandwich::User user;

    std::string newPost0 = "I absolutely love cats! ERMAH GERD <3";
    user.addPost(newPost0);
    
    auto posts = user.getPosts();
    ASSERT_EQ(posts.size(), 1);
    ASSERT_EQ(posts[0].getMsg(), newPost0);

    std::string newPost1 = "CATS SUCK! </3";
    user.addPost(newPost1);

    posts = user.getPosts();
    ASSERT_EQ(posts.size(), 2);
    ASSERT_EQ(posts[1].getMsg(), newPost1);
}

TEST(User, add_Post_post) {

    sandwich::User user;

    sandwich::Post post0("Sup bro. I am an ANIMAL!!1!");
    sandwich::Post post1("Does anyone want to buy protein supplements!?");

    auto posts = user.getPosts();
    ASSERT_EQ(posts.size(), 0);

    user.addPost(post0);
    posts = user.getPosts();
    ASSERT_EQ(posts.size(), 1);
    ASSERT_TRUE(posts[0] == post0);

    user.addPost(post1);
    posts = user.getPosts();
    ASSERT_EQ(posts.size(), 2);
    ASSERT_TRUE(posts[1] == post1);
}

TEST(User, remove_post) {

    sandwich::User user;

    sandwich::Post post0("Sup bro. I am an ANIMAL!!1!");
    sandwich::Post post1("Does anyone want to buy protein supplements!?");

    auto posts = user.getPosts();
    ASSERT_EQ(posts.size(), 0);

    user.addPost(post0);
    posts = user.getPosts();
    ASSERT_EQ(posts.size(), 1);
    ASSERT_TRUE(posts[0] == post0);
    user.addPost(post1);
    posts = user.getPosts();
    ASSERT_EQ(posts.size(), 2);
    ASSERT_TRUE(posts[1] == post1);


    user.removePost(post0);

    posts = user.getPosts();
    ASSERT_EQ(posts.size(), 1);
    ASSERT_TRUE(posts[0] == post1);

    user.removePost(post1);

    posts = user.getPosts();
    ASSERT_EQ(posts.size(), 0);
}

TEST(User, add_friend_has_friend) {

    sandwich::User user0;
    sandwich::User user1;

    ASSERT_FALSE( user0.hasFriend(&user1) );
    ASSERT_TRUE ( user0.addFriend(&user1) );
    ASSERT_TRUE ( user0.hasFriend(&user1) );
    ASSERT_FALSE( user0.addFriend(&user1) );
}

TEST(User, add_friend_remove_friend) {

    sandwich::User* user0 = new sandwich::User();
    sandwich::User* user1 = new sandwich::User();

    ASSERT_FALSE( user0->removeFriend(user1) );
    ASSERT_TRUE ( user0->addFriend(user1) );
    ASSERT_TRUE ( user0->hasFriend(user1) );

    auto friends = user0->getFriends();
    ASSERT_EQ  ( friends.size(), 1 );
    ASSERT_TRUE( friends[0] == user1 );

    ASSERT_TRUE( user0->removeFriend(user1) );
    friends = user0->getFriends();
    ASSERT_EQ( friends.size(), 0 );
    ASSERT_FALSE( user0->hasFriend(user1) );

}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
