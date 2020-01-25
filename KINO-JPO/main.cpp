#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <map>
#include <vector>
#include <string>
#include <inttypes.h>

#include "movie.h"
#include "user.h"
#include "room.h"
/*
59. Design and implement classes for a cinema booking system, user can select movie,
room, time, seats and place order. The system includes following object: movie,
room, track(in which room when which movie is showing), seat, user, order(a user
books which track and which seats) Additionally, this system can be extended to be
used for cinema administrator to plan movie(when to plan which movie in which
room) in order to get the most audience and income.
*/

std::map<int, Movie> movie;
std::map<uint64_t, User> user;
std::map<uint16_t, Room> room;

void setup();
void shutdown();
void serve(uint32_t);
int admin();

int main()
{
	srand((unsigned int)time(NULL));

	setup();

	std::string buff = "";
	while (1) //main loop
	{
		std::cout << "Witamy w kinie!\nPodaj numer uzytkownika lub wpisz \"nowy\", aby utworzyc nowe zamowienie\n";
		std::cin >> buff;
		uint32_t uID = 0; //just 32 to not annoy user
		uint16_t pass = 0;
		if (buff == "nowy") //create new user
		{
			short f = 1;
			while (f)
			{
				uID = rand();
				uID = (uID << 16) + rand();
				f = 0;
				for (int i = 0; i < user.size(); i++) {
					if (uID == user[i].get_ID()) f = 1;
				}
			}
			pass = rand();
			User newuser(uID, pass);
			user[newuser.get_ID()] = newuser;
			std::cout << "Twoj numer uzytkownika to " << uID << "\n";
			std::cout << "Twoje haslo to " << pass << "\n";
		}
		if (buff == "admin") //admin
		{
			std::cout << "Panel administratora\nPodaj haslo: ";
			std::cin >> buff;
			if (buff == "1234")
			{
				if (!admin()) break;
			}
		}
		else //serve user
		{
			if (uID == 0)
			{ 
				try {
					uID = std::stoul(buff, 0, 10);
					std::cout << "Podaj haslo\n";
					std::cin >> buff;
					if (user[uID].match((uint16_t)std::stoi(buff))) serve(uID);
				}
				catch (...) {
					std::cout << "ERR\n";
				}
			}
			else { serve(uID); }
		}
	}
	shutdown();
}

void serve(uint32_t num) {
	std::string buff = "";
	std::cout << "a - dodaj zamowienie\n";
	std::cin >> buff;
	if (buff == "a" || buff == "A") {
		
	}
}

int admin() {
	while (1) {
		std::string buff = "";
		std::cout << "a - dodaj film\nb - zmien tytul filmu\nc - dodaj sale\nexit - wyjdz z trybu administratora\nshutdown - zakoncz program\n";
		std::cin >> buff;
		if (buff == "a" || buff == "A") 
		{
			std::cout << "Podaj tytul nowego filmu\n";
			std::cin >> buff;
			Movie newmovie(buff);
			movie[(int)movie.size()] = newmovie;
			std::cout << "Dodano film: " << movie[(int)movie.size() - 1].getTitle() << "\n";
		}
		if (buff == "b" || buff == "B") 
		{
			std::cout << "Podaj numer filmu\n";
			for (int i = 0; i < movie.size(); i++)
			{
				std::cout << i + 1 << ". " << movie[i].getTitle() << "\n";
			}
			std::cin >> buff;
			try {
				int num = std::stoi(buff) - 1;
				if ( num < movie.size())
				{
					std::cout << "Podaj nowy tytul " << movie.at(num).getTitle() << ":\n";
					std::cin >> buff;
					movie.at(num).modifyTitle(buff);
					std::cout << "Nowy tytul to: " << movie.at(num).getTitle() << "\n";
				}
				else throw;
			}
			catch (...) {
				std::cout << "ERR\n";
			}
		}
		if (buff == "c" || buff == "C")
		{	
			try {
				std::cout << "Podaj nazwe sali\n";
				std::cin >> buff;
				std::string name = buff;
				std::cout << "Podaj liczbe rzedow w sali\n";
				std::cin >> buff;
				if (std::stoi(buff) <= 0) throw;
				short rows = (short)std::stoi(buff);
				std::cout << "Podaj liczbe miejsc w rzedzie\n";
				std::cin >> buff;
				if (std::stoi(buff) <= 0) throw;
				short columns = (short)std::stoi(buff);
				Room newroom(name, rows, columns);
				room[(unsigned short)room.size()] = newroom;
				std::cout << "Dodano sale:\n";
				room[(unsigned short)room.size() - 1].display();
			}
			catch (...) {
				std::cout << "ERR\n";
			}
		}
		if (buff == "shutdown") return 0;
		if (buff == "exit") break;
	}
	return 1;
}

void setup(){}

void shutdown() {}