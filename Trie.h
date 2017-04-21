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

#include <iostream>
#include <cctype>
#include <string>
#include <vector>

namespace sandwich {

/* Node that has a value and marker if the node is a word.
 * It has an array of pointers to children, with [0] = a,
 * [25] = z and [26] = " "
 */
template <typename T = char>
struct Node {
    char value;
    bool isWord;
    bool isLeaf;
    Node<T>* children[27];

    std::vector<T> data;

    // Functions
    
    Node(const char value, const bool isWord);

    // Returns the node with the given value
    Node<T>* getChild(const char ch);
    // Creates new node if it doesn't exist and returns
    // a pointer to it. Otherwise, it just returns a pointer
    // to the existing node
    Node<T>* addChild(const char ch, const bool isWord);

    // Add datum to data vector if it does not already
    // hold it.
    bool store(const T& datum);
    // Remove datum from vector if it exists
    void remove(const T& datum);

};

template <typename T = char>
class Trie {

    Node<T>* root; // value = '\0', isWord = false;
    
public:

    /* Constructor */
    Trie();

    /* Functions */

    // Add: Simply adds string to the trie structure
    bool add(std::string key);
    // Search: Return true if the tree contains exact string
    bool search(std::string key);
    // Return all possible strings
    std::vector<std::string> complete();
    // Complete: Give a string, this returns a vector
    // of all the possible completions of the string.
    std::vector<std::string> complete(std::string key);

    /* Store and retrieve functions */

    // Store the datum at the end of each key given
    bool store(std::string key, const T& datum);

    // Returns vector of data found at key location
    std::vector<T> get(std::string key);
    std::vector<T> get(std::vector<std::string> keys);
    std::vector<T> getComplete(std::string key);


private:
    // Preorder traversal:
    // Current, left right
    std::vector<std::string> preorder(Node<T>* node);

    // Retrieval preorder
    std::vector<T> preorderGet(Node<T>* node);
};

///////////////////////////////////
//        IMPLEMENTATIONS        //
///////////////////////////////////
template <typename T>
Node<T>::Node(const char value, const bool isWord) : 
    value(value), 
    isWord(isWord),
    isLeaf(true) {
    for(int i = 0; i < 27; ++i) children[i] = nullptr;
}


template <typename T>
Node<T>* Node<T>::getChild(const char ch) {

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

template <typename T>
Node<T>* Node<T>::addChild(const char ch, const bool isWord){

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
        children[index] = new Node<T>(ch, isWord);
    }
    return children[index];
}

template <typename T>
bool Node<T>::store(const T& datum) {

    for(auto thing : data) {
        if(thing == datum) return false;
    }
    data.push_back(datum);
    return true;
}

template <typename T>
void Node<T>::remove(const T& datum) {

    for(unsigned int i = 0; i < data.size(); ++i) {
        if(datum == data[i]) {
            data.erase(data.begin() + i);
        }
    }
}

///////////////////////////////////////////////

template <typename T>
Trie<T>::Trie() : root(new Node<T>('\0', false)) {}

template <typename T>
bool Trie<T>::add(std::string key) {

    // Validate string / convert upper to lower
    for(unsigned int i = 0; i < key.size(); ++i) {
        if( !isalpha(key[i]) && key[i] != ' ') {
            return false;
        }
        if(key[i] >= 'A' && key[i] <= 'Z') {
            key[i] = key[i] + 32;
        }
    }
    
    // Iterate through tree adding nodes
    Node<T>* current = root;
    Node<T>* next;
    for(unsigned int i = 0; i < key.size(); ++i) {

        int index = key[i];
        if(index == ' ') index  = 26;
        else             index -= 'a';

        next = current->getChild(index);
        if(next == nullptr) {
            current = current->addChild(key[i], false);
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

template <typename T>
bool Trie<T>::search(std::string key) {
    
    // Validate string
    for(unsigned int i = 0; i < key.size(); ++i) {
        if( !isalpha(key[i]) && key[i] != ' ') {
            return false;
        }  
        if(key[i] >= 'A' && key[i] <= 'Z') {
            key[i] = key[i] + 32;
        }
    }

    // Search through tree
    Node<T>* node = root;
    for(unsigned int i = 0; i < key.size(); ++i) {

        node = node->getChild( key[i] );
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
template <typename T>
std::vector<std::string> Trie<T>::complete() {

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
 *    to the vector will the key string
 */
template <typename T>
std::vector<std::string> Trie<T>::complete(std::string key) {

    std::vector<std::string> words;

    // Guard / convert upper to lower
    if(key.size() < 1) return words;
    for(unsigned int i = 0; i < key.size(); ++i) {
        if( !isalpha(key[i]) && key[i] != ' ') return words;
        if(key[i] >= 'A' && key[i] <= 'Z') {
            key[i] = key[i] + 32;
        }
    }

    // Iterate to last node of the word
    Node<T>* node = root;
    for(unsigned int i = 0; i < key.size(); ++i) {
        node = node->getChild( key[i] );
        if(node == nullptr) return words;
    }

    // Add string if current node is a word
    if(node->isWord) words.push_back(key);

    // Call preorder on all children to get completion
    for(unsigned int i = 0; i < 27; ++i) {
        if(node->children[i] != nullptr) {
            auto vec = preorder(node->children[i]);
            for(auto substring : vec) {
                words.push_back(key + substring);
            }
        }
    }

    return words;
}

template <typename T>
bool Trie<T>::store(std::string key, const T& datum) {

    // Validate string / convert upper to lower
    for(unsigned int i = 0; i < key.size(); ++i) {
        if( !isalpha(key[i]) && key[i] != ' ') {
            return false;
        }
        if(key[i] >= 'A' && key[i] <= 'Z') {
            key[i] = key[i] + 32;
        }
    }
    
    // Iterate through tree adding nodes
    Node<T>* current = root;
    Node<T>* next;
    for(unsigned int i = 0; i < key.size(); ++i) {

        int index = key[i];
        if(index == ' ') index  = 26;
        else             index -= 'a';

        next = current->getChild(index);
        if(next == nullptr) {
            current = current->addChild(key[i], false);
        }
        else {
            current = next;
        }
    }
    current->isWord = true;
    return current->store(datum);
}


template <typename T>
std::vector<T> Trie<T>::get(std::string key) {

    // Validate string / convert upper to lower
    for(unsigned int i = 0; i < key.size(); ++i) {
        if( !isalpha(key[i]) && key[i] != ' ') {
            return std::vector<T>();
        }
        if(key[i] >= 'A' && key[i] <= 'Z') {
            key[i] = key[i] + 32;
        }
    }

    // Iterate to the key node
    Node<T>* node = root;
    for(unsigned int i = 0; i < key.size(); ++i) {
        
        int index = key[i];
        if(index == ' ') index  = 26;
        else             index -= 'a';

        node = node->getChild( key[i] );
        if(node == nullptr) return std::vector<T>();
    }
    return node->data;
}

/* ALGORITHM:
 * Need to go to each key location and build up keys 
 * that are not already in our vector.
 */
template <typename T>
std::vector<T> Trie<T>::get(std::vector<std::string> keys) {

    std::vector<T> dataSet;

    for(unsigned int i = 0; i < keys.size(); ++i) {
        for(unsigned int j = 0; j < keys[i].size(); ++j) {
            

        }
    }
}

/* This traverses the tree in a preorder fashion.
 * TODO: Improve efficiency and runtime
 */
template <typename T>
std::vector<std::string> Trie<T>::preorder(Node<T>* node) {

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
