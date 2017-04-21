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
    sandwich::Trie<> trie;
    ASSERT_TRUE(true);
}

TEST(Trie, add_string) {
    sandwich::Trie<> trie;
    std::string name = "john wick";
    ASSERT_TRUE( trie.add(name) );
}

TEST(Trie, add_multiple_unique_string) {
    sandwich::Trie<> trie;

    std::string name0 = "john wick";
    std::string name1 = "adam savage";
    std::string name2 = "curtis bentley";
    std::string name3 = "apollo creed";

    ASSERT_TRUE( trie.add(name0) );
    ASSERT_TRUE( trie.add(name1) );
    ASSERT_TRUE( trie.add(name2) );
    ASSERT_TRUE( trie.add(name3) );
}

TEST(Trie, add_identical_string) {
    sandwich::Trie<> trie;

    std::string name = "john wick";

    ASSERT_TRUE ( trie.add(name) );
    ASSERT_FALSE( trie.add(name) );
}

TEST(Trie, add_nested_string) {
    sandwich::Trie<> trie;

    std::string name0 = "john wick";
    std::string name1 = "john w";
    std::string name2 = "john";

    ASSERT_TRUE ( trie.add(name0) );
    ASSERT_TRUE ( trie.add(name1) );
    ASSERT_TRUE ( trie.add(name2) );
}

TEST(Trie, add_same_alpha_different_casing) {
    sandwich::Trie<> trie;

    std::string name0 = "john wick";
    std::string name1 = "John wick";
    std::string name2 = "joHn Wick";
    ASSERT_TRUE ( trie.add(name0) );
    ASSERT_FALSE( trie.add(name1) );
    ASSERT_FALSE( trie.add(name2) );
}

TEST(Trie, add_invalid_string) {
    sandwich::Trie<> trie;

    std::string invalid0 = "@savage";
    std::string invalid1 = "Th3 5Av@g3";
    ASSERT_FALSE( trie.add(invalid0) );
    ASSERT_FALSE( trie.add(invalid1) );
}

TEST(Trie, search_empty) {
    sandwich::Trie<> trie;

    std::string name = "penny gallow";
    ASSERT_FALSE( trie.search(name) );
}

TEST(Trie, search_valid_name) {
    sandwich::Trie<> trie;

    std::string name = "penny gallow";
    ASSERT_TRUE( trie.add(name) );
    ASSERT_TRUE( trie.search(name) );
}

TEST(Trie, search_is_case_insensitive) {
    {
    sandwich::Trie<> trie;
    std::string name0 = "JOhn Wick";
    std::string name1 = "john wick";
    std::string name2 = "JOHN WICK";
    std::string name3 = "jOHN wICK";
    ASSERT_TRUE( trie.add(name0) );
    ASSERT_TRUE( trie.search(name1) );
    ASSERT_TRUE( trie.search(name2) );
    ASSERT_TRUE( trie.search(name3) );
    }
    {
    sandwich::Trie<> trie;
    std::string name0 = "JOhn Wick";
    std::string name1 = "john wick";
    std::string name2 = "JOHN WICK";
    std::string name3 = "jOHN wICK";
    ASSERT_TRUE( trie.add(name1) );
    ASSERT_TRUE( trie.search(name0) );
    ASSERT_TRUE( trie.search(name2) );
    ASSERT_TRUE( trie.search(name3) );
    }
    {
    sandwich::Trie<> trie;
    std::string name0 = "JOhn Wick";
    std::string name1 = "john wick";
    std::string name2 = "JOHN WICK";
    std::string name3 = "jOHN wICK";
    ASSERT_TRUE( trie.add(name2) );
    ASSERT_TRUE( trie.search(name1) );
    ASSERT_TRUE( trie.search(name0) );
    ASSERT_TRUE( trie.search(name3) );
    }
    {
    sandwich::Trie<> trie;
    std::string name0 = "JOhn Wick";
    std::string name1 = "john wick";
    std::string name2 = "JOHN WICK";
    std::string name3 = "jOHN wICK";
    ASSERT_TRUE( trie.add(name3) );
    ASSERT_TRUE( trie.search(name1) );
    ASSERT_TRUE( trie.search(name2) );
    ASSERT_TRUE( trie.search(name0) );
    }
}

