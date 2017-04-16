# Sandwich-Social

A Twitter / Facebook - like social networking client made for Team Sandwich's EE 205 final project

# Class descriptions

## User.h

Fields:
Username        - std::string
Name            - std::string
Bio             - std::string
Post History    - std::vector<std::string>
Friends         - HashSet<User*>

# Trie.h

Functions:

add(std::string)
    Adds the string to the trie structure.
search(std::string)
    This returns true if the tree contains a matching string.
complete(std::string) 
    Returns a vector of all possible strings that are completions of it.
delete(std::string)
    Not going to use for now



# Milestones:

Thursday, April 20th, 2017:
1. User class will be tested and completed. We will be able to set every field as well as change them using getters and setters.

2. For the GUI, we will have to have the skeleton set up, in that we will have a user selection window and a window that we can write text to. We will be able to select user options and enter a corresponding logic loop.

3. The Trie data structure will be done and tested independently of the rest of the system.
