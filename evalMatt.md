# FINAL PROJECT - Matthew Yamamoto - Team Sandwich

# 1) What I learned from this project:
	During this project I learned how to work together
with other programmers in order to create a larger piece
of work impossible by myself. I learned how to use various
std and custom classes with different fields, functions,
and purposes. I learned how to use ncurses to write a
GUI to present our work. I learned how to parse a file
by reading in and writing out by looking for specific
indicators on each line and substringing what is needed.
I mostly used an iterative approach for my functions and
the math instead of recursive or special formulas. I also
learned how to use new data structures like the std 	
unordered map and the Trie tree. I also learned how to
use testcases to test seperate parts of our program
to ensure that the seperate parts work before integrating
it into the whole program.

# 2) My Contributions
	I worked mainly on the parser, FileIO.h, where it
contains a class that has 2 strings that holds the files 
to be read and written on. The files hold the information
to be saved when the program is terminated and can be read
when the program is lauched to have the data where it left
off. I worked mainly with strings and searching for
indicators in the string to confirm that the information is
valid and can constitute a new user. I also used a std que 
as a buffer so that lines wouldn't be skipped if there is
incorrect data formatting. I also integrated the FileIO
class into the driver to initialize and to write when the
program ends. I began work on the Trie class but Paulo took
over when he saw that the difficulty would be very high. I
wrote code on the trie to set the structure but didn't
write the functions. I also started a little bit on the
GUI but Jessie took over that with help from Paulo too. 
I wrote the test cases for the FileIO as well.

# 3) Questions:
	I noticed the Paulo used templates in order to
make his class more generic, is it typical for programmers
to do this to reuse code? What if you only use a function
once in your program?

# 4) Comments:
	This project was effective in making me learn in
order to overcome problems. I feel like my code is very
basic as times because I write in nested for loops, 
while loops, if statements, etc. Maybe I should look to
have a more robust programming style with a wider range
of syntax like switch-case, try-catch, etc.
