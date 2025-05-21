#include "ChatRoom.h"
#include<iostream>
#include<Vector>
using namespace std;

ChatRoom::ChatRoom() : chatRoomID(0), userIDs({}), messages({}) {}

ChatRoom::ChatRoom(int chatRoomID, vector<int> userIDs)
    : chatRoomID(chatRoomID), userIDs(userIDs){
    chatRoomID = 100;
}

void ChatRoom::setChatRoomID(int newid) {
    chatRoomID = newid;
}

void ChatRoom::addMesaages(const Message& m){
    messages.push_back(m);
}

int ChatRoom::getChatRoomID() const{
    return chatRoomID;
}

vector<int>ChatRoom::getUserIDs() const {
    return userIDs;
}

const vector<Message>& ChatRoom::getMessages() const {
    return messages;
}


void ChatRoom::setMessages(const vector<Message>& msgs) {
    messages = msgs;
}


string ChatRoom:: type() const{
    if (getUserIDs().size() > 2) {
        return "Group";
    }
    else {
        return "Private";
    }
}
//////////////SAMA/////////////SAMA//////////SAMA//////////SAMA////////////
int ChatRoom::maxMessID() {
    int max = 0;
    for (auto message : messages) {
        if (message.getMessageID() > max) max = message.getMessageID();
    }
    return max;
}

//////SAMA/////////SAMA////////////SAMA//////////SAMA/////////////
void ChatRoom::removeMessage(int messageId) {
    auto& messages = this->messages; // Non-const access to internal vector
    auto it = find_if(messages.begin(), messages.end(),
        [messageId](const Message& msg) { return msg.getMessageID() == messageId; });
    if (it != messages.end()) {
        messages.erase(it);
    }
}





