#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <map>
#include <vector>
#include <string>
#include <inttypes.h>
#include <ctime>

#include "movie.h"
#include "user.h"
#include "room.h"
#include "track.h"

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
std::map<int, Track> track;

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
				if (uID == 0) 
				{
					f = 1;
					continue;
				}
				for (int i = 0; i < user.size(); i++)
				{
					if (uID == user[i].get_ID())
					{
						f = 1;
						break;
					}
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
		std::cout << "a - dodaj film\nb - zmien tytul filmu\nc - dodaj sale\nd - edytuj sale\ne - dodaj seans\nf - edytuj seans\nexit - wyjdz z trybu administratora\nshutdown - zakoncz program\n";
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
		if (buff == "d" || buff == "D")
		{
			std::cout << "Podaj numer sali\n";
			for (int i = 0; i < room.size(); i++)
			{
				std::cout << i + 1 << ". ";
				room[i].summarize();
			}
			std::cin >> buff;
			try {
				int num = std::stoi(buff) - 1;
				if (num < room.size())
				{
					std::cout << "Podaj nowa nazwe (" << room.at(num).getName() << "):\n";
					std::cin >> buff;
					if (buff != "") room.at(num).setName(buff);
					std::cout << "Nowa nazwa to: " << room.at(num).getName() << "\n";
					std::cout << "Podaj nowa ilosc rzedow w sali (" << room.at(num).getRows() << "):\n";
					std::cin >> buff;
					if (buff != "") room.at(num).setRows((short)stoi(buff));
					std::cout << "Nowa ilosc rzedow w sali to: " << room.at(num).getRows() << "\n";
					std::cout << "Podaj nowa ilosc miejsc w rzedzie (" << room.at(num).getColumns() << "):\n";
					std::cin >> buff;
					if (buff != "") room.at(num).setColumns((short)stoi(buff));
					std::cout << "Nowa ilosc miejsc w rzedzie to: " << room.at(num).getColumns() << "\n";
				}
				else throw;
			}
			catch (...) {
				std::cout << "ERR\n";
			}
		}
		if (buff == "e" || buff == "E")
		{
			try {
				std::cout << "Podaj numer sali\n";
				for (int i = 0; i < room.size(); i++)
				{
					std::cout << i + 1 << ". ";
					room[i].summarize();
				}
				std::cin >> buff;
				int num1 = std::stoi(buff) - 1;
				if (num1 < room.size())
				{
					std::cout << "Podaj numer filmu\n";
					for (int i = 0; i < movie.size(); i++)
					{
						std::cout << i + 1 << ". " << movie[i].getTitle() << "\n";
					}
					std::cin >> buff;
					int num2 = std::stoi(buff) - 1;
					if (num2 < movie.size()) 
					{
						//time_t t;
						//time(&t);
						std::tm ntt;
						//ntt = localtime(&t);
						std::cout << "Podaj date sensu w formacie DDMMYYYY:\n";
						std::cin >> buff;
						if (buff.length() != 8) throw;
						ntt.tm_mday = std::stoi(buff.substr(0, 2));
						ntt.tm_mon = std::stoi(buff.substr(2, 2)) - 1;
						ntt.tm_year = std::stoi(buff.substr(4, 4)) - 1900;
						std::cout << "Podaj godzine sensu w formacie HHMM:\n";
						std::cin >> buff;
						if (buff.length() != 4) throw;
						ntt.tm_hour = std::stoi(buff.substr(0, 2));
						ntt.tm_min = std::stoi(buff.substr(2, 2)) - 1;
						Track newtrack((int)track.size(), num2, num1, ntt);
						track[(int)track.size()] = newtrack;
						std::cout << "Dodano seans:\n";
						track[(int)track.size() - 1].summarize();
					}
					else throw;
				}
				else throw;
			}
			catch (...) {
				std::cout << "ERR\n";
			}
		}
		if (buff == "f" || buff == "F")
		{
			std::cout << "Podaj numer seansu\n";
			for (int i = 0; i < track.size(); i++)
			{
				std::cout << i + 1 << ". ";
				track[i].summarize();
			}
			std::cin >> buff;
			try {
				int num = std::stoi(buff) - 1;
				if (num < track.size())
				{
					//MOVIE CHANGE
					std::cout << "Wybierz film (" << track.at(num).getMovie() << ") lub kliknij enter\n";
					for (int i = 0; i < movie.size(); i++)
					{
						std::cout << i + 1 << ". ";
						movie[i].getTitle();
					}
					std::cin >> buff;
					if (buff != "") 
					{
						int num1 = std::stoi(buff) - 1;
						if (num1 < movie.size())
						{
							track.at(num).setMovie(num1);
							std::cout << "Nowy film: " << track.at(num).getMovie() << "\n";
						}
					}
					else { std::cout << "Film bez zmian\n"; }
					//ROOM CHANGE
					std::cout << "Wybierz sale (" << track.at(num).getRoom() << ") lub kliknij enter\n";
					for (int i = 0; i < room.size(); i++)
					{
						std::cout << i + 1 << ". ";
						room[i].getName();
					}
					std::cin >> buff;
					if (buff != "")
					{
						int num1 = std::stoi(buff) - 1;
						if (num1 < room.size())
						{
							track.at(num).setRoom(num1);
							std::cout << "Nowa sala: " << track.at(num).getRoom() << "\n";
						}
					}
					else { std::cout << "Sala bez zmian\n"; }
					//TIME CHANGE
					std::tm ntt;
					std::cout << "Podaj date sensu w formacie DDMMYYYY lub kliknij enter\n";
					std::cin >> buff;
					if (buff != "") 
					{
						if (buff.length() != 8) throw;
						ntt.tm_mday = std::stoi(buff.substr(0, 2));
						ntt.tm_mon = std::stoi(buff.substr(2, 2)) - 1;
						ntt.tm_year = std::stoi(buff.substr(4, 4)) - 1900;
					}
					else { std::cout << "Data bez zmiany\n"; }
					std::cout << "Podaj godzine sensu w formacie HHMM:\n";
					std::cin >> buff;
					if (buff != "")
					{
						if (buff.length() != 4) throw;
						ntt.tm_hour = std::stoi(buff.substr(0, 2));
						ntt.tm_min = std::stoi(buff.substr(2, 2)) - 1;
					}
					track[num].setTime = ntt;
					std::cout << "Wprowadzono zmiany:\n";
					track[num].summarize();
				}
				else throw;
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