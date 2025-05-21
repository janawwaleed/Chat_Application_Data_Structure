#include "Message.h"
//SAMA
Message::Message() : messageID(0), userID(0), text(""), status("unseen"), dateSent(""), timeSent("") {}

Message::Message(int messageID, int userID, string text)
    : messageID(messageID), userID(userID), text(text), status("unseen"),
    dateSent(QDate::currentDate().toString("yyyy-MM-dd").toStdString()),
    timeSent(QTime::currentTime().toString("HH:mm").toStdString()) {}

int Message::getMessageID() const {
    return messageID;
}

int Message::getUserID() const {
    return userID;
}

void Message::setStatus(const string& newStatus) {
    status = newStatus;
}

  string Message::getStatus() const {
    return status;
}

const vector<int>& Message::getViewedBy() const {
    return viewedBy;
}

void Message::addViewer(int userId) {
    if (std::find(viewedBy.begin(), viewedBy.end(), userId) == viewedBy.end()) {
        viewedBy.push_back(userId);
    }
}

void Message::setViewedBy(const vector<int>& viewers) {
    viewedBy = viewers;
}