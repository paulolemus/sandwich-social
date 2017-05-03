# FINAL PROJECT - Jessica - Team Sandwich

# 1) What I learned from this homework:
---------- Encapsulation and Large Project Team work--------
From this project, I learned so much about encapsulation and working in teams on a large project. 
Our team decided to seperate the project up into separate parts and I chose the GUI implementation. 
I really like programming with the user in mind and I'm interested in a career in UI and UX so this 
was something I wanted to pursue. 

We decided to use ncurses for our GUI library. It offers a lot of functions that pertain to producing 
windows, giving them attributes like color, and it provides a way to manipulate the cursor for user input. 

The tricky part about working with window objects is you always have to refresh or delete them and then reset
the screen or the window you're working in. So there with almost every function you have to send in a window ptr
that will only exists for the time of that screen. Also as you make edits, like say print something to a window, 
you have to make sure to refresh in the correct sequence so that it will repopulate before you're getting a 
user input. So what this turned into is a very large GUI class with lots of functions so that we could 
separate the screens into as many side functions as possible. The menu alone took 4 seperate functions to create. 


In order to work seperately, I first started by just getting the window diminsions setup in the way that I 
thought flowed nicely and looked clean. Next I worked with my team to decided how we wanted our logic to flow
in the main driver. And finally, once the other members were finished we worked together on developing
how we would access all of the other classes (Users, their Posts, and the Trie tree for autocomplete).


Aside from the GUI though I was able to learn about tree and map structures used in the Trie autocomplete and 
unordered map of our users. I had to learn how to iterate and access paired members in both of these structures
to create a vector of friends and find matches. 

--------------Inheritance -------------------
Becuase we were working with so many different classes, I learned a lot about inheritance and how to 
create functions so that the private data would be accessible from their public functions. I also practiced
creating pointers and passing them to functions so that it would update these private items for a class's
object. 

-------Good Programming Practices and making reusable code ---------- 
We also implemented these by using templates so that we could do multiple test
cases with different datatypes very quickly. We created our own namespace also so that 
if anyone else wanted to integrate our code with their's, it would be less likely to create errors. 
Lastly, we made sure that we were constantly formatting our code in a clean manner and using the
same tabbing practices. Lastly, Paulo taught us how to use google tests. It became too challenging to 
use them with the GUI.h functions but it was nice to still learn how they were helpful for developing
in general. 


# 2) My Contributions
My primary contribution for this project was the GUI.h development. I created and decided on the main layout for
the login screen and homescreen. I also implemented different attributes for flair such as colors or reverse 
highlighting. 

Integrating was very difficult but once I finally sat down with my team members and had them walk me through how
to access their functions, I was able to create functions that would populate the screens based on the scope of 
what we wanted to show. 

Aside from the attributes and visuals of the GUI, I was responsible for all of the under the hood work for the user
inputs. For example: how to populate a scrolling menu and take in a users selection. Another example is how
to take in a users input from a little window box (like bio or post). Once there were multiple lines, it became very
difficult to keep up with the cursor and maximum limit that the user could have. Implementing "Delete" was extremely
challenging, but after multiple versions and help from my team members, we were able to develop a beautiful 
input string getter (userInput). 



# 3) Questions:
I was wondering if you wouldn't mind giving us some insight into the security of our code. I know that is 
your background and I really don't know hardly anything about it so I was wondering if you would mind 
giving feedback on that. Also I'm pretty bad at not looking out for memory leaks. We tried to implement 
that with using destructors and functions like delwin(w) that would delete a window at the end of the function.
But I still feel like its a problem that I won't recognize until I really screw something up. So if I know of
better ways to look out for it that would be helpful. 



# 4) Comments:
I really appreciate the liberty your gave us with this project. We were able to really push ourselves in
the directions that we wanted to learn about. I feel like this project was very challenging but 
it was because we really pushed ourselves to create a piece of work that we would be proud of. I was 
really lucky also to have found such a great team. I learned pretty quickly into the semester that
my C background from 160 was not very strong. Paulo and Matt were both very patient in explainging things
to me that I didn't understand. They're also great students and I was able to pick up some of their study and 
programming practices from this class. I also liked that we all pushed ourselves as a team. Even when one of us 
brought an idea to the table that wasn't a scope requirement, we all pushed ourselves to try to work together 
and figure it out, instead of giving up because it wasn't a requirement. 



