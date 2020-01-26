#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <map>
#include <vector>
#include <string>
#include <inttypes.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>

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
std::map<int, User> user;
std::map<int, Room> room;
std::map<int, Track> track;

void setup();
void save();
void serve(int);
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
		int uID = 0; 
		int pass = 0;
		if (buff == "nowy") //create new user
		{
			short f = 1;
			while (f)
			{
				uID = rand();
				f = 0;
				if (uID == 0) 
				{
					f = 1;
					continue;
				}
				for (size_t i = 0; i < user.size(); i++)
				{
					if (uID == user[(int)i].get_ID())
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
					uID = std::stoi(buff, 0, 10);
					std::cout << "Podaj haslo\n";
					std::cin >> buff;
					if (user[uID].match((short)std::stoi(buff))) serve(uID);
				}
				catch (...) { //TODO: zamienic na typy stoi, zrobic dla wszystkich catch
					std::cout << "ERR\n";
				}
			}
			else { serve(uID); }
		}
	}
	save();
}

void serve(int num) {
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
			for (size_t i = 0; i < movie.size(); i++)
			{
				std::cout << i + 1 << ". " << movie[(const int)i].getTitle() << "\n";
			}
			std::cin >> buff;
			try {
				size_t num = (size_t)std::stoul(buff) - 1;
				if ( num < movie.size())
				{
					std::cout << "Podaj nowy tytul " << movie.at((const int)num).getTitle() << ":\n";
					std::cin >> buff;
					movie.at((const int)num).modifyTitle(buff);
					std::cout << "Nowy tytul to: " << movie.at((const int)num).getTitle() << "\n";
				}
				else throw "wrong number";
			}
			catch (char * err) {
				std::cout << "ERR: " << err << "\n";
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
				if (std::stoi(buff) <= 0) throw "wrong number";
				short rows = (short)std::stoi(buff);
				std::cout << "Podaj liczbe miejsc w rzedzie\n";
				std::cin >> buff;
				if (std::stoi(buff) <= 0) throw "wrong number";
				short columns = (short)std::stoi(buff);
				Room newroom(name, rows, columns);
				room[(short)room.size()] = newroom;
				std::cout << "Dodano sale:\n";
				room[(short)room.size() - 1].display();
			}
			catch (char * err) {
				std::cout << "ERR: " << err << "\n";
			}
		}
		if (buff == "d" || buff == "D")
		{
			std::cout << "Podaj numer sali\n";
			for (size_t i = 0; i < room.size(); i++)
			{
				std::cout << i + 1 << ". ";
				room[(int)i].summarize();
			}
			std::cin >> buff;
			try {
				size_t num = (size_t)std::stoul(buff) - 1;
				if (num < room.size())
				{
					std::cout << "Podaj nowa nazwe (" << room.at((const int)num).getName() << ") lub C aby pominac\n";
					std::cin >> buff;
					if (buff != "C" && buff != "c") room.at((const int)num).setName(buff);
					std::cout << "Nowa nazwa to: " << room.at((const int)num).getName() << "\n";
					std::cout << "Podaj nowa ilosc rzedow w sali (" << room.at((const int)num).getRows() << ") lub C aby pominac\n";
					std::cin >> buff;
					if (buff != "C" && buff != "c") room.at((const int)num).setRows((short)stoi(buff));
					std::cout << "Nowa ilosc rzedow w sali to: " << room.at((const int)num).getRows() << "\n";
					std::cout << "Podaj nowa ilosc miejsc w rzedzie (" << room.at((const int)num).getColumns() << ") lub C aby pominac\n";
					std::cin >> buff;
					if (buff != "C" && buff != "c") room.at((const int)num).setColumns((short)stoi(buff));
					std::cout << "Nowa ilosc miejsc w rzedzie to: " << room.at((const int)num).getColumns() << "\n";
				}
				else throw "wrong number";
			}
			catch (char * err) {
				std::cout << "ERR: " << err << "\n";
			}
		}
		if (buff == "e" || buff == "E")
		{
			try {
				std::cout << "Podaj numer sali\n";
				for (size_t i = 0; i < room.size(); i++)
				{
					std::cout << i + 1 << ". ";
					room[(int)i].summarize();
				}
				std::cin >> buff;
				size_t num1 = (size_t)std::stoul(buff) - 1;
				if (num1 < room.size())
				{
					std::cout << "Podaj numer filmu\n";
					for (size_t i = 0; i < movie.size(); i++)
					{
						std::cout << i + 1 << ". " << movie[(int)i].getTitle() << "\n";
					}
					std::cin >> buff;
					size_t num2 = (size_t)std::stoul(buff) - 1;
					if (num2 < movie.size()) 
					{
						time_t t;
						time(&t);
						struct tm ntt;
						localtime_s(&ntt, &t);
						std::cout << "Podaj date sensu w formacie DDMMYYYY:\n";
						std::cin >> buff;
						if (buff.length() != 8) throw "wrong date format";
						ntt.tm_mday = std::stoi(buff.substr(0, 2));
						ntt.tm_mon = std::stoi(buff.substr(2, 2)) - 1;
						ntt.tm_year = std::stoi(buff.substr(4, 4)) - 1900;
						std::cout << "Podaj godzine sensu w formacie HHMM:\n";
						std::cin >> buff;
						if (buff.length() != 4) throw "wrong hour format";
						ntt.tm_hour = std::stoi(buff.substr(0, 2));
						ntt.tm_min = std::stoi(buff.substr(2, 2));
						ntt.tm_sec = 0;
						Track newtrack((const int)track.size(), (int)num2, (int)num1, ntt, room.at((const int)num1).getColumns(), room.at((const int)num1).getRows()); //TODO: FIND WHY (int)track.size() is negative !?!?!?
						track[(int)track.size()] = newtrack;
						std::cout << "Dodano seans:\n";
						track[(int)track.size() - 1].summarize();
					}
					else throw "wrong number";
				}
				else throw "wrong number";
			}
			catch (char * err) {
				std::cout << "ERR: " << err << "\n";
			}
		}
		if (buff == "f" || buff == "F")
		{
			std::cout << "Podaj numer seansu\n";
			for (size_t i = 0; i < track.size(); i++)
			{
				std::cout << i + 1 << ". ";
				track[(int)i].summarize();
			}
			std::cin >> buff;
			try {
				size_t num = (size_t)std::stoul(buff) - 1;
				if (num < track.size())
				{
					//MOVIE CHANGE
					std::cout << "Wybierz film (" << track.at((const int)num).getMovie() + 1 << ") lub C aby pominac\n";
					for (size_t i = 0; i < movie.size(); i++)
					{
						std::cout << i + 1 << ". " << movie[(int)i].getTitle() << "\n";
					}
					std::cin >> buff;
					if (buff != "C" && buff != "c")
					{
						size_t num1 = (size_t)std::stoul(buff) - 1;
						if (num1 < movie.size())
						{
							track.at((const int)num).setMovie((const int)num1);
							std::cout << "Nowy film: " << track.at((const int)num).getMovie() + 1 << "\n";
						}
					}
					else { std::cout << "Film bez zmian\n"; }
					//ROOM CHANGE
					std::cout << "Wybierz sale (" << track.at((const int)num).getRoom() + 1 << ") lub C aby pominac\n";
					for (size_t i = 0; i < room.size(); i++)
					{
						std::cout << i + 1 << ". " << room[(int)i].getName() << "\n";
					}
					std::cin >> buff;
					if (buff != "C" && buff != "c")
					{
						size_t num1 = (size_t)std::stoul(buff) - 1;
						if (num1 < room.size())
						{
							track.at((const int)num).setRoom((const int)num1);
							std::cout << "Nowa sala: " << track.at((const int)num).getRoom() + 1 << "\n";
						}
					}
					else { std::cout << "Sala bez zmian\n"; }
					//TIME CHANGE
					time_t t;
					time(&t);
					struct tm ntt;
					localtime_s(&ntt, &t);
					std::cout << "Podaj date sensu w formacie DDMMYYYY lub C aby pominac\n";
					std::cin >> buff;
					if (buff != "C" && buff != "c") 
					{
						if (buff.length() != 8) throw "wrong date";
						ntt.tm_mday = std::stoi(buff.substr(0, 2));
						ntt.tm_mon = std::stoi(buff.substr(2, 2)) - 1;
						ntt.tm_year = std::stoi(buff.substr(4, 4)) - 1900;
					}
					else
					{
						ntt.tm_mday = track.at((const int)num).getTime().tm_mday;
						ntt.tm_mon = track.at((const int)num).getTime().tm_mon;
						ntt.tm_year = track.at((const int)num).getTime().tm_year;
						std::cout << "Data bez zmiany\n";
					}
					std::cout << "Podaj godzine sensu w formacie HHMM lub C aby pominac\n";
					std::cin >> buff;
					if (buff != "C" && buff != "c")
					{
						if (buff.length() != 4) throw "wrong hour";
						ntt.tm_hour = std::stoi(buff.substr(0, 2));
						ntt.tm_min = std::stoi(buff.substr(2, 2));
						ntt.tm_sec = 0;
					}
					else 
					{
						ntt.tm_hour = track.at((const int)num).getTime().tm_hour;
						ntt.tm_min = track.at((const int)num).getTime().tm_min;
						ntt.tm_sec = track.at((const int)num).getTime().tm_sec;
						std::cout << "Godzina bez zmiany\n";
					}
					//time_t t = mktime(&ntt);
					//ntt = localtime(&t);
					track.at((const int)num).setTime(ntt);
					std::cout << "Wprowadzono zmiany:\n";
					track.at((const int)num).summarize();
				}
				else throw "wrong number";
			}
			catch (char * err) {
				std::cout << "ERR: " << err << "\n";
			}
		}
		if (buff == "shutdown") return 0;
		if (buff == "exit") break;
	}
	return 1;
}

