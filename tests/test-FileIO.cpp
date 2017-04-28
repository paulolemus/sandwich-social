/* File: test-FileIO.cpp
 * Name:
 * Team: Sandwich
 * Date: 4/22/2017
 */

#include"../FileIO.h"
#include<gtest/gtest.h>

TEST(FileIO, constructor){
	sandwich::FileIO f1;
}
TEST(FileIO, constructorinput){
	sandwich::FileIO f1("Name","friends");
}



int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
