#pragma once
#include <string>

class User
{
public:
	User(long, std::string);
	~User();
	bool match(std::string);
private:
	long id;
	std::string password;
};
