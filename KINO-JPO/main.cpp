#include <iostream>
#include <vector>
#include <string>

/*
59. Design and implement classes for a cinema booking system, user can select movie,
room, time, seats and place order. The system includes following object: movie,
room, track(in which room when which movie is showing), seat, user, order(a user
books which track and which seats) Additionally, this system can be extended to be
used for cinema administrator to plan movie(when to plan which movie in which
room) in order to get the most audience and income.
*/

int main()
{
	std::string buff = "";
	while (1) //main loop
	{
		std::cout << "Witamy w kinie!\nPodaj numer uzytkownika lub wpisz \"nowy\", aby utworzyc nowe zamowienie\n";
		std::cin >> buff;
		if (buff == "nowy") //create new user
		{
			
		}
		else if (buff == "admin") //admin
		{
			std::cout << "Panel administratora\nPodaj haslo: ";
			std::cin >> buff;
			if (buff == "1234") {
				std::cout << "<Opcje admina>\nexit - zakoncz program";
				std::cin >> buff;
				if (buff == "exit") break;
			}
		}
		else //serve user
		{
		
		}
	}
}