#include "track.h"
#include <iostream>

Track::Track()
{
	track_id = 0;
	movie_id = 0;
	room_id = 0;
	seats = new Seat[1];
}

Track::Track(int _track_id, int _movie_id, int _room_id, std::tm _time, int columns, int rows) : movie_id(_movie_id), room_id(_room_id), time(_time)
{
	seats = new Seat[columns*rows];
}

Track::~Track()
{
	delete[] seats;
}

int Track::getID() { return track_id; }

int Track::getMovie() { return movie_id; }

int Track::getRoom() { return room_id; }

std::tm Track::getTime() { return time; }

void Track::setMovie(int _id)
{
	movie_id = _id;
}

void Track::setRoom(int _id)
{
	room_id = _id;
}

void Track::setTime(std::tm _time)
{
	time = _time;
}

void Track::summarize()
{
	char c[26];
	asctime_s(c, 26, &time);
	std::cout << "ID: " << track_id << " Sid: " << room_id << " Fid: " << movie_id << " Data: " << c << "\n";
}

char Track::getSeat(int x) {
	return seats[x].is_booked() ? 'X' : 'o';
}
