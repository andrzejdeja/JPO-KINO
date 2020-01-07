#include "room.h"
#include <iostream>

Room::Room(short _rows, short _columns) : columns(_columns), rows(_rows)
{
	seats = new Seat[columns*rows];
}

Room::~Room()
{
	delete[] seats;
}

void Room::display()
{
	std::cout << "***\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			seats[i*columns + j].is_booked() ? std::cout << "X" : std::cout << "o";
		}
		std::cout << "\n";
	}
	std::cout << "***\n";
}