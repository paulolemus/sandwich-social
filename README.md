# Sandwich-Social

A Twitter / Facebook - like social networking client made for Team Sandwich's EE 205 final project

Once logged in to your account, you as a user of Sandwich Social are able to post messages to your wall, view your friend list, add new friends, view the profile of a particular friend, edit your profile, remove a friend, and logout.

# How it works

The program has a couple key features. The program is ran in a terminal-based GUI.
For the GUI, we used the NCURSES library, as it provided us easy and complete control over the terminal display. 

As NCURSES also gave us complete control over user input, we were able to make all of our input fields reactive. As a user types the name of another user while searching, we are able to display a list of the closest matches immediately, without the need for the user to press "enter". The list updates as the user types.

To get this autosuggestion feature working, we used a homemade generic Trie class.
We push back User pointers onto the end of each Trie branch that holds their name or username. Every time input is changed, we do a search to get all completion suggestions and display them to the screen.

The program also remembers changes across sessions. We use a FileIO class to parse in user and friend data from .dat files upon launching the program, and then we write all user and friend data to the same dat files before the program exits.

# How to use it

At the login screen, enter a string containing only alpha characters and spaces. If the string matches an existing username, then you login as that account. Otherwise, you will be brought to the user creation screen where you will enter your name and bio. At any time, you can press ESC to exit the program or to go back a screen.

The next screen is the HomeScreen.
This screen is split into two windows, the feed and the menu. To switch between them, press 'q'. While controlling the top window, use the arrow keys to scroll through top posts. While controlling the bottom, use arrow keys to scroll through the options. Press enter to select an option.

In any of the menu-selected screens, you usually have options to enter characters into an input window or to press ESC to exit the screen.

# How to make

To make the main program, simply type `make`
To make any of the tests, type `export TESTCASE=test-<name>`
then type `make run-test`.
Alternatively, type `make tests` then cd into the test folder and type `./run-all-tests.sh`

# Class descriptions

## User.h

Fields:
Username        - std::string
Name            - std::string
Bio             - std::string
Post History    - std::vector<std::Post>
Friends         - std::vector<sandwich::User*>

User objects must be created with a username, name, and bio. 
Each user holds a set of their friends. The set is actually a vector, but the way friends are added gives the vector the properties of a set.
Each user also holds a complete history of their Posts, held in chronological order.
Bundling Friends and Posts with the user class allows us to make all changes we need to an account if we have a pointer to the User.

## Trie.h

Functions:

bool add(std::string key)
    - This function creates a branch of the given key.
    - If the branch exists, it simply marks the last node as a "word".

bool search(std::string key)
    - This returns true if the exact key given is found in the Trie.

std::vector<std::string> complete(std::string key = "")
    - Given a prefix string, this will return a vector of all strings that contain
      the given prefix

bool store(std::string key, const T& datum)
    - This does what add does, however it also adds the datum to the last node of the branch. 
      This is useful because we can later retrieve it with a given string or prefix string.

std::vector<T> get(std::string key)
    - Return a vector of all the datum stored at the end of the given key's branch

std::vector<T> get(std::vector<std::string> keys)
    - Do the same as the previous get, but this returns datum for multiple string searches.

std::vector<T> getComplete(std::string key = "")
    - Get all datum at the end of branches that complete the given prefix

The Trie class is very useful for quick search/retrieval/storage of data or keys. It is very valuable because it allows us to get all data that completes a prefix string.

## Post.h

This class is a wrapper for a post string as well as a timestamp string for when the post was created.
This bundling of post data and timestamp lets us display information as they are on social networking sites; with a timestamp.

## FileIO.h

## GUI.h


# Milestones:

Thursday, April 20th, 2017:
1. User class will be tested and completed. We will be able to set every field as well as change them using getters and setters.

2. For the GUI, we will have to have the skeleton set up, in that we will have a user selection window and a window that we can write text to. We will be able to select user options and enter a corresponding logic loop.

3. The Trie data structure will be done and tested independently of the rest of the system.
