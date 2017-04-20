/* File: Trie.h
 * Name: Paulo, Matt
 * Date: 4/15/2017
 * Team: Sandwich
 */

/* This Trie will be used for autocompletion when
 * searching for users. Case will not matter.
 * Users can enter alpha characters and spaces only.
 */

#ifndef SANDWICH_TRIE_H_
#define SANDWICH_TRIE_H_

#include <iostream> // debugging
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
    bool isLeaf;
    Node* children[27];

    // Functions
    
    Node(const char value, const bool isWord);

    // Returns the node with the given value
    Node* getChild(const char ch);
    // Creates new node if it doesn't exist and returns
    // a pointer to it. Otherwise, it just returns a pointer
    // to the existing node
    Node* addChild(const char ch, const bool isWord);

};

class Trie {

    Node* root; // value = '\0', isWord = false;
    
public:

    /* Constructor */
    Trie();

    /* Functions */

    // Add: Simply adds string to the trie structure
    bool add(std::string name);

    // Search: Return true if the tree contains exact string
    bool search(std::string name);
    
    // Return all possible strings
    std::vector<std::string> complete();

    // Complete: Give a string, this returns a vector
    // of all the possible completions of the string.
    std::vector<std::string> complete(std::string name);


private:
    // Preorder traversal:
    // Current, left right
    std::vector<std::string> preorder(Node* root);
};

///////////////////////////////////
//        IMPLEMENTATIONS        //
///////////////////////////////////
Node::Node(const char value, const bool isWord) : 
    value(value), 
    isWord(isWord),
    isLeaf(true) {
    for(int i = 0; i < 27; ++i) children[i] = nullptr;
}


Node* Node::getChild(const char ch) {

    // Guard
    if((!isalpha(ch) && ch != ' ') || isLeaf) 
        return nullptr;

    // convert to index
    int index = ch;
    if(index == ' ') index = 26;
    else {
        if(index >= 'A' && index <= 'Z') {
            index += 32;
        }
        index -= 'a';
    }
    return children[index];
}

Node* Node::addChild(const char ch, const bool isWord){

    // Guard
    if(!isalpha(ch) && ch != ' ') return nullptr;

    // Convert letter to index
    int index = ch;
    if(index == ' ') index = 26;
    else {
        if(index >= 'A' && index <= 'Z') {
            index += 32;
        }
        index -= 'a';
    }

    // Add node if nonexistant, then return index
    if(children[index] == nullptr) {
        isLeaf = false;
        children[index] = new Node(ch, isWord);
    }
    return children[index];
}

///////////////////////////////////////////////

Trie::Trie() : root(new Node('\0', false)) {}

bool Trie::add(std::string name) {

    // Validate string / convert upper to lower
    for(unsigned int i = 0; i < name.size(); ++i) {
        if( !isalpha(name[i]) && name[i] != ' ') {
            return false;
        }
        if(name[i] >= 'A' && name[i] <= 'Z') {
            name[i] = name[i] + 32;
        }
    }
    
    // Iterate through tree adding nodes
    Node* current = root;
    Node* next;
    for(unsigned int i = 0; i < name.size(); ++i) {

        int index = name[i];
        if(index == ' ') index  = 26;
        else             index -= 'a';

        next = current->getChild(index);
        if(next == nullptr) {
            current = current->addChild(name[i], false);
        }
        else {
            current = next;
        }
    }

    if(current->isWord) return false;
    else {
        current->isWord = true;
        return true;
    }
}

bool Trie::search(std::string name) {
    
    // Validate string
    for(unsigned int i = 0; i < name.size(); ++i) {
        if( !isalpha(name[i]) && name[i] != ' ') {
            return false;
        }  
        if(name[i] >= 'A' && name[i] <= 'Z') {
            name[i] = name[i] + 32;
        }
    }

    // Search through tree
    Node* node = root;
    for(unsigned int i = 0; i < name.size(); ++i) {

        node = node->getChild( name[i] );
        if(node == nullptr) return false;
    }

    if(node->isWord) return true;
    else             return false;
}

/* Algorithm:
 * Get the preorder for each node below the root.
 * Append each word in each vector to one single words
 * vector. This is done to prevent the root's null char
 * from being placed at the beginning of each string
 */
std::vector<std::string> Trie::complete() {

    std::vector<std::string> words;

    for(unsigned int i = 0; i < 27; ++i) {
        if(root->children[i] != nullptr) {
            auto vec = preorder(root->children[i]);
            for(auto word : vec) {
                words.push_back(word);
            }
        }
    }
    return words;
}


/* ALGORITHM:
 * 1. Navigate to the place where string given ends.
 * 2. Work way down each branch until a leaf is reached.
 *    Along the way, any time we hit a word, add that component 
 *    to the vector will the name string
 */
std::vector<std::string> Trie::complete(std::string name) {

    std::vector<std::string> words;

    // Guard / convert upper to lower
    if(name.size() < 1) return words;
    for(unsigned int i = 0; i < name.size(); ++i) {
        if( !isalpha(name[i]) && name[i] != ' ') return words;
        if(name[i] >= 'A' && name[i] <= 'Z') {
            name[i] = name[i] + 32;
        }
    }

    // Iterate to last node of the word
    Node* node = root;
    for(unsigned int i = 0; i < name.size(); ++i) {
        node = node->getChild( name[i] );
        if(node == nullptr) return words;
    }

    // Add string if current node is a word
    if(node->isWord) words.push_back(name);

    // Call preorder on all children to get completion
    for(unsigned int i = 0; i < 27; ++i) {
        if(node->children[i] != nullptr) {
            auto vec = preorder(node->children[i]);
            for(auto substring : vec) {
                words.push_back(name + substring);
            }
        }
    }

    return words;
}

/* This traverses the tree in a preorder fashion.
 * TODO: Improve efficiency and runtime
 */
std::vector<std::string> Trie::preorder(Node* node) {

    std::vector<std::string> words;

    if(node == nullptr);
    else if(node->isLeaf) {
        std::string substring(1, node->value);
        words.push_back(substring);
    }
    else {
        // Push back current value if current node is a word
        if(node->isWord) {
            std::string substring(1, node->value);
            words.push_back(substring);
        }
        // Append string from beneath to current node
        for(unsigned int i = 0; i < 27; ++i) {
            if(node->children[i] != nullptr) {
                auto vec = preorder(node->children[i]);
                for(auto rightstring : vec) {
                    std::string substring(1, node->value);
                    substring += rightstring;
                    words.push_back(substring);
                }
            }
        }
    }
    return words;
}


} // namespace sandwich
#endif // SANDWICH_TRIE_H_
