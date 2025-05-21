#pragma once
#include <vector>
#include <QDateTime>
#include <iostream>
using namespace std;

class Story{

public:
	int userID;
	string content;
	string photoPath;
	string publishedTime;
	bool available;
	vector<int>viewers;

public:
	Story();
	Story(int userID, string publishedTime , string content,string photopath );
		
	
	//Story(string publishedTime, string content, string photoPath);
		
};


