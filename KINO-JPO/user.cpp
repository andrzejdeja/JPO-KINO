#include "user.h"

User::User()
{
	id = 0;
	password = 0;
}

User::User(uint32_t _id, uint16_t _password) : id(_id), password(_password)
{
	 //HOW TO LEAK PASSWORDS 101
}

User::~User()
{
}

uint32_t User::get_ID() {
	return id;
}

bool User::match(uint16_t _test) {
	return password == _test;
}