void setup()
{
	try {
		std::string buff[10];
		int it = 0;
		{
			std::ifstream file("room.txt");
			if (!file.is_open()) throw "room.txt not opened";
			std::cout << "Loading rooms\n";
			std::getline(file, buff[0]);
			while (!file.eof())
			{
				for (int i = 0; i < 3; i++) {
					if (file.eof()) throw "reading room.txt failed";
					std::getline(file, buff[i]);
				}
				Room _room(buff[0], (short)std::stoi(buff[1]), (short)std::stoi(buff[2]));
				room[it] = _room;
				it++;
			}
			file.close();
			std::cout << it << " rooms loaded\n";
			it = 0;
		}
		{
			std::ifstream file("track.txt");
			if (!file.is_open()) throw "track.txt not opened";
			std::cout << "Loading tracks\n";
			std::getline(file, buff[0]);
			while (!file.eof())
			{
				for (int i = 0; i < 4; i++) {
					if (file.eof()) throw "reading track.txt failed";
					std::getline(file, buff[i]);
				}
				time_t t;
				time(&t);
				struct tm ntt;
				localtime_s(&ntt, &t);
				ntt.tm_hour = std::stoi(buff[3].substr(0, 2));
				ntt.tm_min = std::stoi(buff[3].substr(2, 2));
				ntt.tm_sec = 0;
				ntt.tm_mday = std::stoi(buff[3].substr(4, 2));
				ntt.tm_mon = std::stoi(buff[3].substr(6, 2));
				ntt.tm_year = std::stoi(buff[3].substr(8, 4));
				//std::istringstream input(buff[3]);
				//input >> std::get_time(&tm1, "%H%M%d%m%Y");
				Track _track(std::stoi(buff[0]), std::stoi(buff[1]), std::stoi(buff[2]), ntt, room.at(std::stoi(buff[2])).getColumns(), room.at(std::stoi(buff[2])).getRows());
				track[std::stoi(buff[0])] = _track;
				it++;
			}
			file.close();
			std::cout << it << " tracks loaded\n";
			it = 0;
		}
		{
			std::ifstream file("movie.txt");
			if (!file.is_open()) throw "movie.txt not opened";
			std::cout << "Loading movies\n";
			std::getline(file, buff[0]);
			while (!file.eof())
			{
				std::getline(file, buff[0]);
				Movie _movie(buff[0]);
				movie[it] = _movie;
				it++;
			}
			file.close();
			std::cout << it << " movies loaded\n";
			it = 0;
		}
		std::cout << "Setup complete\n";
	}
	catch (const char* err) {
		std::cout << "ERR: " << err << "\n";
	}
	
}

