#include "user.h"

User::User()
{
	id = 0;
	password = 0;
}

User::User(int _id, int _password) : id(_id), password(_password)
{
	 //HOW TO LEAK PASSWORDS 101
}

User::~User()
{
}

int User::get_ID() {
	return id;
}

int User::get_pass() {
	return password;
}

bool User::match(int _test) {
	return password == _test;
}