/* File: test-Map.cpp
 * Name: Jessie Grazziotin
 * Date: 4/23/2017
 */

#include <gtest/gtest.h>
#include "User.h"
#include <unordered_map>
//create users throw into a map and 
//

TEST(User, insertInMap){
	std::unordered_map<std::string, sandwich::User*> userMap;

	std::string username = "kingKong";
	std::string name = "Harambe"; 
	std::string bio = "Gorilla martyr of the 21st century";  

	sandwich::User* user = new sandwich::User(username, name, bio); 
	sandwich::User* user2 = new sandwich::User("u2", "dude", "hacker robot"); 

	ASSERT_TRUE(userMap.insert({user->getLower(), user}).second);
	ASSERT_TRUE(userMap.insert({user2->getLower(), user2}).second);

}



//TEST(User, getAllUsers){
//	std::unordered_map<std::string, sandwich:User*> userMap;
TEST(User, findInMap){
	std::unordered_map<std::string, sandwich::User*> userMap;

	sandwich::User* user1 = new sandwich::User("bradPitt", "Bradley Sofine Pitt", "super hott"); 
	sandwich::User* user2 = new sandwich::User("angieJ", "Angelina Jofine Jolie", "also super hott"); 

	userMap.insert({user1->getLower(), user1}); 
	userMap.insert({user2->getLower(), user2}); 
//	ASSERT_TRUE(userMap.find(user2->getLower())->second == user2 );
	ASSERT_TRUE(userMap[user2->getLower()] == user2); 
}
	


int main (int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS(); 	

}

