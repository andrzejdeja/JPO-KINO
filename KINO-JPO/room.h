#include <string>
#include "seat.h"
#pragma once

class Room
{
public:
	Room();
	Room(std::string, short, short);
	~Room();
	void display();
	void summarize();
private:
	std::string name;
	short columns;
	short rows;
	Seat * seats;

};
