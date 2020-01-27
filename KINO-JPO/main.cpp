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
#include "order.h"

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
std::map<int, Order> order;

int setup();
void save();
void serve(int);
int admin();

int main()
{


	srand((unsigned int)time(NULL));

	if (!setup()) return -1;

	std::string buff = "";
	while (1) //main loop
	{
		std::cout << "Witamy w kinie!\nPodaj numer uzytkownika lub wpisz \"nowy\"\n";
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
			user[(int)user.size()] = newuser;
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
					int unb = 0;
					for (int i = 0; i < (int)user.size(); i++)
					{
						if (user.at(i).get_ID() == uID)
						{
							unb = i;
							break;
						}
					}
					if (user[unb].match(std::stoi(buff))) 
					{
						serve(unb);
					}
					else
					{
						std::cout << "Zle haslo\n"; //...
					}
				}
				catch (std::invalid_argument) {
					std::cout << "ERR: no conversion could be performed\n";
				}
				catch (std::out_of_range) {
					std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
				}
			}
			else { serve((int)user.size() - 1); }
		}
	}
	save();
}

void serve(int uid) {
	while(1)
	{
		std::string buff = "";
		std::cout << "a - dodaj zamowienie\nb - wyswietl zamowienia\nexit - wyjdz\n";
		std::cin >> buff;
		if (buff == "a" || buff == "A") //add order
		{
			std::cout << "Wybierz seans\n";
			for (size_t i = 0; i < track.size(); i++)
			{
				std::cout << i + 1 << ". " << movie.at(track[(int)i].getMovie()).getTitle() << "    " << track[(int)i].getTimeStr() << "\n";
			}
			std::cin >> buff;
			try {
				size_t num = (size_t)std::stoul(buff) - 1;
				if (num < track.size())
				{
					int times = 0;
					std::cout << "Ile biletow chcesz zarezerwowac?\n";
					std::cin >> times;
					track.at((const int)num).clearSeats(room.at(track.at((const int)num).getRoom()).getColumns()*room.at(track.at((const int)num).getRoom()).getRows());
					std::cout << "  ";
					for (int j = 1; j <= room.at(track.at((const int)num).getRoom()).getColumns(); j++) std::cout << (j < 10 ? "  " : " ") << j;
					std::cout << "\n";
					for (int i = 0; i < room.at(track.at((const int)num).getRoom()).getRows(); i++)
					{
						std::cout << (i + 1 < 10 ? " " : "") << i + 1;
						for (int j = 0; j < room.at(track.at((const int)num).getRoom()).getColumns(); j++)
							std::cout << "  " << track.at((const int)num).getSeat(i*room.at(track.at((const int)num).getRoom()).getColumns() + j);
						std::cout << "\n";
					}
					while (1) {
						std::cout << "Wybierz rzad\n";
						int row = 0;
						std::cin >> row;
						row--;
						int free_seats = 0;
						for (int i = room.at(track.at((const int)num).getRoom()).getColumns() * row; i < room.at(track.at((const int)num).getRoom()).getColumns() * (row + 1); i++)
							if (track.at((const int)num).getSeat(i) == 'O') free_seats++;
						if (free_seats < times)
						{
							std::cout << "Za malo miejsc w rzedzie\n";
							continue;
						}
						for (int k = 0; k < times; k++)
						{
							int col = 0;
							while (1)
							{
								std::cout << "Wybierz miejsce\n";
								std::cin >> col;
								if (track.at((const int)num).getSeat(room.at(track.at((const int)num).getRoom()).getColumns() * row + col - 1) == 'X')
								{
									std::cout << "Wybrane miejsce jest zajete\n";
									continue;
								}
								else break;
							}
							track.at((const int)num).bookSeat(room.at(track.at((const int)num).getRoom()).getColumns() * row + col - 1, uid);
							if (k == 0)
							{
								Order _order((int)order.size(), uid, (const int)num, 1);
								order[(int)order.size()] = _order;
							}
							else { order[(int)order.size() - 1].incTickets(); }
						}
						std::cout << "Zarezerwowano\n";
						break;
					}
				}
				else { throw "wrong number"; }
			}
			catch (char * err) {
				std::cout << "ERR: " << err << "\n";
			}
			catch (std::invalid_argument) {
				std::cout << "ERR: no conversion could be performed\n";
			}
			catch (std::out_of_range) {
				std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
			}

		}
		if (buff == "b" || buff == "B") //see orders
		{
			std::map<int, int> orderlist;
			int counter = 0;
			std::cout << "Aby zobaczyc szczogoly wybierz zamowienie lub kliknij 0 aby wyjsc\n";
			for (int i = 0; i < (int)order.size(); i++)
			{
				if (order.at(i).getUser() == uid) 
				{	
					std::cout << i + 1 << ". " << movie.at(track.at(order.at(i).getTrack()).getMovie()).getTitle() << "   ";
					std::cout << track.at(order.at(i).getTrack()).getTimeStr() << "  Bilety: " << order.at(i).getTickets() << "\n";
					orderlist[counter] = i;
					std::cout << orderlist.at(counter);
					counter++;
				}
			}
			int num = 0;
			//std::cin >> buff;
			std::cin >> num;
			//std::cin.clear();
			//std::cin.ignore();
			num--;
			if (num == -1) break; 
			try
			{
				//int num = ((int)std::stoul(buff)) - 1;
				if (num < counter) 
				{
					std::cout << "Zarezerwowane miejsca: \n";
					for (int i = 0; i < room.at(track.at(order.at(orderlist.at(num)).getTrack()).getRoom()).getColumns() * room.at(track.at(order.at(orderlist.at(num)).getTrack()).getRoom()).getRows(); i++)
						if (track.at(order.at(orderlist.at(num)).getTrack()).getSeatUID(i) == uid) std::cout << "R:" << (i / (room.at(track.at(order.at(orderlist.at(num)).getTrack()).getRoom()).getColumns() + 1)) + 1 << " M: " << (i % (room.at(track.at(order.at(orderlist.at(num)).getTrack()).getRoom()).getColumns() + 1)) + 1 << "\n"; else
						{
							std::cout << "wtf\n";
						}
				}
				else throw "wrong number";
			}
			catch (char * err) {
				std::cout << "ERR: " << err << "\n";
			}
			catch (std::invalid_argument) {
				std::cout << "ERR: no conversion could be performed\n";
			}
			catch (std::out_of_range) {
				std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
			}
		}
		if (buff == "exit") break;
	}
}