TEST(Trie, complete_basic) {
    sandwich::Trie<> trie;

    std::string name = "szechuan sauce";
    std::vector<std::string> vec;

    ASSERT_TRUE( trie.add(name) );
    vec = trie.complete();
    ASSERT_EQ( vec.size(), 1 );
    ASSERT_EQ( vec[0], name );
}

TEST(Trie, complete_is_lowercase) {
    sandwich::Trie<> trie;
 
    std::string input    = "SZECHUAN SAUCE";
    std::string expected = "szechuan sauce";
    std::vector<std::string> vec;

    ASSERT_TRUE( trie.add(input) );
    vec = trie.complete();
    ASSERT_EQ( vec.size(), 1 );
    ASSERT_EQ( vec[0], expected );
}

TEST(Trie, complete_multiple_unique_first_letter) {
    sandwich::Trie<> trie;

    std::vector<std::string> names;
    names.push_back("alison beverly");
    names.push_back("borus camendo");
    names.push_back("catherine jack");
    names.push_back("dover queenly");
    names.push_back("ingress oliver");
    names.push_back("jacklyn tommas");
    names.push_back("keenan sage");
    names.push_back("oliver kage");
    names.push_back("xander xanduris");
    names.push_back("yannis fulupe");
    names.push_back("zoro zebra");

    for(unsigned int i = 0; i < names.size(); ++i)
        trie.add(names[i]);

    std::vector<std::string> words = 
        trie.complete();

    for(unsigned int i = 0; i < words.size(); ++i) 
        ASSERT_EQ(words[i], names[i]);
}

TEST(Trie, complete_multiple_same_first_char) {
    sandwich::Trie<> trie;

    std::vector<std::string> names;
    names.push_back("abe jackson");
    names.push_back("alison beverly");
    names.push_back("ally johnson");

    for(unsigned int i = 0; i < names.size(); ++i)
        trie.add(names[i]);

    std::vector<std::string> words = 
        trie.complete();

    for(unsigned int i = 0; i < words.size(); ++i) 
        ASSERT_EQ(words[i], names[i]);
}

TEST(Trie, autocomplete_invalid) {
    sandwich::Trie<> trie;
    trie.add("Hello world");

    auto vec = trie.complete("");
    EXPECT_EQ(vec.size(), 0);
    vec = trie.complete("@");
    EXPECT_EQ(vec.size(), 0);
    vec = trie.complete("w");
    EXPECT_EQ(vec.size(), 0);
    vec = trie.complete(" ");
    EXPECT_EQ(vec.size(), 0);
}

TEST(Trie, autocomplete_valid_simple) {
    sandwich::Trie<> trie;
    std::string word = "hello world";
    ASSERT_TRUE( trie.add(word) );

    auto vec = trie.complete("h");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], word);

    vec = trie.complete("H");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], word);

    vec = trie.complete("hel");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], word);

    vec = trie.complete("hello");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], word);

    vec = trie.complete("hello ");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], word);

    vec = trie.complete("hello world");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], word);

    vec = trie.complete("HELLO WORLD");
    ASSERT_EQ(vec.size(), 1);
    ASSERT_EQ(vec[0], word);
}

TEST(Trie, autocomplete_nested_words) {
    sandwich::Trie<> trie;

    std::vector<std::string> words;
    words.push_back("the");
    words.push_back("the quick");
    words.push_back("the quick brown");
    words.push_back("the quick brown fox");
    words.push_back("the quick brown fox jumps");
    words.push_back("the quick brown fox jumps over");
    words.push_back("the quick brown fox jumps over the");
    words.push_back("the quick brown fox jumps over the lazy");
    words.push_back("the quick brown fox jumps over the lazy dog");
    for(unsigned int i = words.size() - 1; i > 0; --i) {
        ASSERT_TRUE( trie.add(words[i]) );
    }
    ASSERT_TRUE( trie.add(words[0]) );

    for(unsigned int i = 0; i < words.size(); ++i) {
        auto vec = trie.complete(words[i]);

        for(unsigned int j = 0; j < vec.size(); ++j) {
            ASSERT_EQ(vec[j], words[j + i]);
        }
    }
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
