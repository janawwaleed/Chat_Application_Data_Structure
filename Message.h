#pragma once
#include <vector>
#include <QDateTime>
#include <iostream>
#include <string>
using namespace std;
class Message
{
private:
    int messageID;
    int userID;
    vector<int> viewedBy; // Tracks user IDs who have viewed the message

public:
    string text;
    string status;
    string dateSent;
    string timeSent;
    Message();
    Message(int messageID, int userID, string text);
    int getMessageID() const;
    int getUserID() const;
    void setStatus(const string& newStatus);
    string getStatus() const;
    const vector<int>& getViewedBy() const; // Get viewedBy list
    void addViewer(int userId); // Add a viewer
    void setViewedBy(const vector<int>& viewers); // Set viewedBy list
};