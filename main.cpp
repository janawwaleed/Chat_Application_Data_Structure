
#include <QtWidgets/QApplication>
#include <QFontDatabase>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "project_Gui.h"
#include "dataBase.h"



int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    loadFromJson();
    project_Gui::removeExpiredStories();
    currentUserID = 0;
    for (auto& [id, user] : users) {
        if (user->selected){
            currentUserID = id;
            break;
        }
    }

    QWidget* window = new QWidget();
    window->setWindowTitle("What's Wrong");
    window->setGeometry(0, 0, 1280, 720);
    window->setFixedSize(1280, 720);
    window->setWindowFlags(window->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    window->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    window->setWindowIcon(QIcon("icons/logo.png"));

    //starting page
    project_Gui::splash_Screen(window);

    window->show();
    saveUsersToJson();
    return app.exec();
}
