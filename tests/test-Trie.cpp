/* File: test-Trie.cpp
 * Name: 
 * Date: 4/12/2017
 */

#include <gtest/gtest.h>

#include <string>
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



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
