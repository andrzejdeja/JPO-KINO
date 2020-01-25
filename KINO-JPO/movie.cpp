#include "movie.h"

Movie::Movie()
{
	title = "unnamed";
}

Movie::Movie(std::string _title) : title(_title)
{
}

Movie::~Movie()
{
}

std::string Movie::getTitle()
{
	return title;
}

void Movie::modifyTitle(std::string _title) {
	title = _title;
}