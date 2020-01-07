#pragma once
#include "seat.h"

class Room
{
public:
	Room(short, short);
	~Room();
	void display();
private:
	short columns;
	short rows;
	Seat * seats;

};
