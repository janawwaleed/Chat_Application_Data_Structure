#include "dataBase.h"

map<int, User*> users;
User* currentUser = nullptr;
int currentUserID = 0;

int maxID() {
    int max = 0;
    for (auto& [id, user] : users) {
        if (id > max) max = id;
    }
    return max;
}

int maxChatID() {
    int max = 0;
    for (auto& [id, user] : users) {
        for (auto chatroom : user->chatRooms) {
            if (chatroom.getChatRoomID() > max) max = chatroom.getChatRoomID();
        }
    }
    return max;
}

int maxMessID() {
    int max = 0;
    for (auto& [id, user] : users) {
        for (auto chatroom : user->chatRooms) {
            for (auto mess : chatroom.getMessages())
                if (mess.getMessageID() > max)
                    max = mess.getMessageID();
        }
    }
    return max;
}

void to_json(json& j, const Story& s) {
    j = json{
        {"userID", s.userID},
        {"publishedTime", s.publishedTime},
        {"storyText", s.content},
        {"photoPath", s.photoPath},
        {"viewers_id", s.viewers},
    };
}

void to_json(json& j, const Message& m) {
    j = json{
        {"messageID", m.getMessageID()},
        {"userID", m.getUserID()},
        {"text", m.text},
        {"status", m.status},
        {"dateSent", m.dateSent},
        {"timeSent", m.timeSent},
        {"viewedBy", m.getViewedBy()} // Added viewedBy
    };
}

void to_json(json& j, const ChatRoom& cr) {
    j = json{
        {"chatRoomID", cr.getChatRoomID()},
        {"userIDs", cr.getUserIDs()},
        {"messages", cr.getMessages()},
        {"type", cr.type()}
    };

    if (!cr.gcAvatar.empty()) {
        j["groupAvatar"] = cr.gcAvatar;
    }
    if (!cr.gcName.empty()) {
        j["groupName"] = cr.gcName;
    }
}

void to_json(json& j, const ProfileDescription& p) {
    j = json{
        {"about", p.about},
        {"visibility", p.visibility}
    };
}

void to_json(json& j, const User& u) {
    j = json{
        {"id", u.getID()},
        {"Fname", u.Fname},
        {"Lname", u.Lname},
        {"avatar", u.avatar},
        {"password", u.getPassword()},
        {"number", u.getNumber()},
        {"lastSeen", u.lastSeen},
        {
            "contacts", [&] {
                json contactsJson = json::object();
                for (const auto& [id, name] : u.getContacts()) {
                    contactsJson[to_string(id)] = name;
                }
                return contactsJson;
            }()
        },
        {"chatRooms", u.chatRooms},
        {"profile", u.profile},
        {"stories", u.story}
    };

    if (u.selected) {
        j["selected"] = true;
        if(u.theme == 1) j["theme"] = 1;
        else j["theme"] = 0;
    }
}


void from_json(const json& j, Story& s) {
    j.at("userID").get_to(s.userID);
    j.at("publishedTime").get_to(s.publishedTime);
    j.at("storyText").get_to(s.content);
    j.at("photoPath").get_to(s.photoPath);
    j.at("viewers_id").get_to(s.viewers);
}

void from_json(const json& j, Message& m) {
    int messageID, userID;
    string text, status, dateSent, timeSent;
    vector<int> viewedBy;
    j.at("messageID").get_to(messageID);
    j.at("userID").get_to(userID);
    j.at("text").get_to(text);
    j.at("status").get_to(status);
    j.at("dateSent").get_to(dateSent);
    j.at("timeSent").get_to(timeSent);
    if (j.contains("viewedBy")) { // Handle backward compatibility
        j.at("viewedBy").get_to(viewedBy);
    }

    m = Message(messageID, userID, text);
    m.setStatus(status);
    m.dateSent = dateSent;
    m.timeSent = timeSent;
    m.setViewedBy(viewedBy);
}

