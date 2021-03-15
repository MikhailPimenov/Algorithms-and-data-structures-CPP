#ifndef TEST_VOTING_H
#define TEST_VOTING_H

#include <iostream>

#include <unordered_map>

void test_voting ( void ( *algorithm )( const std::string &stream, std::unordered_map < std::string, int > &dbOut ) );


#endif // TEST_VOTING_H
