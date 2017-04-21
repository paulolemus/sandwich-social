/* File: test-Trie-User.cpp
 * Name: 
 * Date: 4/12/2017
 */

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../Trie.h"
//#include "../User.h"

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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
