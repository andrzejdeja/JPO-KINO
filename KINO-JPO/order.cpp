#include "order.h"
#include <iostream>

Order::Order()
{
	orderID = 0;
	userID = 0;
	trackID = 0;
	tickets = 0;
}

Order::Order(int _orderID, int _userID, int _trackID, int _tickets) : orderID(_orderID), userID(_userID), trackID(_trackID), tickets(_tickets)
{
}

Order::~Order()
{
}

void Order::setOrder(int _orderID)
{
	orderID = _orderID;
}

void Order::setUser(int _userID)
{
	userID = _userID;
}

void Order::setTrack(int _trackID)
{
	trackID = _trackID;
}

void Order::setTickets(int _tickets)
{
	tickets = _tickets;
}

int Order::getOrder() { return orderID; }

int Order::getUser() { return userID; }

int Order::getTrack() { return trackID; }

int Order::getTickets() { return tickets; }

void Order::incTickets() { tickets++; }

void Order::summarize() { std::cout << "ID: " << orderID << " User: " << userID << "Track: " << trackID << "\n"; }