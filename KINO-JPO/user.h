#include <string>
#pragma once

class User
{
public:
	User();
	User(int, int);
	~User();
	bool match(int);
	int get_ID();
private:
	int id;
	int password;
};