int admin() {
	while (1) {
		std::string buff = "";
		std::cout << "a - dodaj film\nb - zmien tytul filmu\nc - dodaj sale\nd - edytuj sale\ne - dodaj seans\nf - edytuj seans\ng - wyswietl filmy\nh - wyswietl sale\ni - wyswietl seanse\nj - wyswietl zamowienia\nsave - zapisz stan\nexit - wyjdz z trybu administratora\nshutdown - zakoncz program\n";
		std::cin >> buff;
		if (buff == "a" || buff == "A") //new movie
		{
			std::cout << "Podaj tytul nowego filmu\n";
			std::cin >> buff;
			Movie newmovie(buff);
			movie[(int)movie.size()] = newmovie;
			std::cout << "Dodano film: " << movie[(int)movie.size() - 1].getTitle() << "\n";
		}
		if (buff == "b" || buff == "B") //edit movie
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
			catch (std::invalid_argument) {
				std::cout << "ERR: no conversion could be performed\n";
			}
			catch (std::out_of_range) {
				std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
			}
		}
		if (buff == "c" || buff == "C") //new room
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
				room[(short)room.size() - 1].summarize();
			}
			catch (char * err) {
				std::cout << "ERR: " << err << "\n";
			}
			catch (std::invalid_argument) {
				std::cout << "ERR: no conversion could be performed\n";
			}
			catch (std::out_of_range) {
				std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
			}
		}
		if (buff == "d" || buff == "D") //edit room
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
			catch (std::invalid_argument) {
				std::cout << "ERR: no conversion could be performed\n";
			}
			catch (std::out_of_range) {
				std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
			}
		}
		if (buff == "e" || buff == "E") //new track
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
						Track newtrack((const int)track.size(), (int)num2, (int)num1, ntt, room.at((const int)num1).getColumns(), room.at((const int)num1).getRows());
						track[(int)track.size()] = newtrack;
						track[(int)track.size() - 1].clearSeats(room.at(track[(int)track.size() - 1].getRoom()).getColumns() * room.at(track[(int)track.size() - 1].getRoom()).getRows());
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
			catch (std::invalid_argument) {
				std::cout << "ERR: no conversion could be performed\n";
			}
			catch (std::out_of_range) {
				std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
			}
		}
		if (buff == "f" || buff == "F") //edit track 
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
			catch (std::invalid_argument) {
				std::cout << "ERR: no conversion could be performed\n";
			}
			catch (std::out_of_range) {
				std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
			}
		}
		if (buff == "g" || buff == "G") //print out movies
		{
			for (size_t i = 0; i < movie.size(); i++)
			{
				std::cout << i + 1 << ". " << movie[(int)i].getTitle() << "\n";
			}
		}
		if (buff == "h" || buff == "H") //print out rooms
		{
			for (size_t i = 0; i < room.size(); i++)
			{
				std::cout << i + 1 << ". ";
				room[(int)i].summarize();
			}
		}
		if (buff == "i" || buff == "I") //print out tracks
		{
			for (size_t i = 0; i < track.size(); i++)
			{
				std::cout << i + 1 << ". ";
				track[(int)i].summarize();
			}
		}
		if (buff == "j" || buff == "J") 
		{
		
		}//TODO: print out orders
		if (buff == "save") save();
		if (buff == "shutdown") return 0;
		if (buff == "exit") break;
	}
	return 1;
}

int setup()
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
		{
			std::ifstream file("user.txt");
			if (!file.is_open()) throw "user.txt not opened";
			std::cout << "Loading users\n";
			std::getline(file, buff[0]);
			while (!file.eof())
			{
				for (int i = 0; i < 2; i++) {
					if (file.eof()) throw "reading user.txt failed";
					std::getline(file, buff[i]);
				}
				User _user(std::stoi(buff[0]), std::stoi(buff[1]));
				user[it] = _user;
				it++;
			}
			file.close();
			std::cout << it << " users loaded\n";
			it = 0;
		}
		std::cout << "Setup complete\n";
		return 1;
	}
	catch (const char* err) {
		std::cout << "ERR: " << err << "\n";
		return 1;
	}
	catch (std::invalid_argument) {
		std::cout << "ERR: no conversion could be performed\n";
	}
	catch (std::out_of_range) {
		std::cout << "ERR: the converted value would fall out of the range of the result type or the underlying function(std::strtol or std::strtoll) set errno to ERANGE\n";
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
				file << room.at((const int)s).getRows() << std::endl;
				file << room.at((const int)s).getColumns();
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
		{
			std::ofstream file("user.txt", std::ios::trunc);
			if (!file.is_open()) throw "user.txt not opened";
			std::cout << "Saving users\n";
			for (size_t s = 0; s < user.size(); s++)
			{
				file << std::endl << user.at((const int)s).get_ID() << std::endl;
				file << user.at((const int)s).get_pass();
			}
			file.close();
			std::cout << user.size() << " users saved\n";
		}
		std::cout << "Saving complete\n";
	}
	catch (const char* err) {
		std::cout << "ERR: " << err << "\n";
	}
}