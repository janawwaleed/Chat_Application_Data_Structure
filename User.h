#pragma once
#include <iostream>
#include <vector>
#include "Story.h"
#include "ChatRoom.h"
#include "ProfileDescription.h"
#include "Message.h"
using namespace std;

class User{
private:
	int id;
	int number;
	string password;
	map<int, string> userContacts;
	
public:
	string Fname, Lname;
	string avatar;
	string lastSeen;
	vector<ChatRoom> chatRooms;
	ProfileDescription profile;
	Story story; 
	bool selected;
	int theme;

	string getNameFromContacts(int ID);
	int getID() const;
	int getNumber() const;
	void setID(int newID);
	void setNumber(int newNumber);
	void setPassword(string newPassword);
	map<int, string> getContacts() const;
	void addContacts(int n, string s);
	void setContacts(map<int, string> map);
	string getPassword() const;
	void addChatRoom(ChatRoom c);
	User(string Fname, string Lname, string password, int number, string lastSeen, string avatar);
};

