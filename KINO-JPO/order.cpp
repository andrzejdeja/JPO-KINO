#include "order.h"
#include <iostream>

Order::Order()
{
	orderID = 0;
	userID = 0;
	trackID = 0;
}

Order::Order(int _orderID, int _userID, int _trackID) : orderID(_orderID), userID(_userID), trackID(_trackID) 
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

int Order::getOrder() { return orderID; }

int Order::getUser() { return userID; }

int Order::getTrack() { return trackID; }

void Order::summarize() { std::cout << "ID: " << orderID << " User: " << userID << "Track: " << trackID << "\n"; }