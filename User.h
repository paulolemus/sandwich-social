/* File: User.h
 * Name: Paulo Lemus
 * Date: 4/13/2017
 * Team: Sandwich
 * Members: Paulo L, Jessie G, Matt Y
 */

/* User class is used to store all information about a user.
 * They have several fields:
 * 1. Username
 * 2. Name
 * 3. Bio
 * 4. Post History
 * 5. Friends
 */

/* posts:
 * We are going under the assumption that posts are never deleted.
 * The last post is always the most recent.
 */

/* Friends:
 * We are going to assume that friends cannot delete their accounts.
 * They always, exist, so we do not have to worry about a pointer to
 * a deleted user.
 * When adding a friend, we pass in the friend. If the friend 
 * already exists, we do not add him/her.
 */

#ifndef EE205_FINAL_USERS_H_
#define EE205_FINAL_USERS_H_


#include <vector>
#include <string>
#include "Post.h"

namespace sandwich {

class User {

    std::string username;
    std::string name;
    std::string bio;
    
    std::vector<sandwich::Post>  posts;
    std::vector<sandwich::User*> friends;

public:
    User();
    
    static bool validateUsername(const std::string name);

};

} // namespace sandwich

#endif // EE205_FINAL_USERS_H_
