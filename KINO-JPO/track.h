#include <ctime>
#include "seat.h"
#pragma once

class Track
{
public:
	Track();
	Track(int, int, int, std::tm, int, int);
	~Track();

	void summarize();

	int getID();
	int getMovie();
	int getRoom();
	std::tm getTime();
	char getSeat(int);
	void setMovie(int);
	void setRoom(int);
	void setTime(std::tm);

private:
	int track_id;
	int movie_id;
	int room_id;
	std::tm time;
	Seat * seats;
	
};
