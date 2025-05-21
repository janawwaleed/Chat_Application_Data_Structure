#pragma once
#include<iostream>
#include<vector>
#include<unordered_set>
#include"Message.h"
using namespace std;

class ChatRoom {
private:
    int chatRoomID;
    vector<int> userIDs;
    vector<Message> messages;
    unordered_set<int> viewedBy; // Tracks which users have viewed this chat

public:
    ChatRoom();
    ChatRoom(int chatRoomID, vector<int> userIDs);
    string gcAvatar;
    string gcName;
    int getChatRoomID() const;
    const vector<Message>& getMessages() const;
    vector<int> getUserIDs() const;
    void setMessages(const vector<Message>& msgs);
    string type() const;
    void setChatRoomID(int newid);
    void addMesaages(const Message& m);
    int maxMessID();
    void removeMessage(int messageId);

   
};