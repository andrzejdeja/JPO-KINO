#pragma once

class Order
{
public:
	Order();
	Order(int, int, int, int);
	~Order();

	void setOrder(int);
	void setUser(int);
	void setTrack(int);
	void setTickets(int);
	int getOrder();
	int getUser();
	int getTrack();
	int getTickets();
	void incTickets();

	void summarize();

private:
	int orderID;
	int userID;
	int trackID;
	int tickets;
};