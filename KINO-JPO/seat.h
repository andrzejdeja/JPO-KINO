#pragma once

class Seat
{
public:
	Seat();
	~Seat();
	void book(long);
	void cancel();
	bool is_booked();
private:
	bool booked;
	long userID;
};