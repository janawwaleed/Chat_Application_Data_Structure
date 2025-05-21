#pragma once
#include <fstream>
#include <json.hpp>
#include <iostream>
#include <string>
#include <map>
#include "User.h"
#include "ChatRoom.h"
#include "Message.h"
#include "Story.h"
#include "ProfileDescription.h"
using json = nlohmann::json;
using namespace std;

extern map<int, User*> users;
extern int currentUserID;
int maxID();
int maxChatID();
int maxMessID();

void to_json(json& j, const Story& s);
void to_json(json& j, const Message& m);
void to_json(json& j, const ChatRoom& cr);
void to_json(json& j, const ProfileDescription& p);
void to_json(json& j, const User& u);

void from_json(const json& j, Story& s);
void from_json(const json& j, Message& m);
void from_json(const json& j, ChatRoom& cr);
void from_json(const json& j, ProfileDescription& p);
void from_json(const json& j, User& u);

void updateUsersToJson();
void saveUsersToJson();
void loadFromJson();
int getUserByNumber(int num);