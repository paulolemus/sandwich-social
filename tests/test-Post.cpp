/* File: test-Post.cpp
 * Name: Paulo Lemus
 * Date: 4/12/2017
 */

/* Test files so show usage of the Post class.
 * The post class will be used to hold a message
 * as well as the time the message was made, both
 * as strings.
 */

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Post.h"

// Ensure gtest is linked properly
TEST(Post, assert_gtest_compiles_and_runs) {
    ASSERT_TRUE(true);
}

// Ensure the constructor doesn't crash anything
TEST(Post, constructor) {
    sandwich::Post post("Hello World!");
    ASSERT_TRUE(true);
}

// Check that we can create a post and get the 
//  message back, and that it is what we expect
TEST(Post, getMessage) {
    std::string message = "Hello World!";
    sandwich::Post post(message);
    ASSERT_EQ(post.getMsg(), message);
}

// Check that when a post is created, the time
// string is automatically set to the time it was
// initialized
TEST(Post, getTime) {
    std::string message = "Hello World!";
    sandwich::Post post(message);
    ASSERT_EQ(post.getMsg(), message);
    std::string time = post.getTime();
    std::cout << "time post was made: " << time;
}

// Check that setting a message works, and we can 
// get it out of the post class
TEST(Post, setMessage) {
    std::string message1 = "Hello World!";
    std::string message2 = "Goodbye World!";

    sandwich::Post post(message1);
    ASSERT_EQ(message1, post.getMsg());

    post.setMsg(message2);
    ASSERT_EQ(message2, post.getMsg());
}

// Check that we can properly get the char*
// from the post, this will be important for
// SENDING OVER SOCKETS
TEST(Post, getCMessage) {
    std::string message = "Hello World!";

    sandwich::Post post(message);
    const char* cMsg = post.getCMsg();
    std::string stdCMsg(cMsg);

    ASSERT_EQ(stdCMsg, message);
}

TEST(Post, equals_overload) {
    std::string message = "Hello World!";

    sandwich::Post post0(message);
    sandwich::Post post1(message);
    ASSERT_TRUE(post0 == post1);
}

TEST(Post, post_in_vector) {

    std::vector<sandwich::Post> posts;
    
    std::string message = "Hello World!";
    std::string timeStr = "12:34:34 Apr 4";
    posts.push_back({message, timeStr});

    ASSERT_EQ(posts.size(), 1);
    ASSERT_EQ(posts[0].getMsg(), message);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
