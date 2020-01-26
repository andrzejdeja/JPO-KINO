#include <inttypes.h>
#pragma once

class Seat
{
public:
	Seat();
	~Seat();
	void book(int);
	void cancel();
	bool is_booked();
private:
	bool booked = false;
	int userID = 0;
};