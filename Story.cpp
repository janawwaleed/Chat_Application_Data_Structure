#include "Story.h"


Story::Story(): userID(0),content(""),publishedTime("") {}

Story::Story(int userID, string publishedTime , string content, string photopath)
	: userID(userID), publishedTime(publishedTime), content(content), photoPath(photoPath) {
}

