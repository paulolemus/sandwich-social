/* File: Trie.h
 * Name: Paulo, Matt
 * Date: 4/15/2017
 * Team: Sandwich
 */

/* This Trie will be used to store the username and name 
 * of all users. It will be used particularly for the following:
 *
 * 1. Autocompletion of a string. For example, if you want to
 *    search for a different user's account, you can search for
 *    either the name or username of the account and you will
 *    get a correct result.
 *
 * 2. Retrieving a particular user by either username or name.
 *    Users must have unique usernames, however they all can 
 *    have the same name. Doing a "get" for either string will
 *    return a vector of all the possible users that belong to
 *    that string.
 *
 * 3. Validating that a user exists.
 *
 *
 * BEHAVIOR:
 *
 * Every function that takes a string argument first validates
 * if the string given is ONLY spaces and alpha characters.
 * All string are saved as lowercase, and all searches first
 * convert the given string to lowercase. Keep in mind
 * that usernames may appear with casing, but this makes the
 * searches non-case-sensitive.
 *
 *
 * INSTANTIATION OF TRIE:
 * sandwich::Trie<Type> trie;
 */

#ifndef SANDWICH_TRIE_H_
#define SANDWICH_TRIE_H_

#include <cctype>
#include <string>
#include <vector>
#include <unordered_set>

namespace sandwich {

///////////////////////////////////////////
//            DECLARATIONS               //
///////////////////////////////////////////


/* Node struct
 *
 * This node struct is what is used as nodes in the
 * trie class. Each node has a character value, a bool
 * so that we may tell if all the nodes leading up to the 
 * current spell a valid string. The array of node pointers
 * is what is used to store all possible children. Index 0
 * represents an 'a' node, and index 25 represents 'z' node.
 * Index 26 is a ' ' node.
 *
 * The node also holds a vector of generic data, used for storage
 * and retrieval.
 */
template <typename T = char>
struct Node {

    char           value;
    bool           isWord;
    bool           isLeaf;
    Node<T>*       children[27];
    std::vector<T> data;

    // constructor / deconstructor
    Node(const char value, const bool isWord);
    ~Node();

    // Given a character, returns a pointer
    // from the corresponding Node* index. 
    Node<T>* getChild(const char ch);

    // Creates new node if it doesn't exist and returns
    // a pointer to it. Otherwise, it just returns a pointer
    // to the existing node
    Node<T>* addChild(const char ch, const bool isWord);

    // Add generic datum to data vector if it
    // does not already hold it.
    bool store(const T& datum);

    // Remove datum from vector if it exists
    void remove(const T& datum);
};


/* Trie class
 *
 * This class is used to autocomplete string,
 * store data at a key, and retrieve data at a key.
 */
template <typename T = char>
class Trie {

    Node<T>* root; // value = '\0', isWord = false;
    
public:

    // Constructor / Destructor
    Trie();
    ~Trie();


    // Simply adds string to the trie structure.
    // Returns true on success, false on failure
    bool add(std::string key);

    // Return true if the tree contains string.
    // This search is not case sensitive.
    bool search(std::string key);

    // Return all strings in the trie
    std::vector<std::string> complete();

    // Complete: Give a string, this returns a vector
    // of all the possible completions of the string.
    std::vector<std::string> complete(std::string key);


    // Store the datum at the end of each key given
    // It only stores if the datum does not already exist
    bool store(std::string key, const T& datum);

    // Returns vector of data found at key location
    std::vector<T> get(std::string key);
    std::vector<T> get(std::vector<std::string> keys);
    std::vector<T> getComplete(std::string key = "");


private:
    // Preorder traversal:
    // Current, left right
    std::vector<std::string> preorder(Node<T>* node);

    // Retrieval preorder
    std::unordered_set<T> preorderGet(Node<T>* node);
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
Node<T>::~Node() {
    for(auto ptr : children) {
        if(ptr != nullptr) delete ptr;
    }
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
Trie<T>::~Trie() { delete root; }

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
    // Mark the last node of they key string as a
    // word, and store the data in the node's vector
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


template <typename T>
std::vector<T> Trie<T>::getComplete(std::string key) {

    std::vector<T> dataSet;

    // Verify key, convert to lower if necessary
    for(unsigned int i = 0; i < key.size(); ++i) {
        if(!isalpha(key[i]) && key[i] != ' ') {
            return dataSet;
        }
        if(key[i] >= 'A' && key[i] <= 'Z') {
            key[i] = key[i] + 32;
        }
    }

    // Iterate to key subtree node
    Node<T>* node = root;
    for(unsigned int i = 0; i < key.size(); ++i) {
        node = node->getChild( key[i] );
        if(node == nullptr) return dataSet;
    }

    // Add current data if it exists
    if(node->isWord) {
        dataSet = node->data;
    }

    // Add data from all subtree nodes if they do not
    // already exist in the current dataSet.
    for(unsigned int i = 0; i < 27; ++i) {
        if(node->children[i] != nullptr) {
            auto dataVec = preorderGet(node->children[i]);
            bool isExisting = false;
            for(int j = 0; j < dataVec.size(); ++j) {
                //for() {

                //}
            }
        }
    }
    return dataSet;
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
