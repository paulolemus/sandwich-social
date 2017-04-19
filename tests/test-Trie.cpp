/* File: test-Trie.cpp
 * Name: Paulo Lemus
 * Date: 4/12/2017
 */

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include "../Trie.h"

TEST(Trie, assert_gtest_compiles_and_runs) {
    ASSERT_TRUE(true);
}

TEST(Trie, constructor) {
    sandwich::Trie trie;
    ASSERT_TRUE(true);
}

TEST(Trie, add_string) {
    sandwich::Trie trie;
    std::string name = "John Wick";
    ASSERT_TRUE( trie.add(name) );
}

TEST(Trie, add_multiple_unique_string) {
    sandwich::Trie trie;

    std::string name0 = "John Wick";
    std::string name1 = "Adam Savage";
    std::string name2 = "Curtis Bentley";
    std::string name3 = "Apollo Creed";

    ASSERT_TRUE( trie.add(name0) );
    ASSERT_TRUE( trie.add(name1) );
    ASSERT_TRUE( trie.add(name2) );
    ASSERT_TRUE( trie.add(name3) );
}

TEST(Trie, add_identical_string) {
    sandwich::Trie trie;

    std::string name = "John Wick";

    ASSERT_TRUE ( trie.add(name) );
    ASSERT_FALSE( trie.add(name) );
}

TEST(Trie, add_same_alpha_different_casing) {
    sandwich::Trie trie;

    std::string name0 = "John Wick";
    std::string name1 = "john wick";
    ASSERT_TRUE ( trie.add(name0) );
    ASSERT_FALSE( trie.add(name1) );
}

TEST(Trie, add_invalid_string) {
    sandwich::Trie trie;

    std::string invalid0 = "@savage";
    std::string invalid1 = "Th3 5Av@g3";
    ASSERT_FALSE( trie.add(invalid0) );
    ASSERT_FALSE( trie.add(invalid1) );
}

TEST(Trie, search_empty) {
    sandwich::Trie trie;

    std::string name = "Penny Gallow";
    ASSERT_FALSE( trie.search(name) );
}

TEST(Trie, search_valid_name) {
    sandwich::Trie trie;

    std::string name = "Penny Gallow";
    ASSERT_TRUE( trie.add(name) );
    ASSERT_TRUE( trie.search(name) );
}

TEST(Trie, search_diff_capitalization) {
    sandwich::Trie trie;

    std::string name0 = "Penny Lucas";
    std::string name1 = "penny lucas";
    std::string name2 = "pEnnY lUCAS";
    std::string name3 = " Penny Lucas";
    
    EXPECT_TRUE( trie.add(name0) );
    EXPECT_TRUE( trie.search(name0) );
    EXPECT_TRUE( trie.search(name1) );
    EXPECT_TRUE( trie.search(name2) );
    EXPECT_FALSE( trie.search(name3) );
}

TEST(Trie, complete_basic) {
    sandwich::Trie trie;

    std::string name = "Szechuan Sauce";
    std::vector<std::string> vec;

    ASSERT_TRUE( trie.add(name) );
    vec = trie.complete();
    ASSERT_EQ( vec.size(), 1 );
    ASSERT_EQ( vec[0], name );
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
