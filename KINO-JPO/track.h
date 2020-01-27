#include <ctime>
#include <string>
#include <vector>
#include "seat.h"
#pragma once

class Track
{
public:
	std::vector<Seat> seats;

	Track();
	Track(int, int, int, std::tm, int, int);
	~Track();

	void summarize();
	std::string getTimeStr();
	void clearSeats();
	void bookSeat(int, int);

	int getID();
	int getMovie();
	int getRoom();
	std::tm getTime();
	char getSeat(int);
	int getSeatUID(int);
	void setMovie(int);
	void setRoom(int);
	void setTime(std::tm);

private:
	int track_id;
	int movie_id;
	int room_id;
	std::tm time;
		
};