void from_json(const json& j, ChatRoom& cr) {
    int chatRoomID;
    vector<int> userIDs;
    vector<Message> messages;

    j.at("chatRoomID").get_to(chatRoomID);
    j.at("userIDs").get_to(userIDs);
    j.at("messages").get_to(messages);

    string GcAvatar = j.value("groupAvatar", "");
    string GcName = j.value("groupName", "");

    cr = ChatRoom(chatRoomID, userIDs);
    cr.gcAvatar = GcAvatar;
    cr.gcName = GcName;
    cr.setMessages(messages);
}

void from_json(const json& j, ProfileDescription& p) {
    j.at("about").get_to(p.about);
    j.at("visibility").get_to(p.visibility);
}

void from_json(const json& j, User& u) {
    int id, number;
    string fname, lname, password, lastSeen;
    map<int, string> contacts;
    vector<ChatRoom> chatRooms;
    ProfileDescription profile;
    string Avatar;
    Story stories;
    bool select = false;
    int Theme = 0;

    j.at("id").get_to(id);
    j.at("Fname").get_to(fname);
    j.at("Lname").get_to(lname);
    j.at("avatar").get_to(Avatar);
    j.at("password").get_to(password);
    j.at("number").get_to(number);
    j.at("lastSeen").get_to(lastSeen);

    auto& contactsJson = j.at("contacts");
    if (contactsJson.is_object()) {
        for (auto it = contactsJson.begin(); it != contactsJson.end(); ++it) {
            contacts[stoi(it.key())] = it.value().get<string>();
        }
    }

    j.at("chatRooms").get_to(chatRooms);
    j.at("profile").get_to(profile);
    j.at("stories").get_to(stories);

    if (j.contains("selected")) {
        j.at("selected").get_to(select);
    }
    if (j.contains("theme")) {
        j.at("theme").get_to(Theme);
    }

    u = User(fname, lname, password, number, lastSeen, Avatar);
    u.setID(id);
    u.setContacts(contacts);
    u.chatRooms = chatRooms;
    u.profile = profile;
    u.story = stories;
    u.selected = select;
    u.theme = Theme;
}

void updateUsersToJson() {
    json j;
    ifstream inFile("userData.json");

    if (inFile.is_open()) {
        try {
            inFile >> j;
        }
        catch (const json::parse_error& e) {
            cerr << "Error parsing existing JSON: " << e.what() << endl;
            j = json::object();
        }
        inFile.close();
    }
    for (const auto& [id, user] : users) {
        json userJson;
        to_json(userJson, *user);
        j[to_string(id)] = userJson;
    }

    ofstream outFile("userData.json");
    if (!outFile.is_open()) {
        return;
    }

    outFile << j.dump(4);
    outFile.close();

}

void saveUsersToJson() {
    json j;

    ifstream inFile("userData.json");

    if (inFile.is_open()) {
        try {
            inFile >> j;
        }
        catch (const json::parse_error& e) {
            cerr << "Error parsing existing JSON: " << e.what() << endl;
            j = json::object(); // start fresh if file is corrupted
        }
        inFile.close();
    }

    for (const auto& [id, user] : users) {
        json userJson;
        to_json(userJson, *user);
        j[to_string(id)] = userJson;  // will add or overwrite by ID
    }

    ofstream outFile("userData.json");
    if (!outFile.is_open()) {
        cerr << "Failed to open userData.json for writing.\n";
        return;
    }

    outFile << j.dump(4);  // Pretty print with indentation
    outFile.close();

    cout << " Users saved to userData.json successfully!\n";
}


void loadFromJson() {
    ifstream file("userData.json");
    if (!file.is_open()) {
        cerr << "Failed to open userData.json for reading.\n";
        return;
    }

    json j;
    file >> j;
    file.close();

    for (auto& [id, user] : users) {
        delete user;
    }
    users.clear();

    for (auto& [idStr, userJson] : j.items()) {
        int id = stoi(idStr);
        User* user = new User("", "", "", 0, "", "");
        from_json(userJson, *user);
        users[id] = user;
    }
}

int getUserByNumber(int num) {
    for (const auto& [id, user] : users) {
        if (user->getNumber() == num) {
            return user->getID();
        }
    }
    return -1;
}
