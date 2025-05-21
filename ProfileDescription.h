#pragma once
#include <iostream>
using namespace std;
class ProfileDescription{
public:
	string about;
	bool visibility;
	ProfileDescription();
	ProfileDescription(int userID, string about, bool visibility = false);
};

