#pragma once
#include <ctime>

class Track
{
public:
	Track();
	Track(int, int, int, std::tm);
	~Track();

	void summarize();

	int getID();
	int getMovie();
	int getRoom();
	std::tm getTime();
	void setMovie(int);
	void setRoom(int);
	void setTime(std::tm);

private:
	int track_id;
	int movie_id;
	int room_id;
	std::tm time;
	
};
