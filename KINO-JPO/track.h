#pragma once
#include <ctime>

class Track
{
public:
	Track();
	Track(int, int, int, std::tm);
	~Track();

private:
	int track_id;
	int movie_id;
	int room_id;
	std::tm time;
	
};
