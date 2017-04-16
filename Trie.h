/* File: Trie.h
 * Name:
 * Date: 4/15/2017
 * Team: Sandwich
 */

/* This Trie will be used for autocompletion when
 * searching for users. Case will not matter.
 * Users can enter alpha characters and spaces only.
 */

#ifndef SANDWICH_TRIE_H_
#define SANDWICH_TRIE_H_

#include <cctype>
#include <string>
#include <vector>

namespace sandwich {

/* Node that has a value and marker if the node is a word.
 * It has an array of pointers to children, with [0] = a,
 * [25] = z and [26] = " "
 */
struct Node {
    char value;
    bool isWord;
    Node* children[27];

    Node(char value, bool isWord);
    char getLower();
    Node* getChild(char ch);
    Node* addChild(char ch);
};

class Trie {

    Node root('\0');
    
public:

    /* Constructor */
    Trie();

    /* Functions */

    // Add: Simply adds string to the trie structure
    bool add(std::string);

    // Search: Return true if the tree contains exact string
    bool search(std::string);
    
    // Complete: Give a string, this returns a vector
    // of all the possible completions of the string.
    std::vector<std::string> complete(std::string);
};

///////////////////////////////////
//        IMPLEMENTATIONS        //
///////////////////////////////////
Node::Node(char value, bool isWord) : 
    value(value), 
    isWord(isWord) {
    for(int i = 0 i < 27; ++i) children[i] = nullptr;
}
char Node::getLower() {
    char ch = value;
    if(ch >= 'A' && ch <= 'Z') ch += 32;
    return ch;
}
Node* Node::getChild(char ch) {
    if(ch >= 'A' && ch <= 'Z') ch += 32;
}


} // namespace sandwich
#endif // SANDWICH_TRIE_H_
