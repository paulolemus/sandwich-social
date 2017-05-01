/* File: test-FileIO.cpp
 * Name:
 * Team: Sandwich
 * Date: 4/22/2017
 */

#include"FileIO.h"
#include<gtest/gtest.h>

std::string inputUserFile    = "tests/users.dat";
std::string inputFriendsFile = "tests/friends.dat";

TEST(FileIO, default_constructor){
	sandwich::FileIO f1;
	f1.setUserFileName(inputUserFile);
	f1.setFriendsFileName(inputFriendsFile);
	ASSERT_EQ(f1.getUserFileName(),inputUserFile);
        ASSERT_EQ(f1.getFriendsFileName(), inputFriendsFile);
}

TEST(FileIO, constructorinput){
	sandwich::FileIO f1(inputUserFile,inputFriendsFile);
	ASSERT_EQ(f1.getUserFileName(),inputUserFile);
	ASSERT_EQ(f1.getFriendsFileName(), inputFriendsFile);
}

TEST(FileIO, readusers){
	sandwich::FileIO f1(inputUserFile,inputFriendsFile);
	std::vector<sandwich::User*>  U1 = f1.readUsers();
	std::vector<sandwich::User*> U2;
	
	U2.push_back(new sandwich::User("pauloasdf","Paulo Lemus","Everytime I turn a corner I take an L."));
	U2.push_back(new sandwich::User("jessieG","Jessie G","Hippy life | Yo yo dawg | 920"));
	U2.push_back(new sandwich::User("YamaSama","Matt Y","Anime wo suuuuugoi desu nee"));

	for(int counter = 0; counter < U2.size(); counter++){
		ASSERT_EQ(U2[counter]->getUsername(), U1[counter]->getUsername());
		ASSERT_EQ(U2[counter]->getName(),     U1[counter]->getName());
		ASSERT_EQ(U2[counter]->getBio(),      U1[counter]->getBio());
	}
}

TEST(FileIO, readfriends){
	sandwich::FileIO f1(inputUserFile,inputFriendsFile);
	std::vector<std::vector<std::string>> fl1 = f1.readFriends();
	std::vector<std::vector<std::string>> fl2;
	std::vector<std::string> s1;
	
	s1.push_back("pauloasdf");
	s1.push_back("jessieG");
	s1.push_back("YamaSama");
	fl2.push_back(s1);

	s1.clear();
	s1.push_back("jessieG");
	s1.push_back("pauloasdf");
	s1.push_back("YamaSama");
	fl2.push_back(s1);

	s1.clear();
	s1.push_back("YamaSama");
	s1.push_back("pauloasdf");
	s1.push_back("jessieG");
	fl2.push_back(s1);

	ASSERT_EQ(fl1.size(),3);
	ASSERT_EQ(fl2.size(),3);

	for(unsigned int counter1 = 0; counter1 < fl1.size(); counter1++){
		ASSERT_EQ(fl1[counter1].size(),3);
		ASSERT_EQ(fl2[counter1].size(),3);
	}


	for(unsigned int counter1 = 0; counter1 < fl1.size(); counter1++){
		for(unsigned int counter2 = 0; counter2 < fl1[counter1].size(); counter2++){
			ASSERT_EQ(fl1[counter1][counter2], fl2[counter1][counter2]);
		}
	}

	
}




int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
