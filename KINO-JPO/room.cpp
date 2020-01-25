#include "room.h"
#include <iostream>
#include <string>

Room::Room()
{
	name = "unnamed";
	columns = 1;
	rows = 1;
}

Room::Room(std::string _name, short _rows, short _columns) : columns(_columns), rows(_rows), name(_name)
{
	
}

Room::~Room() {}

std::string Room::getName() { return name; }

short Room::getColumns() { return columns; }

short Room::getRows() { return rows; }

void Room::setName(std::string _name) { name = _name; }

void Room::setColumns(short _columns) { columns = _columns; }

void Room::setRows(short _rows) { rows = _rows; }

void Room::display()
{
	std::cout << "***\n" << name << "\n***\n";

	std::cout << "***\n";
}

void Room::summarize()
{
	std::cout << "N: " << name << " R: " << rows << "C: " << columns << "\n";
}