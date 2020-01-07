#include "user.h"

User::User(long _id, std::string _password) : id(_id)
{
	password = _password; //HOW TO LEAK PASSWORDS 101
}

User::~User()
{
}

bool User::match(std::string _test) {
	return password == _test;
}