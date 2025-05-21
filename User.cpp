#include "User.h"



string User::getNameFromContacts(int number) {
    for (const auto& [num, name] : userContacts) {
        if (number == num) {
            return name;
        }
    }
    return "";
}
int User::getID() const {
    return id;
}

string User::getPassword() const {
    return password;
}

int User::getNumber() const {
    return number;
}

map<int, string> User::getContacts() const {
    return userContacts;
}

void User::addContacts(int n, string s){
    userContacts[n] = s;
}

void User::setContacts(map<int, string> map){
    userContacts = map;
}

void User::setID(int newID) {
    id = newID;
}

void User::setNumber(int newNumber) {
    number = newNumber;
}

void User::setPassword(string newPassword) {
    password = newPassword;
}


User::User(string Fname, string Lname, string password, int number, string lastSeen, string avatar="") 
    : Fname(Fname), Lname(Lname), password(password), number(number), lastSeen(lastSeen), avatar(avatar) {
    id = 1; 
}


void User:: addChatRoom(ChatRoom c) {
    chatRooms.push_back(c);
}

