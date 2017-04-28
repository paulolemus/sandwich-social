/* File: paulo-test.cpp
 * Name: Paulo Lemus
 * Team: Sandwich
 */

/* A test program to learn how to use the ncurses library.
 */

#include <ncurses.h>
#include <iostream>
#include <cstdio>

int main() {

    // Open config
    initscr();              // Starts ncurses mode
    cbreak();               // get input immediately
    noecho();               // prevent characters from being automatically echoed
    keypad(stdscr, TRUE);   // Enable keypad and arrow keys

    printw("Hello World!"); // print window
    refresh();              // Draws virtual screen to actual screen
    getch();                // get a character without printing it to screen
    refresh();              // Draws virtual screen to actual screen
    getchar();              // get char and print to screen
    refresh();              // Draws virtual screen to actual screen
    getchar();
    endwin();               // Ends ncurses mode
    return 0;
}
