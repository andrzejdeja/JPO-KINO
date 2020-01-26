#include "track.h"
#include <iostream>
#include <string>

Track::Track()
{
	track_id = 0;
	movie_id = 0;
	room_id = 0;
	seats = new Seat[1];
}

Track::Track(int _track_id, int _movie_id, int _room_id, std::tm _time, int columns, int rows) : track_id(_track_id), movie_id(_movie_id), room_id(_room_id), time(_time)
{
	seats = new Seat[(size_t)(columns*rows)];
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

std::string Track::getTimeStr()
{
	return std::to_string(time.tm_hour) + ":" + std::to_string(time.tm_min) + " " + std::to_string(time.tm_mday) + "." + std::to_string(time.tm_mon + 1 )+ "." + std::to_string(time.tm_year + 1900);
}

void Track::summarize()
{
	std::cout << "ID: " << track_id + 1 << " Sid: " << room_id + 1 << " Fid: " << movie_id + 1 << " Data: " << time.tm_hour << ":" << time.tm_min << " " << time.tm_mday << "." << time.tm_mon + 1 << "." << time.tm_year + 1900 << "\n";
}

char Track::getSeat(int x) {
	return seats[x].is_booked() ? 'X' : 'o';
}
