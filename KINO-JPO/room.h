#include <string>
#include "seat.h"
#pragma once

class Room
{
public:
	Room();
	Room(std::string, short, short);
	~Room();
	void display();
	void summarize();
	std::string getName();
	short getRows();
	short getColumns();
	void setName(std::string);
	void setRows(short);
	void setColumns(short);
private:
	std::string name;
	short columns;
	short rows;

};
