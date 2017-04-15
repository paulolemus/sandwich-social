/* File: Post.h
 * Name: Paulo Lemus
 * Date: 4/14/2017
 */

/* This is a Post class, used to store any text posts.
 * They have a date and time, as well as the string of the
 * post contents.
 *
 * USAGE:
 * A post must be created with a message. Creating a new post 
 * automatically sets it's time string to whatever the current
 * time is. To get either, simply call getMsg or getTime.
 *
 * To get the char* to send over sockets, simply call getCMsg,
 * or getCTime.
 */

#ifndef EE205_FINAL_POST_H_
#define EE205_FINAL_POST_H_

// REFER TO THIS FOR MAX POST SIZE
#define POST_MAX 100

#include <string>
#include <chrono>
#include <ctime>

namespace sandwich {

class Post {

    std::string message;
    std::string time;

public:
    // Constructor
    Post(std::string message);

    // Getters
    const std::string& getMsg()   const;
    const std::string& getTime()  const;
    const char*        getCMsg()  const;
    const char*        getCTime() const;

    // Setters
    void setMsg (std::string& message);
    void setTime(std::string& time);
};

// Implementations

// Constructor
Post::Post(std::string message) : message(message) {
    
    // Save current time
    std::chrono::system_clock::time_point now = 
        std::chrono::system_clock::now();

    // convert to a time_t type
    std::time_t currTime =
        std::chrono::system_clock::to_time_t(now);

    // Save contents into string
    time = ctime(&currTime);
}

// Getters
const std::string& Post::getMsg()  const { return message; }
const std::string& Post::getTime() const { return time; }
const char*  Post::getCMsg()  const { return message.c_str(); }
const char*  Post::getCTime() const { return time.c_str(); }

// Setters
void Post::setMsg(std::string& message) {
    this->message = message;

    std::chrono::system_clock::time_point now = 
        std::chrono::system_clock::now();

    // convert to a time_t type
    std::time_t currTime =
        std::chrono::system_clock::to_time_t(now);

    // Save contents into string
    time = ctime(&currTime);
}   

void Post::setTime(std::string& time) {
    this->time = time;
}

} // namespace sandwich

#endif // EE205_FINAL_POST_H_
