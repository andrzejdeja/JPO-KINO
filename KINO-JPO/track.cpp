#include "track.h"

Track::Track(int _movie_id, int _room_id, std::time_t _time) : movie_id(_movie_id), room_id(_room_id), time(_time)
{
}

Track::~Track()
{
}