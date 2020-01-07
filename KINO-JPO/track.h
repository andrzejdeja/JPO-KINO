#pragma once
#include <ctime>

class Track
{
public:
	Track(int, int, std::time_t);
	~Track();

private:
	int movie_id;
	int room_id;
	std::time_t time;
	
};
