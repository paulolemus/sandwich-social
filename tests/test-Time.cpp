/* File: test-Time.cpp
 * Name: Paulo Lemus
 * Date: 4/12/2017
 */

#include <gtest/gtest.h>
#include <ctime> // Header with classed used to store time
#include <chrono> // Header for getting current time
#include <iostream>
#include <sstream>
#include <string>

TEST(Time, assert_gtest_compiles_and_runs) {
    ASSERT_TRUE(true);
}

TEST(Time, test_time) {
    // Make a time point object and make it the current time
    std::chrono::system_clock::time_point now = 
        std::chrono::system_clock::now();
    ASSERT_TRUE(true);
}

TEST(Time, print_curr_time) {
    // Create the c++ time_point object at curr_time
    std::chrono::system_clock::time_point now = 
        std::chrono::system_clock::now();

    // Convert the time to a time_t object that can be printed
    std::time_t currTime = std::chrono::system_clock::to_time_t(now);

    std::cout <<std::endl;
    std::cout << "current time: " << ctime(&currTime);
    std::cout <<std::endl;
    ASSERT_TRUE(true);
}

TEST(Time, save_time_as_string) {
    // Create the c++ time_point object at curr_time
    std::chrono::system_clock::time_point now = 
        std::chrono::system_clock::now();

    // Convert the time to a time_t object that can be printed
    std::time_t currTime = std::chrono::system_clock::to_time_t(now);

    std::cout << std::endl;
    std::cout << "current time: " << ctime(&currTime);

    // Save the time as a string!!
    std::string timeString = ctime(&currTime);
    std::cout << "timeString  : " << timeString;
    std::cout << std::endl;

    ASSERT_EQ(timeString, ctime(&currTime));
    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
