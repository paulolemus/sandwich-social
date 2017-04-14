/* File: test-User.cpp
 * Name: Paulo Lemus
 * Date: 4/12/2017
 */

#include <gtest/gtest.h>

TEST(User, assert_gtest_compiles_and_runs) {
    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
