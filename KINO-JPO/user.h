#pragma once
#include <string>

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
