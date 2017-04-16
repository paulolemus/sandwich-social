/* File: test-Trie.cpp
 * Name: 
 * Date: 4/12/2017
 */

#include <gtest/gtest.h>
#include "../Trie.h"

TEST(Trie, assert_gtest_compiles_and_runs) {
    ASSERT_TRUE(true);
}

TEST(Trie, constructor) {
    Trie trie;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
