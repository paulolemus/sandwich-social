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

	for(unsigned int counter = 0; counter < U2.size(); counter++){
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

TEST(FileIO, writeusers){
	
	const std::string inputUsertempFile = "usertemp.dat";
	sandwich::FileIO f1(inputUsertempFile,inputFriendsFile);
	std::vector<std::string> S1, S2;
	std::string p1, p2;

	sandwich::User* U1 = new sandwich::User("pauloasdf","Paulo Lemus","Everytime I turn a corner I take an L.");
	p1 = "\"That moment when peeing feels so good you start crying\"";
	p2 = "timestamp here";
	U1->addPost({p1,p2});

	sandwich::User* U2 = new sandwich::User("jessieG","Jessie G","Hippy life | Yo yo dawg | 920");
	p1 = "Sup sup yo yo yo yo yo yo I got this freeesh mixtape hit up my soundcloud jessieG";
	p2 = "timestamp here";
	U2->addPost({p1,p2});

	sandwich::User* U3 = new sandwich::User("YamaSama","Matt Y","Anime wo suuuuugoi desu nee");
	p1 = "I prayed and then jesus took the wheel";
	p2 = "timestamp here";
	U3->addPost({p1,p2});

	//ADD posts
	std::ofstream outfile(inputUsertempFile, std::ofstream::out);
	outfile.close();	
	f1.writeUser(U1);//write into new file
	f1.writeUser(U2);
	f1.writeUser(U3);

	//read in inputUsertempFile and compare to users.dat
	
	std::ifstream myfile(inputUserFile);

	if(myfile){//write original file into S1
		while(!myfile.eof()){
			getline(myfile, p1);
			S1.push_back(p1);
		}
		myfile.close();
	}

	myfile.open(inputUsertempFile);

	if(myfile){//write temp file into S2
		while(!myfile.eof()){
			getline(myfile, p1);
			S2.push_back(p1);
		}
		myfile.close();
	}

	for(unsigned int counter1 = 0; counter1 < S1.size(); counter1++){//compare that S1 and S2 are equal
		ASSERT_EQ(S1[counter1], S2[counter1]);
	}

}
/*
TEST(FileIO, writefriends){
	
	std::string inputFriendstempFile = "friendstemp.dat";
	sandwich::FileIO f1(inputUserFile, inputFriendstempFile);
	std::vector<std::string> S1, S2;
	std::string p1;

	//create users
	sandwich::User* U1 = new User("pauloasdf","Paulo Lemus","Everytime I turn a corner I take an L.");
	sandwich::User* U2 = new User("jessieG","Jessie G","Hippy life | Yo yo dawg | 920");
	sandwich::User* U3 = new User("YamaSama","Matt Y","Anime wo suuuuugoi desu nee");
	
	U1->addFriend(U2);//add friends into users
	U1->addFriend(U3);//returns bool, check if this is ok
	U2->addFriend(U1);
	U2->addFriend(U3);
	U3->addFriend(U1);
	U3->addFriend(U2);

	f1.writeFriends(U1);//write friends into file
	f1.writeFriends(U2);
	f1.writeFriends(U3);

	std::ifstream myfile(inputFriendsFile);

	if(myfile){//read original file
		while(!myfile.eof()){
			getline(myfile, p1);
			S1.push_back(p1);
		}
		myfile.close();
	}

	myfile.open(inputFriendstempFile);//read temp file

	if(myfile){
		while(!myfile.eof()){
			getline(myfile, p1);
			S2.push_back(p1);
		}
		myfile.close();
	}

	for(int counter1 = 0; counter1 < S1.size(); counter1++){//compare each line
		ASSERT_EQ(S1[counter1], S2[counter1]);
	}


}

*/
int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
