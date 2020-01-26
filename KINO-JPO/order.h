#pragma once

class Order
{
public:
	Order();
	Order(int, int, int);
	~Order();

	void setOrder(int);
	void setUser(int);
	void setTrack(int);
	int getOrder();
	int getUser();
	int getTrack();

	void summarize();

private:
	int orderID;
	int userID;
	int trackID;
};