#include "seat.h"

Seat::Seat() : booked(false), userID(0)
{}

Seat::~Seat()
{}

void Seat::book(int _userID)
{
	userID = _userID;
	booked = true;
}

void Seat::cancel()
{
	userID = 0;
	booked = false;
}

bool Seat::is_booked() 
{
	return booked;
}