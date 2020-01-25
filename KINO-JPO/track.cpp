#include "track.h"

Track::Track()
{
	track_id = 0;
	movie_id = 0;
	room_id = 0;
}

Track::Track(int _track_id, int _movie_id, int _room_id, std::tm _time) : movie_id(_movie_id), room_id(_room_id), time(_time)
{
}

Track::~Track()
{
}