void save() {
	try {
		{
			std::ofstream file("room.txt", std::ios::trunc);
			if (!file.is_open()) throw "room.txt not opened";
			std::cout << "Saving rooms\n";
			for (size_t s = 0; s < room.size(); s++)
			{
				file << std::endl << room.at((const int)s).getName() << std::endl;
				file << room.at((const int)s).getColumns() << std::endl;
				file << room.at((const int)s).getRows();
			}
			file.close();
			std::cout << room.size() << " rooms saved\n";
		}
		{
			std::ofstream file("track.txt", std::ios::trunc );
			if (!file.is_open()) throw "track.txt not opened";
			std::cout << "Saving tracks\n";
			for (size_t s = 0; s < track.size(); s++)
			{
				file << std::endl << track.at((const int)s).getID() << std::endl;
				file << track.at((const int)s).getMovie() << std::endl;
				file << track.at((const int)s).getRoom() << std::endl;
				tm tm1 = track.at((const int)s).getTime();
				//std::strftime((char *)&buff, sizeof(buff), "%H%M%d%m%Y", &tm1);
				file << (tm1.tm_hour < 10 ? "0" : "") << tm1.tm_hour << (tm1.tm_min < 10 ? "0" : "") << tm1.tm_min << (tm1.tm_mday < 10 ? "0" : "") << tm1.tm_mday << (tm1.tm_mon < 10 ? "0" : "") << tm1.tm_mon << (tm1.tm_year < 1000 ? "0" : "") << tm1.tm_year;
			}
			file.close();
			std::cout << track.size() << " tracks saved\n";
		}
		{
			std::ofstream file("movie.txt", std::ios::trunc);
			if (!file.is_open()) throw "movie.txt not opened";
			std::cout << "Saving movies\n";
			for (size_t s = 0; s < track.size(); s++)
			{
				file << std::endl << movie.at((const int)s).getTitle();
			}
			file.close();
			std::cout << movie.size() << " movies saved\n";
		}
		std::cout << "Saving complete\n";
	}
	catch (const char* err) {
		std::cout << "ERR: " << err << "\n";
	}

}