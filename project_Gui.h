#pragma once
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <string>
#include <QVBoxLayout>
#include <QSplashScreen>
#include <QTimer>
#include <QHBoxLayout>
#include <qtoolbutton.h>
#include <QScrollArea>
#include <QMessageBox>
#include <QPainterPath>
#include <QRegularExpression>
#include <QPainter>
#include <iostream>
#include <QWidgetAction.h>
#include <qlist.h>
#include <QList>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QFileDialog>
#include <QScrollBar>
#include "dataBase.h"
#include <QMouseEvent>
#include <QTextEdit>
#include <set>
#include <QCheckBox>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <random>
using namespace std;


class project_Gui{
public:
	static QLabel* currentImageLabel;
	static QLabel* currentStoryLabel;

	static void splash_Screen(QWidget* window);
	static void login_Screen(QWidget* window);
	static void register_Screen(QWidget* window);
	static void chat_Screen(QWidget* window);
	static void story_Screen(QWidget* window);
	static void setting_Screen(QWidget* window);
	static void group_Screen(QWidget* window);

	static void createGroupChat(const vector<int>& selectedUserIDs);
	static QString wrapMessage(const QString& message, int wrapLength = 40);
	static int customized_chat(const QString& message, QWidget* parent, int y);
	static int customized_group(const QString& message, QWidget* parent, int y);
	static QPushButton* customized_Contact(QString name, QWidget* parent, int y, const QString& avatarPath);
	static QPushButton* customized_setting(const QString& name, QWidget* parent, int y);
	static QPushButton* customizedPop_Contact(int number, QString name, QWidget* parent, int y);
	static vector<Message> sortMessagesBySentTime(const vector<Message>& messages);////SAMA////
	static void deleteMessage(int messageId, QWidget* alignmentContainer, int chatRoomID);////SAMA////
	static QPushButton* customized_Story(QString name, QWidget* parent, const QString& avatarPath); 
	static void removeExpiredStories();
};


class ShadowEventFilter : public QObject {
public:
	ShadowEventFilter(QGraphicsDropShadowEffect* shadow, QObject* parent = nullptr)
		: QObject(parent), shadow(shadow) {
	}

protected:
	bool eventFilter(QObject* obj, QEvent* event) override {
		if (event->type() == QEvent::FocusIn) {
			shadow->setEnabled(true);
		}
		else if (event->type() == QEvent::FocusOut) {
			shadow->setEnabled(false);
		}
		return QObject::eventFilter(obj, event);
	}

private:
	QGraphicsDropShadowEffect* shadow;
};
