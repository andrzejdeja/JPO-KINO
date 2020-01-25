#include <inttypes.h>
#pragma once

class Seat
{
public:
	Seat();
	~Seat();
	void book(uint32_t);
	void cancel();
	bool is_booked();
private:
	bool booked;
	uint32_t userID;
};