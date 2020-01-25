#pragma once
#include <string>

class User
{
public:
	User();
	User(uint32_t, uint16_t);
	~User();
	bool match(uint16_t);
	uint32_t get_ID();
private:
	uint32_t id;
	uint16_t password;
};
