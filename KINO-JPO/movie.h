#pragma once
#include <string>

class Movie
{
public:
	Movie();
	Movie(std::string);
	~Movie();
	std::string getTitle();
	void modifyTitle(std::string);
private:
	std::string title;
};
