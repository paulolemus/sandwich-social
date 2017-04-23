/* File: test-FileIO.cpp
 * Name:
 * Team: Sandwich
 * Date: 4/22/2017
 */

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include "FileIO.h"

static const std::string readUserFile     = "users.dat";
static const std::string writeUserFile    = "writeusers.dat";
static const std::string readFriendsFile  = "friends.dat";
static const std::string writeFriendsFile = "writefriends.dat";


TEST(FileIO, build_with_gtest) {
    ASSERT_TRUE(true);
}

TEST(FileIO, constructor) {
    
}

TEST(FileIO, getters_settters) {


}

TEST(FileIO, read_users) {


}

TEST(FileIO, read_friends) {


}

TEST(FileIO, write_users) {


}

TEST(FileIO, write_friends) {


}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
