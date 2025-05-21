#include "project_Gui.h"

QLabel* project_Gui::currentImageLabel = nullptr;
QLabel* project_Gui::currentStoryLabel = nullptr;

int selectedChatRoom = 0;
int selectedNumber = 0;
QString selectedAvatar = "";

class LambdaEventFilter : public QObject {
public:
	 function<bool(QObject*, QEvent*)> callback;

	LambdaEventFilter(function<bool(QObject*, QEvent*)> cb, QObject* parent = nullptr)
		: QObject(parent), callback(move(cb)) {}

protected:
	bool eventFilter(QObject* watched, QEvent* event) override {
		return callback(watched, event);
	}
};

void project_Gui::splash_Screen(QWidget* window) {
	QWidget* mainContainer = new QWidget(window);
	mainContainer->setGeometry(0, 0, 1280, 720);
	mainContainer->show();

	QWidget* mainBg = new QWidget(mainContainer);
	mainBg->setGeometry(0, 0, 1280, 720);
	if(currentUserID != 0 && users[currentUserID]->theme == 1) mainBg->setStyleSheet("background-color: #31473a;");
	else mainBg->setStyleSheet("background-color: #222023;");
	QLabel* imageLabel = new QLabel(mainContainer);
	QPixmap pixmap("icons/Qbg.png");
	imageLabel->setPixmap(pixmap);
	imageLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

	QLabel* bgImage = new QLabel(mainContainer);
	bgImage->setPixmap(QPixmap("icons/logo2.png"));
	bgImage->setScaledContents(mainContainer);
	bgImage->move(565, 200);

	QWidget* splashScreen = new QWidget(mainContainer);
	splashScreen->setGeometry(0, 0, 1280, 720);

	QLabel* title = new QLabel("What's Wrong?", splashScreen);
	QFont titleFont("Poppins", 36, QFont::Bold);
	title->setFont(titleFont);
	title->setStyleSheet("color: white;  background: transparent;");
	title->adjustSize();
	title->move((1280 - title->width()) / 2, 360);

	// Welcome Message
	QLabel* welcome = new QLabel("Welcome to our Application", splashScreen);
	QFont welcomeFont("Poppins", 18);
	welcome->setFont(welcomeFont);
	welcome->setStyleSheet("color: white; background: transparent;");
	welcome->adjustSize();
	welcome->move((1280 - welcome->width()) / 2 - 6, 420);

	splashScreen->show();


	QTimer::singleShot(2200, splashScreen, [=]() {
		bgImage->hide();
		splashScreen->hide();
		mainContainer->hide();
		mainContainer->deleteLater();
		if (currentUserID == 0) {
			login_Screen(window);
		}
		else {
			chat_Screen(window);
		}
	});

}

void project_Gui::login_Screen(QWidget* window) {
	QWidget* mainContainer = new QWidget(window);
	mainContainer->setGeometry(0, 0, 1280, 720);

	QWidget* mainBg = new QWidget(mainContainer);
	mainBg->setGeometry(0, 0, 1280, 720);
	mainBg->setStyleSheet("background-color: #222023;");

	QLabel* Label1 = new QLabel("What's", mainContainer);
	QLabel* Label2 = new QLabel("Wrong?", mainContainer);
	QFont titleFont("Poppins", 55, QFont::Bold);
	Label1->setFont(titleFont);
	Label1->setStyleSheet("color: white; background: transparent; letter-spacing: -1px;");
	Label1->setGeometry(120, 257, 350, 100);

	Label2->setFont(titleFont);
	Label2->setStyleSheet("color: white; background: transparent; letter-spacing: -1px;");
	Label2->setGeometry(120, 324, 350, 100);

	QWidget* container = new QWidget(mainContainer);
	container->setGeometry(750, 144, 330, 432);
	container->setStyleSheet("background-color: white; border-radius: 30px; border: 1px solid rgba(0, 0, 0, 0.35);");

	QLabel* imageLabel = new QLabel(mainContainer);
	QPixmap pixmap("icons/Qbg.png");
	imageLabel->setPixmap(pixmap);
	imageLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(container);
	shadow->setBlurRadius(40);
	shadow->setOffset(0, 0);
	shadow->setColor(QColor(232, 229, 4, 20));
	QGraphicsDropShadowEffect* shadow2 = new QGraphicsDropShadowEffect(container);
	shadow2->setBlurRadius(40);
	shadow2->setOffset(0, 0);
	shadow2->setColor(QColor(232, 229, 4, 20));
	QGraphicsDropShadowEffect* shadow3 = new QGraphicsDropShadowEffect(container);
	shadow3->setBlurRadius(40);
	shadow3->setOffset(0, 0);
	shadow3->setColor(QColor(232, 229, 4, 20));

	container->setGraphicsEffect(shadow);
	Label2->setGraphicsEffect(shadow2);
	Label1->setGraphicsEffect(shadow3);

	QLabel* Label3 = new QLabel("Welcome Back", container);
	QFont subFont("Poppins", 25, QFont::Bold);
	Label3->setGeometry(47, 20, 250, 100);
	Label3->setFont(subFont);
	Label3->setStyleSheet("color: #212e36; letter-spacing: -1.3px; background: transparent; border: none;");


	QLineEdit* numberField = new QLineEdit(container);
	QRegularExpression regex("^\\d{10}$");
	QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex, numberField);
	numberField->setValidator(validator);
	numberField->setPlaceholderText("Phone Number");
	numberField->setGeometry(30, 143, 270, 45);
	numberField->setStyleSheet(R"(
	QLineEdit {
		padding-left: 68px;
		border: 1px solid #ccc;
		border-radius: 7px;
		font-size: 14px;
		color: black;
		background: white;
	}
	QLineEdit:focus {
		border: 1px solid rgba(0, 0, 0, 0.6);
	}
	)");

	//number
	QLabel* numLabel = new QLabel(container);
	numLabel->setText("+20");
	numLabel->setStyleSheet("font-size: 14px; color: black; border: 0;");
	numLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
	numLabel->setGeometry(numberField->x() + 40, numberField->y() + 12, 25, 20);

	QLineEdit* passwordField = new QLineEdit(container);
	passwordField->setPlaceholderText("Password");
	passwordField->setGeometry(30, 203, 270, 45);
	passwordField->setEchoMode(QLineEdit::Password);
	passwordField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 42px;
        border: 1px solid #ccc;
        border-radius: 7px;
        font-size: 14px;
        color: black;
    }
	QLineEdit:focus {
		border: 1px solid rgba(0, 0, 0, 0.6);
	}
    )");

	QLineEdit* passwordField2 = new QLineEdit(container);
	passwordField2->setPlaceholderText("Password");
	passwordField2->setGeometry(30, 203, 270, 45);
	passwordField2->setEchoMode(QLineEdit::Password);
	passwordField2->setStyleSheet(R"(
    QLineEdit {
        padding-left: 42px;
        border: 1px solid #ccc;
        border-radius: 7px;
        font-size: 14px;
        color: black;
    }
	QLineEdit:focus {
		border: 1px solid rgba(0, 0, 0, 0.6);
	}
    )");


	//Field Shadow
	QGraphicsDropShadowEffect* fieldShadow = new QGraphicsDropShadowEffect();
	fieldShadow->setBlurRadius(8);
	fieldShadow->setOffset(0, 0);
	fieldShadow->setColor(QColor(0, 0, 0, 80));
	fieldShadow->setEnabled(false);

	QGraphicsDropShadowEffect* fieldShadow2 = new QGraphicsDropShadowEffect();
	fieldShadow2->setBlurRadius(8);
	fieldShadow2->setOffset(0, 0);
	fieldShadow2->setColor(QColor(0, 0, 0, 80));
	fieldShadow2->setEnabled(false);

	QGraphicsDropShadowEffect* fieldShadow3 = new QGraphicsDropShadowEffect();
	fieldShadow3->setBlurRadius(8);
	fieldShadow3->setOffset(0, 0);
	fieldShadow3->setColor(QColor(0, 0, 0, 80));
	fieldShadow3->setEnabled(false);

	numberField->setGraphicsEffect(fieldShadow);
	numberField->installEventFilter(new ShadowEventFilter(fieldShadow, numberField));

	passwordField->setGraphicsEffect(fieldShadow2);
	passwordField->installEventFilter(new ShadowEventFilter(fieldShadow2, passwordField));

	passwordField2->setGraphicsEffect(fieldShadow3);
	passwordField2->installEventFilter(new ShadowEventFilter(fieldShadow3, passwordField2));

	QPushButton* loginButton = new QPushButton("Login Now", container);
	loginButton->setGeometry(30, 270, 270, 50);
	loginButton->setCursor(Qt::PointingHandCursor);
	loginButton->setStyleSheet(
		"QPushButton {"
		"  color: white;"
		"  background-color: #222023;"
		"  border: 1px solid #ccc;"
		"  border-radius: 7px;"
		"  font-size: 18px;"
		"  font-weight: bold;"
		"}"
		"QPushButton:hover {"
		"  background-color: #333134;"
		"}"
	);


	QPushButton* register_Button = new QPushButton("Register Now", container);
	register_Button->setGeometry(30, 330, 270, 50);
	register_Button->setCursor(Qt::PointingHandCursor);
	register_Button->setStyleSheet(
		"QPushButton {"
		"  color: #222023;"
		"  background-color: white;"
		"  border: 1px solid #ccc;"
		"  border-radius: 7px;"
		"  font-size: 18px;"
		"  font-weight: bold;"
		"}"
		"QPushButton:hover {"
		"  background-color: #f0f0f0;"
		"}"
	);

	//phone icon
	QLabel* iconLabel = new QLabel(container);
	iconLabel->setPixmap(QPixmap("icons/telephone.png").scaled(17, 17, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	iconLabel->setGeometry(numberField->x() + 16, numberField->y() + 12, 20, 20);
	iconLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
	iconLabel->setStyleSheet("border: none; outline: none;");
	//lock icon
	QLabel* iconLabel2 = new QLabel(container);
	iconLabel2->setPixmap(QPixmap("icons/lock.png").scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	iconLabel2->setGeometry(passwordField->x() + 16, passwordField->y() + 12, 20, 20);
	iconLabel2->setAttribute(Qt::WA_TransparentForMouseEvents);
	iconLabel2->setStyleSheet("border: none; outline: none;");



	// Validation labels
	QLabel* numberErrorLabel1 = new QLabel("Number required", container);
	numberErrorLabel1->setGeometry(33, 182, 350, 20);
	numberErrorLabel1->setStyleSheet("color: red; font-size: 11px; background: transparent; border:none;");
	numberErrorLabel1->hide();

	QLabel* passwordErrorLabel1 = new QLabel("Password required", container);
	passwordErrorLabel1->setGeometry(33, 243, 350, 20);
	passwordErrorLabel1->setStyleSheet("color: red; font-size: 11px; background: transparent; border:none;");
	passwordErrorLabel1->hide();

	QLabel* numberErrorLabel = new QLabel("Invalid phone number", container);
	numberErrorLabel->setGeometry(33, 182, 350, 20);
	numberErrorLabel->setStyleSheet("color: red; font-size: 11px; background: transparent; border:none;");
	numberErrorLabel->hide();

	QLabel* credentialsErrorLabel = new QLabel("Invalid phone number or password", container);
	credentialsErrorLabel->setGeometry(74, 247, 350, 20);
	credentialsErrorLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	credentialsErrorLabel->hide();

	QLabel* emptyErrorLabel = new QLabel("Please fill in all fields", container);
	emptyErrorLabel->setGeometry(111, 244, 350, 30);
	emptyErrorLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	emptyErrorLabel->hide();

	Label1->show();
	Label2->show();
	mainContainer->show();
	container->show();

	QObject::connect(register_Button, &QPushButton::clicked, [=]() {
		container->hide();
		project_Gui::register_Screen(mainContainer);
		});


	QObject::connect(loginButton, &QPushButton::clicked, [=]() {
		// Hide all error labels initially
		numberErrorLabel->hide();
		emptyErrorLabel->hide();
		credentialsErrorLabel->hide();
		passwordErrorLabel1->hide();
		numberErrorLabel1->hide();

		QString phoneNumber = numberField->text().trimmed();
		QString password = passwordField2->text();
		bool hasError = false;

		if (phoneNumber.isEmpty() && password.isEmpty()) {
			emptyErrorLabel->show();
			hasError = true;
		}
		else if (phoneNumber.isEmpty()) {
			numberErrorLabel1->show();
			hasError = true;
		}
		else if (phoneNumber.length() != 10 || phoneNumber.at(0) == '0') {
			numberErrorLabel->show();
			hasError = true;
		}
		else if (password.isEmpty()) {
			passwordErrorLabel1->show();
			hasError = true;
		}

		if (!hasError) {
			int number = phoneNumber.toInt();
			string passwordStr = password.toStdString();
			bool found = false;

			for (const auto& [id, user] : users) {
				if (user->getNumber() == number && user->getPassword() == passwordStr) {
					found = true;
					currentUserID = id;
					users[currentUserID]->selected = true;
					updateUsersToJson();
					break;
				}
			}

			if (found) {
				mainContainer->hide();
				project_Gui::chat_Screen(window);
			}
			else {
				credentialsErrorLabel->show();
			}
		}
		});
}

void project_Gui::register_Screen(QWidget* window) {

	QWidget* container = new QWidget(window);
	container->setGeometry(750, 85, 330, 550);

	container->setStyleSheet("background-color: white; border-radius: 30px; border: 1px solid gray;");

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(container);
	shadow->setBlurRadius(40);
	shadow->setOffset(0, 6);
	shadow->setColor(QColor(232, 229, 4, 20));

	container->setGraphicsEffect(shadow);

	QLabel* Label1 = new QLabel("Welcome", container);
	QFont Font("Poppins", 25, QFont::Bold);
	Label1->setFont(Font);
	Label1->setStyleSheet("color: #212e36; letter-spacing: -1.3px; background: transparent; border: none;");

	Label1->adjustSize();
	Label1->move(89, 40);

	QLabel* Label2 = new QLabel("Create your account below", container);
	QFont subFont("Poppins", 15, QFont::Black);
	Label2->setFont(subFont);
	Label2->setStyleSheet("color: #2d343a; background: transparent; border: none;font-weight: 400;");
	Label2->adjustSize();
	Label2->move(31, 80);


	//full name
	QLineEdit* FullnameField = new QLineEdit(container);
	FullnameField->setPlaceholderText("Full Name");
	FullnameField->setGeometry(30, 150, 270, 45);
	FullnameField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 42px;
        border: 1px solid #ccc;
        border-radius: 7px;
        font-size: 14px;
        color: black;
    }
	QLineEdit:focus {
		border: 1px solid rgba(0, 0, 0, 0.6);
	}
    )");



	QLineEdit* numberField = new QLineEdit(container);
	QRegularExpression regex("^\\d{10}$");
	QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex, numberField);
	numberField->setValidator(validator);
	numberField->setPlaceholderText("Phone Number");
	numberField->setGeometry(30, 210, 270, 45);
	numberField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 68px;
        border: 1px solid #ccc;
        border-radius: 7px;
        font-size: 14px;
        color: black;
    }
	QLineEdit:focus {
		border: 1px solid rgba(0, 0, 0, 0.6);
	}
    )");

	//number
	QLabel* numLabel = new QLabel(container);
	numLabel->setText("+20");
	numLabel->setStyleSheet("font-size: 14px; color: black; border: 0;");
	numLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
	numLabel->setGeometry(numberField->x() + 40, numberField->y() + 12, 25, 20);



	//password
	QLineEdit* passwordField = new QLineEdit(container);
	passwordField->setPlaceholderText("Password");
	passwordField->setGeometry(30, 270, 270, 45);
	passwordField->setEchoMode(QLineEdit::Password);
	passwordField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 42px;
        border: 1px solid #ccc;
        border-radius: 7px;
        font-size: 14px;
        color: black;
    }
	QLineEdit:focus {
		border: 1px solid rgba(0, 0, 0, 0.6);
	}
    )");



	//confirm password
	QLineEdit* conPasswordField = new QLineEdit(container);
	conPasswordField->setPlaceholderText("Confirm Password");
	conPasswordField->setGeometry(30, 330, 270, 45);
	conPasswordField->setEchoMode(QLineEdit::Password);
	conPasswordField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 42px;
        border: 1px solid #ccc;
        border-radius: 7px;
        font-size: 14px;
        color: black;
    }   
	QLineEdit:focus {
		border: 1px solid rgba(0, 0, 0, 0.6);
	}
    )");

	//Field Shadow
	QGraphicsDropShadowEffect* fieldShadow = new QGraphicsDropShadowEffect();
	fieldShadow->setBlurRadius(8);
	fieldShadow->setOffset(0, 0);
	fieldShadow->setColor(QColor(0, 0, 0, 80));
	fieldShadow->setEnabled(false);

	QGraphicsDropShadowEffect* fieldShadow2 = new QGraphicsDropShadowEffect();
	fieldShadow2->setBlurRadius(8);
	fieldShadow2->setOffset(0, 0);
	fieldShadow2->setColor(QColor(0, 0, 0, 80));
	fieldShadow2->setEnabled(false);

	QGraphicsDropShadowEffect* fieldShadow3 = new QGraphicsDropShadowEffect();
	fieldShadow3->setBlurRadius(8);
	fieldShadow3->setOffset(0, 0);
	fieldShadow3->setColor(QColor(0, 0, 0, 80));
	fieldShadow3->setEnabled(false);

	QGraphicsDropShadowEffect* fieldShadow4 = new QGraphicsDropShadowEffect();
	fieldShadow4->setBlurRadius(8);
	fieldShadow4->setOffset(0, 0);
	fieldShadow4->setColor(QColor(0, 0, 0, 80));
	fieldShadow4->setEnabled(false);

	numberField->setGraphicsEffect(fieldShadow);
	numberField->installEventFilter(new ShadowEventFilter(fieldShadow, numberField));

	passwordField->setGraphicsEffect(fieldShadow2);
	passwordField->installEventFilter(new ShadowEventFilter(fieldShadow2, passwordField));

	conPasswordField->setGraphicsEffect(fieldShadow3);
	conPasswordField->installEventFilter(new ShadowEventFilter(fieldShadow3, conPasswordField));

	FullnameField->setGraphicsEffect(fieldShadow4);
	FullnameField->installEventFilter(new ShadowEventFilter(fieldShadow4, FullnameField));

	//name icon
	QLabel* iconLabel = new QLabel(container);
	iconLabel->setPixmap(QPixmap("icons/person.png").scaled(17, 17, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	iconLabel->setGeometry(FullnameField->x() + 16, FullnameField->y() + 12, 20, 20);
	iconLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
	iconLabel->setStyleSheet("border: none; outline: none;");
	//phone icon
	QLabel* iconLabel2 = new QLabel(container);
	iconLabel2->setPixmap(QPixmap("icons/telephone.png").scaled(17, 17, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	iconLabel2->setGeometry(numberField->x() + 16, numberField->y() + 12, 20, 20);
	iconLabel2->setAttribute(Qt::WA_TransparentForMouseEvents);
	iconLabel2->setStyleSheet("border: none; outline: none;");
	//lock icon
	QLabel* iconLabel3 = new QLabel(container);
	iconLabel3->setPixmap(QPixmap("icons/lock.png").scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	iconLabel3->setGeometry(passwordField->x() + 16, passwordField->y() + 12, 20, 20);
	iconLabel3->setAttribute(Qt::WA_TransparentForMouseEvents);
	iconLabel3->setStyleSheet("border: none; outline: none;");
	//lock2 icon
	QLabel* iconLabel4 = new QLabel(container);
	iconLabel4->setPixmap(QPixmap("icons/lock2.png").scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	iconLabel4->setGeometry(conPasswordField->x() + 16, conPasswordField->y() + 12, 20, 20);
	iconLabel4->setAttribute(Qt::WA_TransparentForMouseEvents);
	iconLabel4->setStyleSheet("border: none; outline: none;");

	//validation
	QLabel* numberErrorLabel = new QLabel("Invalid phone number", container);
	numberErrorLabel->setGeometry(33, 250, 350, 20);
	numberErrorLabel->setStyleSheet("color: red; font-size: 11px; background: transparent; border:none;");
	numberErrorLabel->hide();

	// under password field
	QLabel* passErrorLabel = new QLabel("Password must be at least 6 characters", container);
	passErrorLabel->setGeometry(33, 311, 350, 20);
	passErrorLabel->setStyleSheet("color: red; font-size: 11px; background: transparent; border:none;");
	passErrorLabel->hide();

	// under confirm password field
	QLabel* matchErrorLabel = new QLabel("Passwords do not match", container);
	matchErrorLabel->setGeometry(33, 371, 350, 20);
	matchErrorLabel->setStyleSheet("color: red; font-size: 11px; background: transparent; border:none;");
	matchErrorLabel->hide();

	// general empty field error (optional)
	QLabel* emptyErrorLabel = new QLabel("Please fill in all fields", container);
	emptyErrorLabel->setGeometry(95.5, 380, 350, 30);
	emptyErrorLabel->setStyleSheet("color: red; font-size: 15px; background: transparent; border:none;");
	emptyErrorLabel->hide();

	QLabel* ErrorLabel = new QLabel("User already exists", container);
	ErrorLabel->setGeometry(101, 380, 350, 30);
	ErrorLabel->setStyleSheet("color: red; font-size: 15px; background: transparent; border:none;");
	ErrorLabel->hide();




	QPushButton* register_Button = new QPushButton("Register", container);
	register_Button->setGeometry(30, 416, 270, 45);
	register_Button->setCursor(Qt::PointingHandCursor);
	register_Button->setStyleSheet(
		"QPushButton {"
		"  color: white;"
		"  background-color: #222023;"
		"  border: 1px solid #ccc;"
		"  border-radius: 6px;"
		"  font-size: 18px;"
		"  font-weight: bold;"
		"}"
		"QPushButton:hover {"
		"  background-color: #333134;"
		"}"
	);


	QPushButton* login_Button = new QPushButton("Already have an account? Login", container);
	login_Button->setGeometry(-10, 460, 350, 50);
	login_Button->setCursor(Qt::PointingHandCursor);
	login_Button->setStyleSheet(R"(
	QPushButton {
		background: none;
		border: none;
		color: #222023;
		font-size: 18px;
		text-decoration: underline;
	}
	QPushButton:hover {
		color: #333134;
	}
    )");
	login_Button->setCursor(Qt::PointingHandCursor);
	login_Button->setFlat(true);


	container->show();

	QObject::connect(login_Button, &QPushButton::clicked, [=]() {
		container->hide();
		project_Gui::login_Screen(window);
		});

	//validation
	QObject::connect(register_Button, &QPushButton::clicked, [=]() {
		// Hide all error labels initially
		numberErrorLabel->hide();
		passErrorLabel->hide();
		matchErrorLabel->hide();
		emptyErrorLabel->hide();
		ErrorLabel->hide();

		QString fullName = FullnameField->text().trimmed();
		QString phoneNumber = numberField->text().trimmed();
		QString password = passwordField->text();
		QString confirmPassword = conPasswordField->text();

		size_t firstSpace = fullName.toStdString().find(' ');
		string firstName = fullName.toStdString().substr(0, firstSpace);
		size_t lastSpace = fullName.toStdString().rfind(' ');
		string lastName = fullName.toStdString().substr(lastSpace + 1);

		bool hasError = false;


		if (fullName.isEmpty() || phoneNumber.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
			emptyErrorLabel->show();
			hasError = true;
		}
		else {
			if (phoneNumber.length() != 10 || phoneNumber.at(0) == '0') {
				numberErrorLabel->show();
				hasError = true;
			}

			if (password.length() < 6) {
				passErrorLabel->show();
				hasError = true;
			}

			if (password != confirmPassword) {
				matchErrorLabel->show();
				hasError = true;
			}

			if (hasError == false)
				for (auto& [id, user] : users) {
					if (user->getNumber() == stoi(phoneNumber.toStdString())) {
						ErrorLabel->show();
						hasError = true;
						break;
					}
				}
		}



		if (!hasError) {
			User* u = new User(firstName, lastName, password.toStdString(), stoi(phoneNumber.toStdString()), "lastSeen", "");
			u->setID(maxID() + 1);
			u->selected = true;
			currentUserID = u->getID();
			users[currentUserID] = u;

			updateUsersToJson();
			container->hide();
			project_Gui::chat_Screen(window);
		}
		});





}

void project_Gui::chat_Screen(QWidget* window) {

	QWidget* container = new QWidget(window);
	container->setGeometry(0, 0, 1280, 720);
	QFont ButtonFont6("Poppins", 11);


	//chat wallpaperr
	QLabel* chatWallpaper = new QLabel(container);
	chatWallpaper->setGeometry(442, 0, 838, 720);
	chatWallpaper->setPixmap(QPixmap("icons/chatWallpaper.png"));
	chatWallpaper->setScaledContents(true);
	chatWallpaper->setStyleSheet("border: none;");

	//contacts room
	QWidget* contactsArea = new QWidget(container);
	contactsArea->setGeometry(61, 66, 380, 720);
	contactsArea->setStyleSheet("border: none; background-color: #eef4f2;");

	//chats room
	QWidget* chatArea = new QWidget(container);
	chatArea->setGeometry(442, 0, 838, 720);
	chatArea->setStyleSheet(R"(
    QWidget {
        background-color: transparent;
        border: none;
    }
	)");



	//scrolling area
	  //contact scroll
	QScrollArea* contactScrollArea = new QScrollArea(contactsArea);
	contactScrollArea->setGeometry(0, 87, 380, 567);
	contactScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	contactScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	contactScrollArea->setWidgetResizable(true);
	contactScrollArea->setStyleSheet(R"(
    QScrollBar:vertical, QScrollBar:horizontal {
        width: 0px;
        height: 0px;
        background: transparent;

        }
    )");



	//chat scroll
	QScrollArea* chatScrollArea = new QScrollArea(chatArea);
	chatScrollArea->setGeometry(0, 87, 838, 567);
	chatScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	chatScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	chatScrollArea->setWidgetResizable(true);
	chatScrollArea->setStyleSheet(R"(
    QScrollBar:vertical, QScrollBar:horizontal {
        width: 0px;
        height: 0px;
        background: transparent;

        }
    )");


	QWidget* contactListWidget = new QWidget();
	contactListWidget->setStyleSheet("background-color: transparent; background-color: #eef4f2;");
	contactScrollArea->setWidget(contactListWidget);

	QWidget* chatMessagesWidget = new QWidget();
	chatMessagesWidget->setStyleSheet("background-color: transparent;");
	chatScrollArea->setWidget(chatMessagesWidget);

	QVector<QPair<QPushButton*, QString>> contactButtons;


	//search bar
	QLineEdit* searchField = new QLineEdit(contactsArea);
	searchField->setPlaceholderText("Search");
	searchField->setGeometry(14, 3, 348, 30);
	searchField->setStyleSheet(R"(
    QLineEdit {
        background-color: #222023;
        padding-left: 20px;
        border: none;
        border-radius: 7px;
        font-size: 15px;
        color: #eef4f2;
    }
    )");

	QWidget* SearchDevider1 = new QWidget(contactsArea);
	SearchDevider1->setGeometry(17, 82, 348, 1);
	SearchDevider1->setStyleSheet("background-color: #b4b7b7; border: none;");
	QWidget* SearchDevider2 = new QWidget(contactsArea);
	SearchDevider2->setGeometry(17, 84, 348, 1);
	SearchDevider2->setStyleSheet("background-color: #b4b7b7; border: none;");


	QFont ButtonFont("Poppins", 10);

	QToolButton* Button3 = new QToolButton(contactsArea);
	Button3->setText("Add Contact");
	Button3->setGeometry(14, 40, 115, 30);
	Button3->setCursor(Qt::PointingHandCursor);
	Button3->setFont(ButtonFont);

	QToolButton* Button4 = new QToolButton(contactsArea);
	Button4->setText("Add Chat");
	Button4->setGeometry(134, 40, 96, 30);
	Button4->setCursor(Qt::PointingHandCursor);
	Button4->setFont(ButtonFont);



	QToolButton* searchIcon = new QToolButton(searchField);
	searchIcon->setIcon(QIcon("icons/search.png"));
	searchIcon->setGeometry(0, -5, 40, 40);
	searchIcon->setIconSize(QSize(19, 19));
	searchIcon->setStyleSheet("border: none; background-color: transparent; padding-left: 10px;"); // optional
	searchField->addAction(new QWidgetAction(searchIcon), QLineEdit::LeadingPosition);


	//////////////////////////////////////
	QWidget* bar = new QWidget(chatArea);
	bar->setGeometry(0, 0, 860, 66);
	QWidget* bar2 = new QWidget(chatArea);
	bar2->setGeometry(0, 654, 860, 66);
	if (users[currentUserID]->theme == 1) {
		bar->setStyleSheet("border: none; background-color: #31473a;");
		bar2->setStyleSheet("border: none; background-color: #31473a;");
	}
	else {
		bar->setStyleSheet("border: none; background-color: #222023;");
		bar2->setStyleSheet("border: none; background-color: #222023;");
	}

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
	shadow->setBlurRadius(20);
	shadow->setOffset(0, 1);
	shadow->setColor(QColor(0, 0, 0, 80));

	bar->setGraphicsEffect(shadow);

	QGraphicsDropShadowEffect* shadow2 = new QGraphicsDropShadowEffect();
	shadow2->setBlurRadius(20);
	shadow2->setOffset(0, -1);
	shadow2->setColor(QColor(0, 0, 0, 80));

	bar2->setGraphicsEffect(shadow2);


	// Chat name as clickable button
	QPushButton* chatNameButton = new QPushButton(bar);
	chatNameButton->setGeometry(70, 12, 400, 40);
	QFont nameFont("Poppins", 16, QFont::Bold);
	chatNameButton->setFont(nameFont);
	chatNameButton->setStyleSheet(R"(
        QPushButton {
            background: transparent;
            border: none;
            color: #e4d9d7;
            text-align: left;
            padding: 0;
        }
    )");
	chatNameButton->setCursor(Qt::PointingHandCursor);
	chatNameButton->setFlat(true); // Remove default button decoration

	// Add round avatar as clickable button
	QPushButton* avatarButton = new QPushButton(bar);
	avatarButton->setGeometry(20, 13, 40, 40);
	avatarButton->setStyleSheet(R"(
        QPushButton {
            border: 2px solid #222023;
            border-radius: 20px;
            background: transparent;
            padding: 0;
        }
        QPushButton:hover {
            border-color: #e4d9d7;
        }
    )");
	avatarButton->setCursor(Qt::PointingHandCursor);
	avatarButton->setFlat(true); // Remove default button decoration

	QLabel* avatarLabel = new QLabel(avatarButton);
	avatarLabel->setGeometry(0, 0, 40, 40);
	avatarLabel->setScaledContents(true);
	avatarLabel->setStyleSheet("border-radius: 20px;");





	QLabel* HidechatArea = new QLabel(container);
	HidechatArea->setGeometry(442, 0, 838, 720);
	if (users[currentUserID]->theme == 1) {
		HidechatArea->setPixmap(QPixmap("icons/chatImg2.png"));
	}
	else {
		HidechatArea->setPixmap(QPixmap("icons/chatImg.png"));
	}
	HidechatArea->setScaledContents(true);
	HidechatArea->setStyleSheet("border: none; background-color: #222023;");

	QWidget* topBarDevider = new QWidget(container);
	topBarDevider->setGeometry(441, 0, 1, 720);
	topBarDevider->setStyleSheet("background-color: #f9eded; border: none;");

	//right click
	QWidget* rightClickContainer = new QWidget(container);
	rightClickContainer->setStyleSheet(R"(
	QWidget{
		border-radius: 3px;
		border: none;
		background-color: #eef4f2;
	}
	)");
	rightClickContainer->hide();

	QWidget* rightClickDiv = new QWidget(rightClickContainer);
	rightClickDiv->setStyleSheet("background-color: transparent;");

	QWidget* rightClickColors = new QWidget(rightClickContainer);
	rightClickColors->setStyleSheet(R"(
	QWidget{
		border-top-left-radius: 3px; border-top-right-radius: 3px; border-bottom-left-radius: 0px; border-bottom-right-radius: 0px;
		background-color: #f44400;
	}
	/*QWidget::hover{
		background-color: #f86f33;
	}*/
	)");




	QToolButton* deleteBtn = new QToolButton(rightClickContainer);
	deleteBtn->setText(" Delete");
	deleteBtn->setStyleSheet(R"(
        QToolButton{
			background-color: transparent;
			border: none;
			color: #e4d9d7;
		}
    )");
	deleteBtn->setFont(ButtonFont6);


	QToolButton* closeBtn = new QToolButton(rightClickContainer);
	closeBtn->setText("Close");
	closeBtn->setStyleSheet(R"(
        QToolButton{
			background-color: transparent;
			border: none;
			color: #f44400;
		}
    )");
	closeBtn->setFont(ButtonFont6);

	QIcon icon("icons/trash.png");
	deleteBtn->setIcon(icon);
	deleteBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	closeBtn->setGeometry(0, 30, 85, 30);
	rightClickDiv->setGeometry(0, 29, 85, 1);
	rightClickColors->setGeometry(0, 0, 85, 30);
	deleteBtn->setGeometry((85 - 72) / 2, 0, 71, 30);

	//n'lt de hna 3shan n3ml clear lma nro7 chat tany --the one and only -Abdelaziz
	QLineEdit* messageField = new QLineEdit(chatArea);
	messageField->setPlaceholderText("Type a message");
	messageField->setGeometry(55, 669, 745, 38);
	messageField->setStyleSheet(R"(
        QLineEdit {
            padding-left: 18px;
            border: none;
            border-radius: 7px;
            font-size: 14px;
            background: #2d2c2d;
            color: #ffffff;
        }
    )");


	int contactHeight = 81;
	int index = 0;

	struct ContactInfo {
		QPushButton* button;
		QString name;
		int number; // Store phone number for user lookup
		int originalIndex;
		QString avatar;
	};
	QVector<ContactInfo> contactInfos;


	for (auto& [id, user] : users) {
		if (id == currentUserID) continue;

		for (auto V1 : users[currentUserID]->chatRooms) {
			for (auto V2 : user->chatRooms) {
				if ((V1.getChatRoomID() == V2.getChatRoomID()) && V1.type() == "Private" && V2.type() == "Private") {
					int sharedRoomID = V1.getChatRoomID();
					string s = users[currentUserID]->getNameFromContacts(user->getNumber());
					QString name = QString::fromStdString(s);
					int number = user->getNumber();
					int selectedID;
					if (V1.getUserIDs()[0] != currentUserID) {
						selectedID = V1.getUserIDs()[0];
					}
					else {
						selectedID = V1.getUserIDs()[1];
					}

					const QString& avatar = users[selectedID]->avatar != "" ? QString::fromStdString(users[selectedID]->avatar) : "icons/default.jpg";
					QPushButton* contactBtn = customized_Contact(name, contactListWidget, index * contactHeight, avatar);

					contactBtn->setObjectName("contactBtn");
					bool isUnopened = find(user->story.viewers.begin(), user->story.viewers.end(), currentUserID) == user->story.viewers.end();
					if ((user->story.content != "" || user->story.photoPath != "") && user->profile.visibility && isUnopened) {
						QLabel* StoryAvatar = contactBtn->findChild<QLabel*>("chatAvatar");
						QString storyAvatarPath = user->avatar != "" ? QString::fromStdString(user->avatar) : "icons/default.jpg";
						if (!storyAvatarPath.isEmpty()) {
							QPixmap pixmap(storyAvatarPath);
							QPixmap scaledPixmap = pixmap.scaled(42, 42, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

							QPixmap finalPixmap(42, 42);
							finalPixmap.fill(Qt::transparent);

							QPainter painter(&finalPixmap);
							painter.setRenderHint(QPainter::Antialiasing);

							QPainterPath path;
							path.addEllipse(0, 0, 42, 42);
							painter.setClipPath(path);

							painter.drawPixmap(0, 0, scaledPixmap);

							painter.setClipping(false);

							// Draw the light gray circle border
							QPen blackPen(QColor("#eef4f2"));
							blackPen.setWidth(3);
							painter.setPen(blackPen);
							painter.setBrush(Qt::NoBrush);
							painter.drawEllipse(2, 2, 38, 38);

							// Draw the green gradient "guardian" border
							QConicalGradient gradient(21, 21, 0);
							gradient.setColorAt(0.0, QColor("#00cc66"));
							gradient.setColorAt(0.25, QColor("#00e673"));
							gradient.setColorAt(0.5, QColor("#1aff66"));
							gradient.setColorAt(0.75, QColor("#66ff99"));
							gradient.setColorAt(1.0, QColor("#00cc66"));

							QPen greenPen(QBrush(gradient), 2);
							painter.setPen(greenPen);
							painter.setBrush(Qt::NoBrush);
							painter.drawEllipse(1, 1, 40, 40);

							painter.end();
							StoryAvatar->setPixmap(finalPixmap);
						}

					}
					else if ((user->story.content != "" || user->story.photoPath != "") && user->profile.visibility && !isUnopened) {
						QLabel* StoryAvatar = contactBtn->findChild<QLabel*>("chatAvatar");
						QString storyAvatarPath = user->avatar != "" ? QString::fromStdString(user->avatar) : "icons/default.jpg";
						if (!storyAvatarPath.isEmpty()) {
							QPixmap pixmap(storyAvatarPath);
							QPixmap scaledPixmap = pixmap.scaled(42, 42, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

							QPixmap finalPixmap(42, 42);
							finalPixmap.fill(Qt::transparent);

							QPainter painter(&finalPixmap);
							painter.setRenderHint(QPainter::Antialiasing);

							QPainterPath path;
							path.addEllipse(0, 0, 42, 42);
							painter.setClipPath(path);

							painter.drawPixmap(0, 0, scaledPixmap);

							painter.setClipping(false);

							// Draw the light gray circle border
							QPen blackPen(QColor("#eef4f2"));
							blackPen.setWidth(3);
							painter.setPen(blackPen);
							painter.setBrush(Qt::NoBrush);
							painter.drawEllipse(2, 2, 38, 38);

							// Draw the green gradient "guardian" border
							QConicalGradient gradient(21, 21, 0);
							gradient.setColorAt(0.0, QColor("#A9A9A9"));

							QPen greenPen(QBrush(gradient), 2);
							painter.setPen(greenPen);
							painter.setBrush(Qt::NoBrush);
							painter.drawEllipse(1, 1, 40, 40);

							painter.end();
							StoryAvatar->setPixmap(finalPixmap);
						}
					}


					contactBtn->setFixedHeight(contactHeight);
					vector<Message> messages = V1.getMessages();
					if (!messages.empty()) {
						///////////////////////SAMA////SAMA////SAMA////SAMA////SAMA////SAMA/////////////////////////////////////////
						vector<Message> SortedMessages = sortMessagesBySentTime(messages);
						Message latestMessage = SortedMessages.back(); // Get the most recent message
						QString messageText = QString::fromStdString(latestMessage.text);
						QString Qtime24 = QString::fromStdString(latestMessage.timeSent);
						QTime Qtime = QTime::fromString(Qtime24, "HH:mm:ss");
						QString Qtime12 = Qtime.toString("hh:mm AP");

						QLabel* messageLabel = contactBtn->findChild<QLabel*>("messageLabel");
						QLabel* messageLabelTime = contactBtn->findChild<QLabel*>("messageLabelTime");
						if (messageLabel) {
							QFontMetrics metrics(messageLabel->font());
							if (metrics.horizontalAdvance(messageText) > 225) {
								messageText = metrics.elidedText(
									messageText,
									Qt::ElideRight,  // Add "..." at the end
									225
								);
							}

							messageLabel->setText(messageText);
							messageLabelTime->setText(Qtime12);
						}
					}
					else {
						// If no messages, display a placeholder
						QLabel* messageLabel = contactBtn->findChild<QLabel*>("messageLabel");
						if (messageLabel) {
							messageLabel->setText("Start chatting now!");
						}
					}


					contactButtons.append(qMakePair(contactBtn, name));
					contactInfos.append({ contactBtn, name, number, index, avatar });


					QObject::connect(contactBtn, &QPushButton::clicked, [=]() {
						QPushButton* TEMPbtn = nullptr;
						for (QPushButton* btn : contactListWidget->findChildren<QPushButton*>("contactBtn")) {
							if (btn == contactBtn && TEMPbtn != nullptr) {
								QLabel* Tempy = TEMPbtn->findChild<QLabel*>("userDev2");
								Tempy->setGeometry(43, 80, 380, 0);
							}
							else {
								QLabel* Tempy = btn->findChild<QLabel*>("userDev2");
								Tempy->setGeometry(43, 80, 380, 1);
							}
							btn->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    padding-bottom: 17px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
							)");
							TEMPbtn = btn;
						}


						contactBtn->setStyleSheet(R"(
						QPushButton {
							background-color: #dde3e1;
							text-align: left;
							border: none;
							padding-left: 70px;
							padding-bottom: 17px;
							font-size: 20px;
							color: black;
						}
						)");

						messageField->clear();
						chatNameButton->setText(name);
						QPixmap originalPixmap(avatar); // Load your avatar image
						QPixmap circularPixmap(40, 40); // Create a 40x40 target pixmap
						circularPixmap.fill(Qt::transparent); // Make the background transparent
						selectedChatRoom = sharedRoomID;

						QPainter painter(&circularPixmap);
						painter.setRenderHint(QPainter::Antialiasing);
						QPainterPath path;
						path.addEllipse(0, 0, 40, 40); // Define a circular path
						painter.setClipPath(path);
						painter.drawPixmap(0, 0, 40, 40, originalPixmap); // Draw the original pixmap clipped to the circle

						avatarLabel->setPixmap(circularPixmap);
						HidechatArea->hide();
						chatMessagesWidget->show();
						selectedNumber = number; // Use static member
						selectedAvatar = avatar;
						rightClickContainer->hide();


						for (ChatRoom& room : users[currentUserID]->chatRooms) {
							if (room.getChatRoomID() == selectedChatRoom) {
								vector<int> userIDs = room.getUserIDs();
								vector<Message> currentUserMessages = room.getMessages();
								vector<Message> updatedMessages = currentUserMessages;

								int otherUserID = -1;
								vector<Message> otherUserMessages;
								for (int userId : userIDs) {
									if (userId != currentUserID) {
										otherUserID = userId;
										for (ChatRoom& otherRoom : users[userId]->chatRooms) {
											if (otherRoom.getChatRoomID() == selectedChatRoom) {
												otherUserMessages = otherRoom.getMessages();
												break;
											}
										}
										break;
									}
								}

								for (Message& msg : updatedMessages) {
									if (msg.getUserID() != currentUserID && msg.status == "unseen") {
										msg.setStatus("seen");
									}
								}

								for (Message& msg : updatedMessages) {
									if (msg.getUserID() == currentUserID) {
										for (const Message& otherMsg : otherUserMessages) {
											if (msg.getMessageID() == otherMsg.getMessageID() &&
												otherMsg.status == "seen") {
												msg.setStatus("seen");
												break;
											}
										}
									}
								}

								room.setMessages(updatedMessages);

								// Update the other user's chat room to reflect only "seen" statuses for messages sent by them
								if (otherUserID != -1) {
									for (ChatRoom& otherRoom : users[otherUserID]->chatRooms) {
										if (otherRoom.getChatRoomID() == selectedChatRoom) {
											vector<Message> otherMsgs = otherRoom.getMessages();
											bool updated = false;

											for (Message& otherMsg : otherMsgs) {
												if (otherMsg.getUserID() == otherUserID) { // message sent by other user
													for (const Message& updatedMsg : updatedMessages) {
														if (updatedMsg.getMessageID() == otherMsg.getMessageID() &&
															updatedMsg.status == "seen") {
															otherMsg.setStatus("seen");
															updated = true;
															break;
														}
													}
												}
											}

											if (updated)
												otherRoom.setMessages(otherMsgs); // only update if changes occurred
											break;
										}
									}
								}

								break;
							}
						}

						updateUsersToJson();
						cout << "saved" << endl;

						// Clear old messages properly (keep layout, just remove its contents)
						QLayout* layout = chatMessagesWidget->layout();
						if (!layout) {
							layout = new QVBoxLayout(chatMessagesWidget);
							chatMessagesWidget->setLayout(layout);
						}
						QVBoxLayout* messagesLayout = qobject_cast<QVBoxLayout*>(layout);
						QLayoutItem* item;
						while ((item = messagesLayout->takeAt(0)) != nullptr) {
							if (item->widget()) delete item->widget();
							delete item;
						}
						messagesLayout->setAlignment(Qt::AlignTop);
						messagesLayout->setSpacing(5);
						int y = 0;
						for (ChatRoom& room : users[currentUserID]->chatRooms) {
							if (room.getChatRoomID() == sharedRoomID) {
								vector<int> userIDs = room.getUserIDs();
								int otherUserID = -1;
								vector<Message> otherUserMessages;
								for (int userId : userIDs) {
									if (userId != currentUserID) {
										otherUserID = userId;
										for (ChatRoom& otherRoom : users[otherUserID]->chatRooms) {
											if (otherRoom.getChatRoomID() == sharedRoomID) {
												otherUserMessages = otherRoom.getMessages();
												break;
											}
										}
										break;
									}
								}
								QObject::disconnect(deleteBtn, &QToolButton::clicked, nullptr, nullptr);

								// Outside the loop, after rightClickContainer is defined
								QObject::connect(deleteBtn, &QToolButton::clicked, [=]() {
									   cout << "delete clicked" << endl;
									   int messageId = rightClickContainer->property("messageId").toInt();
									QWidget* alignmentContainer = rightClickContainer->property("alignmentContainer").value<QWidget*>();
									if (rightClickContainer && alignmentContainer && messageId != 0) {
										cout << "deleting message id: " << messageId << endl;
										rightClickContainer->hide();
										deleteMessage(messageId, alignmentContainer, sharedRoomID);
									}
									else {
										cout << "error,invalid" << endl;
										if (!rightClickContainer)
											cout << "rightClickContainer is null" << endl;
										if (!alignmentContainer)
											cout << "alignmentContainer is null" << endl;
										if (messageId == 0)
											cout << "messageId is 0" << endl;
									}
									});

								vector<Message> sortedMessages = sortMessagesBySentTime(room.getMessages());
								// display sorted and aligned messages
								for (const Message& msg : sortedMessages) {
									QString msgText = QString::fromStdString(msg.text);
									cout << "Message UserID:" << msg.getUserID() << ", CurrentUserID:" << currentUserID << ", IsSent:" << (msg.getUserID() == currentUserID) << endl;

									QLabel* messageLabel = new QLabel(wrapMessage(msgText), chatMessagesWidget);
									QFont nameFont("Poppins", 14);
									messageLabel->setFont(nameFont);
									messageLabel->setWordWrap(true);
									//////////////////SAMA///////////////SAMA/////////////////////SAMA///////////////////SAMA////////////////SAMA////////////////////////
																	   //POSITION ISSUE SOLVED!//
									int chatAreaWidth = 838;
									int labelWidth = 500;
									int marginRightSent = 10;
									int marginLeftSent = chatAreaWidth - labelWidth - marginRightSent; // For sent messages (right)
									int marginLeftReceived = 10; // Desired padding from left for received messages
									int marginRightReceived = chatAreaWidth - labelWidth - marginLeftReceived;

									// Create a horizontal layout for alignment
									QWidget* alignmentContainer = new QWidget(chatMessagesWidget);
									QHBoxLayout* alignmentLayout = new QHBoxLayout(alignmentContainer);
									alignmentLayout->setContentsMargins(0, 0, 0, 0);
									alignmentLayout->setSpacing(0);

									auto rightClickFilter = new LambdaEventFilter(
										[=](QObject* watched, QEvent* event) -> bool {
											if (event->type() == QEvent::MouseButtonPress) {
												QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
												if (mouseEvent->button() == Qt::RightButton && msg.getUserID() == currentUserID) {
													QPoint globalPos = QCursor::pos();
													rightClickContainer->move(globalPos);
													if (globalPos.x() > 1194) {
														rightClickContainer->setGeometry(1194, globalPos.y() - 20, 85, 60);
													}
													else {
														rightClickContainer->setGeometry(globalPos.x(), globalPos.y() - 20, 85, 60);
													}
													////////////////////SAMA////SAMA////SAMA////SAMA////SAMA//////////////////////////
													cout << "Right-click on message ID: " << msg.getMessageID() << endl;
													rightClickContainer->setProperty("messageId", msg.getMessageID());
													rightClickContainer->setProperty("alignmentContainer", QVariant::fromValue(alignmentContainer));
													rightClickContainer->show();
													return true;
												}
											}
											return false;
										},
										messageLabel
									);
									messageLabel->installEventFilter(rightClickFilter);
									// For received messages (left)
									QString style = (msg.getUserID() == currentUserID) ?
										QString(R"(
										    color: white;
										    background-color: #222023;
										    border: 1px solid #444;
										    border-radius: 7px;
										    padding: 10px;
										    padding-bottom: 20px;
										    
										)") : QString(R"(
										    color: black;
										    background-color: #eef4f2;
										    border: 1px solid rgba(0, 0, 0, 30);
										    border-radius: 7px;
										    padding: 10px;
										    padding-bottom: 18px;
										    
										)");
									if (users[currentUserID]->theme == 1) {
										style = (msg.getUserID() == currentUserID) ?
											QString(R"(
										    color: white;
										    background-color: #31473a;
										    border: 1px solid #444;
										    border-radius: 7px;
										    padding: 10px;
										    padding-bottom: 20px;
										    
										)") : QString(R"(
										    color: black;
										    background-color: #eef4f2;
										    border: 1px solid rgba(0, 0, 0, 30);
										    border-radius: 7px;
										    padding: 10px;
										    padding-bottom: 18px;
										    
										)");
									}
									if (messageLabel->text().isEmpty()) {
										style += R"(
										    min-height: 30px;
										)";
									}
									messageLabel->setStyleSheet(style);
									messageLabel->adjustSize();
									if (messageLabel->width() < 89) {
										messageLabel->setMinimumWidth(89);
									}
									messageLabel->setMinimumHeight(messageLabel->height() + 10);
									// Create a container for the message and timestamp
									QWidget* messageContainer = new QWidget(chatMessagesWidget);
									messageContainer->setProperty("messageId", msg.getMessageID()); // Store message ID
									messageContainer->raise();

									QVBoxLayout* containerLayout = new QVBoxLayout(messageContainer);
									containerLayout->setContentsMargins(0, 0, 0, 0);
									containerLayout->setSpacing(2); // Small spacing between message and timestamp

									// Add the message label to the container
									containerLayout->addWidget(messageLabel);

									// Create a horizontal layout for timestamp and "seen" label
									QWidget* bottomRow = new QWidget(messageContainer);
									QHBoxLayout* bottomLayout = new QHBoxLayout(bottomRow);
									bottomLayout->setContentsMargins(0, 0, 0, 0);
									bottomLayout->setSpacing(5); // Small spacing between timestamp and "seen"

									// Add timestamp label
									QString timeStr = QString::fromStdString(msg.timeSent).left(5); // Get HH:mm
									QTime time = QTime::fromString(timeStr, "HH:mm"); // Convert to QTime
									QString formattedTime = time.toString("h:mm AP"); // Convert to 12-hour format with AM/PM

									QLabel* timestampLabel = new QLabel(formattedTime, messageLabel);
									QFont timestampFont("Poppins", 8);
									timestampLabel->setFont(timestampFont);
									timestampLabel->setStyleSheet(R"(
										color: rgba(135, 135, 135, 127);
										background: transparent;
										padding: 0px;
										qproperty-alignment: AlignLeft;
										border: none;
									)");
									timestampLabel->adjustSize();
									if (msg.getUserID() == currentUserID) {
										timestampLabel->move(messageLabel->width() - timestampLabel->width() - 28, messageLabel->height() - timestampLabel->height() - 4);
									}
									else {
										timestampLabel->move(messageLabel->width() - timestampLabel->width() - 7, messageLabel->height() - timestampLabel->height() - 4);
									}									//bottomLayout->addWidget(timestampLabel);


									// Add "seen" label for sent messages
									if (msg.getUserID() == currentUserID) {
										QString iconPath = (msg.status == "seen") ? "icons/Doublecheck2.png" : "icons/Doublecheck.png";
										QLabel* seenLabel = new QLabel(messageLabel);
										QPixmap iconPixmap(iconPath);
										seenLabel->setPixmap(iconPixmap.scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
										seenLabel->setStyleSheet("background: transparent; border: none;");
										seenLabel->adjustSize();
										seenLabel->move(messageLabel->width() - seenLabel->width() + 3, messageLabel->height() - timestampLabel->height() - 13);
										//bottomLayout->addWidget(seenLabel, 0, Qt::AlignRight);

									}

									// Add the bottom row to the container layout
									containerLayout->addWidget(bottomRow);

									if (msg.getUserID() == currentUserID) {
										alignmentLayout->addStretch();
										alignmentLayout->addWidget(messageContainer);
									}
									else {
										alignmentLayout->addWidget(messageContainer);
										alignmentLayout->addStretch();
									}

									messagesLayout->addWidget(alignmentContainer);
									y += messageContainer->height() + 5;

									QObject::connect(closeBtn, &QPushButton::clicked, [=]() {
										rightClickContainer->hide();
										});
								}
								break;
							}
						}

						// 1n
						// After adding all messages to chatMessagesWidget
						chatMessagesWidget->adjustSize();
						chatMessagesWidget->setMinimumHeight(chatMessagesWidget->sizeHint().height());

						// Only scroll to bottom if content is taller than viewport
						QTimer::singleShot(0, [=]() {
							if (chatMessagesWidget->height() > chatScrollArea->viewport()->height()) {
								chatScrollArea->verticalScrollBar()->setValue(
									chatScrollArea->verticalScrollBar()->maximum()
								);
							}
							});
						});
					contactBtn->show();
					index++;
				}

			}

		}

	}
	QVBoxLayout* contactLayout = new QVBoxLayout(contactListWidget);
	contactLayout->setContentsMargins(0, 0, 0, 0);
	contactLayout->setSpacing(0);
	contactLayout->setAlignment(Qt::AlignTop);
	for (const auto& info : contactInfos) {
		contactLayout->addWidget(info.button);
	}
	contactListWidget->setMinimumHeight(contactInfos.size() * contactHeight);
	contactListWidget->setFixedWidth(380);

	QObject::connect(searchField, &QLineEdit::textChanged, [=](const QString& text) {
		QString searchText = text.trimmed().toLower();
		int visibleCount = 0;
		for (auto& info : contactInfos) {
			bool isVisible = (searchText.isEmpty() || info.name.toLower().startsWith(searchText));
			info.button->setVisible(isVisible);
			if (isVisible) {
				visibleCount++;
			}
		}

		QVector<ContactInfo> sortedInfos = contactInfos;
		   sort(sortedInfos.begin(), sortedInfos.end(), [](const ContactInfo& a, const ContactInfo& b) {
			if (a.button->isVisible() != b.button->isVisible())
				return a.button->isVisible();
			return a.originalIndex < b.originalIndex;
			});

		QLayoutItem* item;
		while ((item = contactLayout->takeAt(0)) != nullptr) {
			delete item;
		}
		for (const auto& info : sortedInfos) {
			contactLayout->addWidget(info.button);
		}

		contactListWidget->setMinimumHeight(visibleCount * contactHeight);
		contactScrollArea->verticalScrollBar()->setValue(0);

		if (visibleCount == 0) {
			HidechatArea->show();
			chatMessagesWidget->hide();
			avatarLabel->clear();
			chatNameButton->setText("");
			selectedAvatar = nullptr;
			selectedNumber = -1; // Reset static member
		}
		});




	QAction* iconAction = new QAction(QIcon("icons/sending.png"), "", messageField);
	messageField->addAction(iconAction, QLineEdit::TrailingPosition);
	////////////////SAMA///////////SAMA////////////////SAMA/////////////SAMA//////////////////
	QObject::connect(messageField, &QLineEdit::returnPressed, [=]() {
		QString Fmessage = messageField->text().trimmed();
		if (!Fmessage.isEmpty() && selectedChatRoom != 0) { 
			int addedHeight = customized_chat(Fmessage, chatMessagesWidget, selectedChatRoom);
			chatMessagesWidget->setMinimumHeight(chatMessagesWidget->height() + addedHeight);
			messageField->clear(); 
			chatScrollArea->ensureVisible(0, chatMessagesWidget->height());

			// 2n
			for (const auto& info : contactInfos) {
				for (ChatRoom& room : users[currentUserID]->chatRooms) {
					if (room.getChatRoomID() == selectedChatRoom) {
						// Match the contact button to the chat room
						vector<int> userIDs = room.getUserIDs();
						int otherUserID = (userIDs[0] != currentUserID) ? userIDs[0] : userIDs[1];
						if (info.number == users[otherUserID]->getNumber()) {
							// Get the latest message
							vector<Message> messages = room.getMessages();
							if (!messages.empty()) {
								vector<Message> sortedMessages = sortMessagesBySentTime(messages);
								Message latestMessage = sortedMessages.back();
								QString messageText = QString::fromStdString(latestMessage.text);
								QString Qtime24 = QString::fromStdString(latestMessage.timeSent);
								QTime Qtime = QTime::fromString(Qtime24, "HH:mm:ss");
								QString Qtime12 = Qtime.toString("hh:mm AP");

								QLabel* messageLabel = info.button->findChild<QLabel*>("messageLabel");
								QLabel* messageLabelTime = info.button->findChild<QLabel*>("messageLabelTime");

								if (messageLabel) {
									QFontMetrics metrics(messageLabel->font());
									if (metrics.horizontalAdvance(messageText) > 225) {
										messageText = metrics.elidedText(
											messageText,
											Qt::ElideRight,  // Add "..." at the end
											225
										);
									}

									messageLabel->setText(messageText);
									messageLabelTime->setText(Qtime12);
								}
							}
							break;
						}
					}
				}
			}
		}
		});

	QObject::connect(iconAction, &QAction::triggered, [=]() {
		QString Fmessage = messageField->text().trimmed();
		if (!Fmessage.isEmpty() && selectedChatRoom != 0) { // Use global selectedChatRoom
			int addedHeight = customized_chat(Fmessage, chatMessagesWidget, selectedChatRoom);
			chatMessagesWidget->setMinimumHeight(chatMessagesWidget->height() + addedHeight);
			messageField->clear();
			chatScrollArea->ensureVisible(0, chatMessagesWidget->height());
			// 3n
			for (const auto& info : contactInfos) {
				for (ChatRoom& room : users[currentUserID]->chatRooms) {
					if (room.getChatRoomID() == selectedChatRoom) {
						// Match the contact button to the chat room
						vector<int> userIDs = room.getUserIDs();
						int otherUserID = (userIDs[0] != currentUserID) ? userIDs[0] : userIDs[1];
						if (info.number == users[otherUserID]->getNumber()) {
							// Get the latest message
							vector<Message> messages = room.getMessages();
							if (!messages.empty()) {
								vector<Message> sortedMessages = sortMessagesBySentTime(messages);
								Message latestMessage = sortedMessages.back();
								QString messageText = QString::fromStdString(latestMessage.text);
								QString Qtime24 = QString::fromStdString(latestMessage.timeSent);
								QTime Qtime = QTime::fromString(Qtime24, "HH:mm:ss");
								QString Qtime12 = Qtime.toString("hh:mm AP");

								QLabel* messageLabel = info.button->findChild<QLabel*>("messageLabel");
								QLabel* messageLabelTime = info.button->findChild<QLabel*>("messageLabelTime");

								if (messageLabel) {
									QFontMetrics metrics(messageLabel->font());
									if (metrics.horizontalAdvance(messageText) > 225) {
										messageText = metrics.elidedText(
											messageText,
											Qt::ElideRight,  // Add "..." at the end
											225
										);
									}

									messageLabel->setText(messageText);
									messageLabelTime->setText(Qtime12);
								}
							}
							break;
						}
					}
				}
			}
		}
		});
	////////////////////SAMA/////////////////SAMA////////////////SAMA/////////////SAMA////////////////////////

	QWidget* topBar = new QWidget(container);
	topBar->setGeometry(61, 0, 380, 66);
	topBar->setStyleSheet("background-color: #eef4f2; border: none;");

	QWidget* leftBar = new QWidget(container);
	leftBar->setGeometry(0, 0, 60, 720);

	QWidget* leftBarDevider = new QWidget(container);
	leftBarDevider->setGeometry(60, 0, 1, 720);
	leftBarDevider->setStyleSheet("background-color: #f9eded; border: none;");

	QLabel* title = new QLabel("Chats", topBar);
	QFont titleFont("Poppins", 21, QFont::Bold);
	title->setFont(titleFont);
	title->setStyleSheet("color: #222023; background: transparent;");
	title->adjustSize();
	title->move(14, 14);

	QToolButton* home_Button = new QToolButton(leftBar);
	home_Button->setIcon(QIcon("icons/home.png"));
	home_Button->setGeometry(-10, 0, 80, 66);
	home_Button->setIconSize(QSize(28, 28));
	home_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	home_Button->setStyleSheet(R"(
        QToolButton {
            color: white;
            background: none;
            background-color: #2a272a;
            border: none;
        }
    )");

	QToolButton* story_Button = new QToolButton(leftBar);
	story_Button->setIcon(QIcon("icons/story.png"));
	story_Button->setIconSize(QSize(28, 28));
	story_Button->setGeometry(-10, 66, 80, 66);
	story_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	story_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
        }
    )");

	QToolButton* group_Button = new QToolButton(leftBar);
	group_Button->setIcon(QIcon("icons/group-chat.png"));
	group_Button->setIconSize(QSize(30, 30));
	group_Button->setGeometry(-10, 132, 80, 66);
	group_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	group_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
        }
    )");

	QToolButton* settings_Button = new QToolButton(leftBar);
	settings_Button->setIcon(QIcon("icons/setting.png"));
	settings_Button->setIconSize(QSize(28, 28));
	settings_Button->setGeometry(-10, 654, 80, 66);
	settings_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	settings_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
        }
    )");

	QWidget* popUpContainer = new QWidget(container);
	popUpContainer->setGeometry(0, 0, 1280, 720);
	popUpContainer->setStyleSheet("background-color: rgba(0,0,0,200);");
	popUpContainer->hide();

	QWidget* popUpContacts = new QWidget(popUpContainer);
	popUpContacts->setGeometry(442, 270, 398, 180);
	popUpContacts->setStyleSheet("background-color: #eef4f2; border-radius: 7px;");

	QLineEdit* popUpNameField = new QLineEdit(popUpContacts);
	popUpNameField->setPlaceholderText("Name");
	popUpNameField->setGeometry(20, 47, 358, 30);
	if (users[currentUserID]->theme == 1) {
		popUpNameField->setStyleSheet(R"(
        QLineEdit {
            background-color: #d3e4dc;
            padding-left: 20px;
            border: none;
            border-radius: 7px;
            font-size: 15px;
            color: #222023;
        }
    )");
	}
	else {
		popUpNameField->setStyleSheet(R"(
        QLineEdit {
            background-color: #d4d9d7;
            padding-left: 20px;
            border: none;
            border-radius: 7px;
            font-size: 15px;
            color: #222023;
        }
    )");
	}

	QLineEdit* popUpNumberField = new QLineEdit(popUpContacts);
	QRegularExpression regex("^\\d{10}$");
	QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex, popUpNumberField);
	popUpNumberField->setValidator(validator);
	popUpNumberField->setPlaceholderText("Number");
	popUpNumberField->setGeometry(20, 88, 358, 30);
	if (users[currentUserID]->theme == 1) {
		popUpNumberField->setStyleSheet(R"(
        QLineEdit {
            background-color: #d3e4dc;
            padding-left: 49px;
            border: none;
            border-radius: 7px;
            font-size: 15px;
            color: #222023;
        }
    )");
	}
	else {
		popUpNumberField->setStyleSheet(R"(
        QLineEdit {
            background-color: #d4d9d7;
            padding-left: 49px;
            border: none;
            border-radius: 7px;
            font-size: 15px;
            color: #222023;
        }
    )");
	}

	QToolButton* popAddButton = new QToolButton(popUpContacts);
	popAddButton->setText("Add");
	popAddButton->setGeometry(20, 135, 50, 30);
	popAddButton->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	popAddButton->setFont(ButtonFont);

	QToolButton* popCloseButton = new QToolButton(popUpContacts);
	popCloseButton->setText("Close");
	popCloseButton->setGeometry(313, 135, 65, 30);
	if (users[currentUserID]->theme == 1) {
		popCloseButton->setStyleSheet(R"(
        background-color: #31473a;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	}
	else {
		popCloseButton->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	}
	popCloseButton->setFont(ButtonFont);

	QLabel* popLabel = new QLabel(popUpContacts);
	popLabel->setText("Add Contacts");
	popLabel->setGeometry(20, 4, 200, 40);
	QFont popFont("Poppins", 13, QFont::Bold);
	popLabel->setFont(popFont);
	if(users[currentUserID]->theme == 1) 	popLabel->setStyleSheet("color: #31473a; background: transparent;");
	else 	popLabel->setStyleSheet("color: #222023; background: transparent;");

	QLabel* popnumLabel = new QLabel(popUpContacts);
	popnumLabel->setText("+20");
	popnumLabel->setStyleSheet("font-size: 15px; color: #222023; border: 0; background: transparent;");
	popnumLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
	popnumLabel->setGeometry(popUpNumberField->x() + 20, popUpNumberField->y() + 5, 27, 20);

	QLabel* numberErrorLabel = new QLabel("Invalid phone number", popUpContacts);
	numberErrorLabel->setGeometry(133, 140, 178, 20);
	numberErrorLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	numberErrorLabel->hide();

	QLabel* numberErrorLabel2 = new QLabel("Number required", popUpContacts);
	numberErrorLabel2->setGeometry(146, 140, 160, 20);
	numberErrorLabel2->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	numberErrorLabel2->hide();

	QLabel* nameErrorLabel = new QLabel("Name required", popUpContacts);
	nameErrorLabel->setGeometry(152, 140, 160, 20);
	nameErrorLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	nameErrorLabel->hide();

	QLabel* emptyErrorLabel = new QLabel("Name and number required", popUpContacts);
	emptyErrorLabel->setGeometry(118, 140, 190, 20);
	emptyErrorLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	emptyErrorLabel->hide();

	QWidget* popUpContainer2 = new QWidget(container);
	popUpContainer2->setGeometry(0, 0, 1280, 720);
	popUpContainer2->setStyleSheet("background-color: rgba(0,0,0,200);");
	popUpContainer2->hide();

	QWidget* popUpContacts2 = new QWidget(popUpContainer2);
	popUpContacts2->setGeometry(442, 227.5, 398, 265);
	popUpContacts2->setStyleSheet("background-color: #eef4f2; border-radius: 7px;");

	QToolButton* popAddButton2 = new QToolButton(popUpContacts2);
	popAddButton2->setText("Add");
	popAddButton2->setGeometry(20, 218, 50, 30);
	popAddButton2->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	popAddButton2->setFont(ButtonFont);

	QToolButton* popCloseButton2 = new QToolButton(popUpContacts2);
	popCloseButton2->setText("Close");
	popCloseButton2->setGeometry(313, 218, 65, 30);
	popCloseButton2->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	popCloseButton2->setFont(ButtonFont);

	QLabel* popLabel2 = new QLabel(popUpContacts2);
	popLabel2->setText("Add Chat");
	popLabel2->setGeometry(20, 4, 200, 40);
	popLabel2->setFont(popFont);
	if(users[currentUserID]->theme == 1) popLabel2->setStyleSheet("color: #31473a; background: transparent;");
	else popLabel2->setStyleSheet("color: #222023; background: transparent;");

	QScrollArea* scrollArea = new QScrollArea(popUpContacts2);
	scrollArea->setGeometry(20, 46, 358, 158);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setStyleSheet("background-color: transparent; border: none;");

	QWidget* scrollPopContainer = new QWidget();
	scrollPopContainer->setStyleSheet("background-color: transparent;");

	QVBoxLayout* layout = new QVBoxLayout(scrollPopContainer);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(12);

	static int isSelected = 0;
	static int constrainti = 0;
	int indexi = 0;
	static int selected = 0;
	static int selected_index = 0;
	static vector<QPushButton*> btn;
	QLabel* userNotFoundLabel = new QLabel("This number doesn't have an account", popUpContacts2);
	userNotFoundLabel->setGeometry(92.5, 222, 210, 20);
	userNotFoundLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	userNotFoundLabel->hide();
	QLabel* userExistsLabel = new QLabel("Chat with this number already exists", popUpContacts2);
	userExistsLabel->setGeometry(96.5, 222, 210, 20);
	userExistsLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	userExistsLabel->hide();
	QLabel* NoUserSelectedLabel = new QLabel("Please select a number", popUpContacts2);
	NoUserSelectedLabel->setGeometry(131.5, 222, 150, 20);
	NoUserSelectedLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	NoUserSelectedLabel->hide();

	for (const auto& [num, name] : users[currentUserID]->getContacts()) {
		QString Qname = QString::fromStdString(name);

		btn.push_back(customizedPop_Contact(num, Qname, scrollPopContainer, -35));
		btn[indexi]->setFixedSize(358, 30);

		layout->addWidget(btn[indexi]);

		QObject::connect(btn[indexi], &QPushButton::clicked, [=]() mutable {
			userNotFoundLabel->hide();
			NoUserSelectedLabel->hide();
			userExistsLabel->hide();
			if (isSelected == 0) {

				QString bgColor = (users[currentUserID]->theme == 1) ? "#31473a" : "#222023";
				btn[indexi]->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QLabel {
        color: rgba(238, 244, 242, 127);
        background: transparent;
    }
    QLabel#numberLabel {
        color: #eef4f2;
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(238, 244, 242, 127);
        background: transparent;
    }
)").arg(bgColor));

				isSelected = 1;
				selected = num;
				selected_index = indexi;
			}
			else {
				if (num == selected) {
					QString bgColor = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";
					QString hoverColor = (users[currentUserID]->theme == 1) ? "#dce9e2" : "#e0e4e2";

					btn[indexi]->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QPushButton:hover {
        background-color: %2;
    }
    QLabel {
        color: rgba(34,32,35,110);
        background: transparent;
    }
    QLabel#numberLabel {
        color: rgba(34, 32, 35, 255);
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(0, 0, 0, 110); /* Change to rgba(34, 32, 35, 110) after testing */
        background: transparent;
    }
)").arg(bgColor).arg(hoverColor));


					isSelected = 0;
				}
				else {
					selected = num;
					QString bgColor = (users[currentUserID]->theme == 1) ? "#31473a" : "#222023";
					btn[indexi]->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QLabel {
        color: rgba(238, 244, 242, 127);
        background: transparent;
    }
    QLabel#numberLabel {
        color: #eef4f2;
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(238, 244, 242, 127);
        background: transparent;
    }
)").arg(bgColor));
					QString bgColor2 = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";
					QString hoverColor2 = (users[currentUserID]->theme == 1) ? "#dce9e2" : "#e0e4e2";

					btn[selected_index]->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QPushButton:hover {
        background-color: %2;
    }
    QLabel {
        color: rgba(34,32,35,110);
        background: transparent;
    }
    QLabel#numberLabel {
        color: rgba(34, 32, 35, 255);
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(0, 0, 0, 110); /* Change to rgba(34, 32, 35, 110) after testing */
        background: transparent;
    }
)").arg(bgColor2).arg(hoverColor2));

					selected_index = indexi;
				}
			}
			});

		indexi++;
	}

	QObject::connect(popAddButton2, &QPushButton::clicked, [=]() {

		if (isSelected == 1) {
			bool userExists = false;
			for (const auto& [id, user] : users) {
				if (user->getNumber() == selected) {
					userExists = true;
					break;
				}
			}
			if (!userExists) {
				userNotFoundLabel->show();
			}
			else {
				bool testing = true;
				//ADDING HERE
				vector<int> v = { currentUserID, getUserByNumber(selected) };
				ChatRoom c(maxChatID() + 1, v);
				for (auto ChatRoom : users[currentUserID]->chatRooms) {
					if (ChatRoom.type() == "Private") {
						if ((ChatRoom.getUserIDs()[0] == currentUserID || ChatRoom.getUserIDs()[0] == getUserByNumber(selected)) && (ChatRoom.getUserIDs()[1] == currentUserID || ChatRoom.getUserIDs()[1] == getUserByNumber(selected))) {
							userExistsLabel->show();
							testing = false;
						}

					}
				}
				if (testing) {
					users[currentUserID]->addChatRoom(c);
					users[getUserByNumber(selected)]->addChatRoom(c);
					updateUsersToJson();
					//reset
					QString bgColor2 = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";
					QString hoverColor2 = (users[currentUserID]->theme == 1) ? "#dce9e2" : "#e0e4e2";

					btn[selected_index]->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QPushButton:hover {
        background-color: %2;
    }
    QLabel {
        color: rgba(34,32,35,110);
        background: transparent;
    }
    QLabel#numberLabel {
        color: rgba(34, 32, 35, 255);
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(0, 0, 0, 110); /* Change to rgba(34, 32, 35, 110) after testing */
        background: transparent;
    }
)").arg(bgColor2).arg(hoverColor2));
					isSelected = 0;
					btn.clear();
					QLayoutItem* item;
					while ((item = layout->takeAt(0)) != nullptr) {
						if (QWidget* widget = item->widget()) {
							delete widget;
						}
						delete item;
					}
					container->hide();
					chat_Screen(window);
				}

			}
		}
		else {
			NoUserSelectedLabel->show();
		}

		});

	QObject::connect(popCloseButton2, &QPushButton::clicked, [=]() {
		//reset
		for (auto& button : btn) {
			QString bgColor2 = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";
			QString hoverColor2 = (users[currentUserID]->theme == 1) ? "#dce9e2" : "#e0e4e2";

			button->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QPushButton:hover {
        background-color: %2;
    }
    QLabel {
        color: rgba(34,32,35,110);
        background: transparent;
    }
    QLabel#numberLabel {
        color: rgba(34, 32, 35, 255);
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(0, 0, 0, 110); /* Change to rgba(34, 32, 35, 110) after testing */
        background: transparent;
    }
)").arg(bgColor2).arg(hoverColor2));
		}
		userNotFoundLabel->hide();
		NoUserSelectedLabel->hide();
		userExistsLabel->hide();
		popUpContainer2->hide();
		isSelected = 0;
		});

	QObject::connect(popAddButton, &QPushButton::clicked, [=]() {
		numberErrorLabel->hide();
		numberErrorLabel2->hide();
		nameErrorLabel->hide();
		emptyErrorLabel->hide();

		QString phoneNumber = popUpNumberField->text();
		QString name = popUpNameField->text().trimmed();
		bool hasError = false;

		if (phoneNumber.isEmpty() && name.isEmpty()) {
			emptyErrorLabel->show();
			hasError = true;
		}
		else if (name.isEmpty()) {
			nameErrorLabel->show();
			hasError = true;
		}
		else if (phoneNumber.isEmpty()) {
			numberErrorLabel2->show();
			hasError = true;
		}
		else if (phoneNumber.length() != 10 || phoneNumber.at(0) == '0') {
			numberErrorLabel->show();
			hasError = true;
		}
		if (!hasError) {
			//Add number
			users[currentUserID]->addContacts(phoneNumber.toInt(), name.toStdString());
			updateUsersToJson();
			popUpContainer->hide();
			isSelected = 0;
			btn.clear();
			QLayoutItem* item;
			while ((item = layout->takeAt(0)) != nullptr) {
				if (QWidget* widget = item->widget()) {
					delete widget;
				}
				delete item;
			}
			container->hide();
			chat_Screen(window);
		}
		});

	scrollArea->setWidget(scrollPopContainer);


	if (users[currentUserID]->theme == 1) {

		Button3->setStyleSheet(R"(
    background-color: #31473a;
    border: none;
    border-radius: 15px;
    color: #e4d9d7;
    )");
		Button4->setStyleSheet(R"(
    background-color: #31473a;
    border: none;
    border-radius: 15px;
    color: #e4d9d7;
    )");
		leftBar->setStyleSheet("background-color: #31473a; border: none;");
		home_Button->setStyleSheet(R"(
    QToolButton {
        color: white;
        background: none;
        background-color: #2f3f36;
        border: none;
    }
)");
		popCloseButton2->setStyleSheet(R"(
        background-color: #31473a;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
		popAddButton2->setStyleSheet(R"(
    background-color: #31473a;
    border: none;
    border-radius: 7px;
    color: #e4d9d7;
)");
		popCloseButton->setStyleSheet(R"(
    background-color: #31473a;
    border: none;
    border-radius: 7px;
    color: #e4d9d7;
)");
		popAddButton->setStyleSheet(R"(
    background-color: #31473a;
    border: none;
    border-radius: 7px;
    color: #e4d9d7;
)");

		searchField->setStyleSheet(R"(
    QLineEdit {
        background-color: #31473a;
        padding-left: 20px;
        border: none;
        border-radius: 7px;
        font-size: 15px;
        color: #eef4f2;
    }
    )");
		Button3->setStyleSheet(R"(
    background-color: #31473a;
    border: none;
    border-radius: 15px;
    color: #e4d9d7;
    )");

		leftBar->setStyleSheet("background-color: #31473a; border: none;");
		title->setStyleSheet("color: #31473a; background: transparent;");
		messageField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 18px;
        border: none;
        border-radius: 7px;
        font-size: 14px;
        background: #4b6d59;
        color: #ffffff;
    }
)");
	}
	else {

		Button3->setStyleSheet(R"(
    background-color: #222023;
    border: none;
    border-radius: 15px;
    color: #e4d9d7;
    )");
		Button4->setStyleSheet(R"(
    background-color: #222023;
    border: none;
    border-radius: 15px;
    color: #e4d9d7;
    )");
		leftBar->setStyleSheet("background-color: #222023; border: none;");

		home_Button->setStyleSheet(R"(
    QToolButton {
        color: white;
        background: none;
        background-color: #2a272a;
        border: none;
    }
)");
		searchField->setStyleSheet(R"(
    QLineEdit {
        background-color: #222023;
        padding-left: 20px;
        border: none;
        border-radius: 7px;
        font-size: 15px;
        color: #eef4f2;
    }
    )");
		Button3->setStyleSheet(R"(
    background-color: #222023;
    border: none;
    border-radius: 15px;
    color: #e4d9d7;
    )");


		leftBar->setStyleSheet("background-color: #222023; border: none;");
		title->setStyleSheet("color: #222023; background: transparent;");
		messageField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 18px;
        border: none;
        border-radius: 7px;
        font-size: 14px;
        background: #2d2c2d;
        color: #ffffff;
    }
)");

	}


	QObject::connect(Button3, &QPushButton::clicked, [=]() {
		popUpContainer->show();

		});

	QObject::connect(popCloseButton, &QPushButton::clicked, [=]() {
		popUpContainer->hide();

		});

	QObject::connect(Button4, &QPushButton::clicked, [=]() {
		popUpContainer2->show();

		});

	QObject::connect(story_Button, &QPushButton::clicked, [=]() {
		container->hide();
		isSelected = 0;
		btn.clear();
		QLayoutItem* item;
		while ((item = layout->takeAt(0)) != nullptr) {
			if (QWidget* widget = item->widget()) {
				delete widget;
			}
			delete item;
		}
		container->hide();
		project_Gui::story_Screen(window);
		});

	QObject::connect(settings_Button, &QPushButton::clicked, [=]() {
		container->hide();
		isSelected = 0;
		btn.clear();
		QLayoutItem* item;
		while ((item = layout->takeAt(0)) != nullptr) {
			if (QWidget* widget = item->widget()) {
				delete widget;
			}
			delete item;
		}
		container->hide();
		project_Gui::setting_Screen(window);
		});

	QObject::connect(group_Button, &QPushButton::clicked, [=]() {
		container->hide();
		isSelected = 0;
		btn.clear();
		QLayoutItem* item;
		while ((item = layout->takeAt(0)) != nullptr) {
			if (QWidget* widget = item->widget()) {
				delete widget;
			}
			delete item;
		}
		container->hide();
		project_Gui::group_Screen(window);
		});

	// Pop-up for user info
	QWidget* infoPopUpContainer = new QWidget(container);
	infoPopUpContainer->setGeometry(0, 0, 1280, 720);
	infoPopUpContainer->setStyleSheet("background-color: rgba(0,0,0,200);");
	infoPopUpContainer->hide();

	QWidget* infoPopUp = new QWidget(infoPopUpContainer);
	infoPopUp->setGeometry(491, 200, 300, 320);
	infoPopUp->setStyleSheet("background-color: #eef4f2; border-radius: 7px;");

	QLabel* infoName = new QLabel(infoPopUp);
	infoName->setGeometry(0, 130, 300, 30);
	infoName->setAlignment(Qt::AlignHCenter);
	infoName->setStyleSheet("color: #222023; background: transparent; font-size: 24px;");

	QLabel* infoNumber = new QLabel(infoPopUp);
	infoNumber->setGeometry(0, 160, 300, 30);
	infoNumber->setAlignment(Qt::AlignHCenter);
	infoNumber->setStyleSheet("color: rgba(34, 32, 35, 190); background: transparent; font-size: 14px;");

	QLabel* infoAbout = new QLabel(infoPopUp);
	infoAbout->setGeometry(10, 200, 280, 60);
	infoAbout->setAlignment(Qt::AlignHCenter);
	infoAbout->setWordWrap(true);
	infoAbout->setStyleSheet("color: #222023; background: transparent; font-size: 12px;");

	QToolButton* closeInfoButton = new QToolButton(infoPopUp);
	closeInfoButton->setText("Close");
	closeInfoButton->setGeometry(115, 270, 70, 30);
	closeInfoButton->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	closeInfoButton->setFont(ButtonFont);
	closeInfoButton->setCursor(Qt::PointingHandCursor);


	// Store selected user's phone number
	auto showUserInfo = [=]() {
		if (selectedNumber != -1) { // Use static member
			int userId = getUserByNumber(selectedNumber);
			if (userId != -1) {
				User* user = users[userId];
				QString fullName = QString::fromStdString(user->Fname + " " + user->Lname);
				infoName->setText(fullName);
				infoNumber->setText("+20" + QString::number(user->getNumber()));
				infoAbout->setText(user->profile.about == "" ? "Hey there! I'm using What's Wrong" : QString::fromStdString(user->profile.about));

				QLabel* avatar = new QLabel(infoPopUp);
				avatar->setGeometry(100, 20, 100, 100);
				avatar->setStyleSheet("background-color: transparent; border-radius: 50px;");
				QPixmap pixmap(selectedAvatar);
				QPixmap roundedPixmap(pixmap.size());
				roundedPixmap.fill(Qt::transparent);

				QPainter painter(&roundedPixmap);
				painter.setRenderHint(QPainter::Antialiasing);
				QPainterPath path;
				path.addEllipse(0, 0, pixmap.width(), pixmap.height());
				painter.setClipPath(path);
				painter.drawPixmap(0, 0, pixmap);
				painter.end();
				avatar->setPixmap(roundedPixmap.scaled(100, 100, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
				avatar->setStyleSheet("border-radius: 50px;");
				infoPopUpContainer->show();
			}
		}
		};
	QObject::connect(chatNameButton, &QPushButton::clicked, showUserInfo);
	QObject::connect(avatarButton, &QPushButton::clicked, showUserInfo);
	QObject::connect(closeInfoButton, &QToolButton::clicked, [=]() {
		infoPopUpContainer->hide();
		});


	container->show();
}

void project_Gui::story_Screen(QWidget* window) {

	QWidget* container = new QWidget(window);
	container->setGeometry(0, 0, 1280, 720);
	//contacts room
	QWidget* contactsArea = new QWidget(container);
	contactsArea->setGeometry(61, 50, 380, 720);
	contactsArea->setStyleSheet("border: none; background-color: #eef4f2;");


	//chats room
	QWidget* chatArea = new QWidget(container);
	chatArea->setGeometry(442, 0, 838, 720);
	chatArea->show();


	QFont titleFont("Poppins", 20, QFont::Bold);
	QVBoxLayout* mainLayout = new QVBoxLayout(contactsArea);
	mainLayout->setContentsMargins(0, 10, 0, 10);
	mainLayout->setSpacing(0);

	QPushButton* userContactBtn = customized_Story(QString::fromStdString(users[currentUserID]->Fname), contactsArea, users[currentUserID]->avatar != "" ? QString::fromStdString(users[currentUserID]->avatar) : "icons/default.jpg");
	userContactBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #dde3e1;
            text-align: left;
            border: none;
            padding-left: 70px;
            font-size: 20px;
            color: black;
        }
	)");
	mainLayout->addWidget(userContactBtn);  // Top contact button
	mainLayout->addSpacing(5);

	QLabel* userContactBtnDev = new QLabel(contactsArea);
	userContactBtnDev->setFixedHeight(1);
	userContactBtnDev->setFixedWidth(348);
	userContactBtnDev->setStyleSheet("background-color: #b4b7b7; border: none;");
	mainLayout->addWidget(userContactBtnDev, 0, Qt::AlignHCenter | Qt::AlignTop);  // Centered horizontally
	mainLayout->addSpacing(1);

	QLabel* userContactBtnDe2 = new QLabel(contactsArea);
	userContactBtnDe2->setFixedHeight(1);
	userContactBtnDe2->setFixedWidth(348);
	userContactBtnDe2->setStyleSheet("background-color: #b4b7b7; border: none;");
	mainLayout->addWidget(userContactBtnDe2, 0, Qt::AlignHCenter | Qt::AlignTop);  // Centered horizontally

	// 2. Scrollable area for other contacts
	QScrollArea* scrollArea = new QScrollArea(contactsArea);
	scrollArea->setWidgetResizable(true);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setStyleSheet("border: none;");

	mainLayout->addWidget(scrollArea);

	// 3. Scrollable content widget
	QWidget* scrollContent = new QWidget();
	scrollContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	scrollArea->setWidget(scrollContent);

	QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);
	scrollLayout->setContentsMargins(0, 10, 0, 10);
	scrollLayout->setSpacing(0);

	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	contactsArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


	QFont storyFont("Poppins", 10);


	QLabel* EmptyLabel = new QLabel(chatArea);
	EmptyLabel->setGeometry(964 - 442, 70, 275, 610);
	EmptyLabel->setStyleSheet("background: transparent; color: #d4d9d7");
	EmptyLabel->setFont(storyFont);
	EmptyLabel->setText("Empty");
	EmptyLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	QLabel* uploadedImageLabel = new QLabel(chatArea);
	uploadedImageLabel->setGeometry(964 - 442, 70, 275, 610); // Adjusted to fit within phone's "screen"
	uploadedImageLabel->setStyleSheet("background: black;");
	if (users[currentUserID]->story.photoPath != "") {
		QPixmap originalPixmap(QString::fromStdString(users[currentUserID]->story.photoPath));
		if (originalPixmap.isNull()) {
			qWarning() << "Failed to load image";
			return;
		}

		QPixmap stretchedPixmap = originalPixmap.scaled(
			uploadedImageLabel->width(),
			uploadedImageLabel->height(),
			Qt::IgnoreAspectRatio,  // Allows stretching
			Qt::SmoothTransformation
		);
		uploadedImageLabel->setPixmap(stretchedPixmap);
		uploadedImageLabel->show();
	}


	QLabel* currentStoryLabelTEST = new QLabel(chatArea);
	currentStoryLabelTEST->move(-100, -490);//
	currentStoryLabelTEST->setMaximumHeight(20);//
	currentStoryLabelTEST->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	currentStoryLabelTEST->setStyleSheet("font-size: 10px; color: #eef4f2; background: rgba(0,0,0,133);");


	QLabel* currentStoryLabel = new QLabel(chatArea);
	currentStoryLabel->setGeometry(964 - 442, 390, 275, 20);
	currentStoryLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	currentStoryLabel->setStyleSheet("font-size: 10px; color: #eef4f2; background: rgba(0, 0, 0, 150);");
	if (users[currentUserID]->story.content != "") {
		currentStoryLabel->setText(QString::fromStdString(users[currentUserID]->story.content));
		currentStoryLabel->show();
	}
	else
		currentStoryLabel->hide();



	//Contacts
	QWidget* contactsChatArea = new QWidget(container);
	contactsChatArea->setGeometry(442, 0, 838, 720);
	contactsChatArea->hide();

	QLabel* contactsUploadedImageLabel = new QLabel(contactsChatArea);
	contactsUploadedImageLabel->setGeometry(7, 0, 330, 720);
	contactsUploadedImageLabel->setStyleSheet("background: black;");

	QLabel* contactsLabel = new QLabel(contactsUploadedImageLabel);
	contactsLabel->setGeometry(0, 360, 330, 25);
	contactsLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	contactsLabel->setStyleSheet(R"(
		background-color: rgba(0, 0, 0, 150); 
		color: #eef4f2; 
		font-size: 13px;
	)");

	QWidget* topBarDevider01 = new QWidget(contactsChatArea);
	topBarDevider01->setGeometry(7, 0, 1, 720);
	topBarDevider01->setStyleSheet("background-color: #f9eded; border: none;");
	QWidget* topBarDevider02 = new QWidget(contactsChatArea);
	topBarDevider02->setGeometry(337, 0, 1, 720);
	topBarDevider02->setStyleSheet("background-color: #f9eded; border: none;");

	QLabel* contactsMiniAvatar = new QLabel(contactsChatArea);
	contactsMiniAvatar->setGeometry(21, 20, 30, 30);
	contactsMiniAvatar->setStyleSheet("background-color: transparent;  border-radius: 15px;");

	QLabel* contactsMiniAvatarName = new QLabel(contactsChatArea);
	contactsMiniAvatarName->move(61, 25);
	contactsMiniAvatarName->setStyleSheet("background-color: transparent; color: #eef4f2; font-size: 15px;");

	QLabel* contactsMiniAvatarDate = new QLabel(contactsChatArea);
	contactsMiniAvatarDate->setStyleSheet("background-color: transparent; color: rgba(238, 244, 242, 122); font-size: 11px;");

	QLabel* contactsBigAvatar = new QLabel(contactsChatArea);
	contactsBigAvatar->setGeometry(489, 102, 200, 200);
	contactsBigAvatar->setStyleSheet("background-color: transparent;  border-radius: 100px;");

	QLabel* contactsBigAvatarName = new QLabel(contactsChatArea);
	contactsBigAvatarName->setGeometry(338, 332, 501, 100);
	contactsBigAvatarName->setAlignment(Qt::AlignHCenter);
	contactsBigAvatarName->setStyleSheet("background-color: transparent; color: rgb(238,244,242); font-size: 35px;");

	QLabel* contactsBigAvatarNumber = new QLabel(contactsChatArea);
	contactsBigAvatarNumber->setGeometry(338, 376, 501, 100);
	contactsBigAvatarNumber->setAlignment(Qt::AlignHCenter);
	contactsBigAvatarNumber->setStyleSheet("background-color: transparent; color: rgba(238,244,242,102); font-size: 25px;");

	QLabel* contactsBigAvatarAbout = new QLabel(contactsChatArea);
	contactsBigAvatarAbout->setGeometry(351, 430, 475, 222);
	contactsBigAvatarAbout->setAlignment(Qt::AlignHCenter);
	contactsBigAvatarAbout->setStyleSheet("background-color: transparent; color: rgb(238,244,242); font-size: 22px;");
	contactsBigAvatarAbout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	contactsBigAvatarAbout->setWordWrap(true);

	QLabel* safeMessagesIcon = new QLabel(contactsChatArea);
	QPixmap iconPixmap("icons/safeMessages.png");
	safeMessagesIcon->setPixmap(iconPixmap);
	safeMessagesIcon->setAttribute(Qt::WA_TranslucentBackground);


	QGraphicsDropShadowEffect* Cshadow67 = new QGraphicsDropShadowEffect();
	Cshadow67->setBlurRadius(8);
	Cshadow67->setOffset(0, 0);
	Cshadow67->setColor(QColor(0, 0, 0, 222));
	QGraphicsDropShadowEffect* Cshadow68 = new QGraphicsDropShadowEffect();
	Cshadow68->setBlurRadius(10);
	Cshadow68->setOffset(0, 0);
	Cshadow68->setColor(QColor(0, 0, 0, 40));
	QGraphicsDropShadowEffect* Cshadow69 = new QGraphicsDropShadowEffect();
	Cshadow69->setBlurRadius(2);
	Cshadow69->setOffset(0, 0);
	Cshadow69->setColor(QColor(0, 0, 0, 140));

	contactsMiniAvatarName->setGraphicsEffect(Cshadow67);
	contactsMiniAvatarDate->setGraphicsEffect(Cshadow69);
	contactsMiniAvatar->setGraphicsEffect(Cshadow68);





	QLabel* phone = new QLabel(chatArea);
	phone->move(0 - 442, 0);
	if (users[currentUserID]->theme == 1) phone->setPixmap(QPixmap("icons/phone2.png"));
	else phone->setPixmap(QPixmap("icons/phone.png"));
	phone->setStyleSheet("background: transparent;");
	phone->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	QLabel* miniAvatar = new QLabel(phone);
	miniAvatar->setGeometry(981, 88, 30, 30);
	miniAvatar->setStyleSheet("background-color: transparent; border-radius: 15px;");

	QPixmap pixmap68(users[currentUserID]->avatar != "" ? QString::fromStdString(users[currentUserID]->avatar) : "icons/default.jpg");
	QPixmap roundedPixmap68(pixmap68.size());
	roundedPixmap68.fill(Qt::transparent);

	QPainter painter68(&roundedPixmap68);
	painter68.setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addEllipse(0, 0, pixmap68.width(), pixmap68.height());
	painter68.setClipPath(path);
	painter68.drawPixmap(0, 0, pixmap68);
	painter68.end();

	miniAvatar->setPixmap(roundedPixmap68.scaled(30, 30, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
	miniAvatar->setStyleSheet("border-radius: 20px;");

	QLabel* miniAvatarName = new QLabel(phone);
	miniAvatarName->setText(QString::fromStdString(users[currentUserID]->Fname) +
		(users[currentUserID]->Lname.empty() ? "" : " " + QString::fromStdString(users[currentUserID]->Lname)));
	QTimer::singleShot(0, [miniAvatarName]() {
		miniAvatarName->adjustSize();
		miniAvatarName->move(1021, 90);
		});
	miniAvatarName->setStyleSheet("background-color: transparent; color: #eef4f2; font-size: 15px;");

	QLabel* miniAvatarDate = new QLabel(phone);
	miniAvatarDate->setStyleSheet("background-color: transparent; color: rgba(238, 244, 242, 122); font-size: 11px;");


	QString timestamp0 = QString::fromStdString(users[currentUserID]->story.publishedTime);
	QDateTime timestampTime0 = QDateTime::fromString(timestamp0, "yyyy-MM-dd HH:mm:ss");
	QDateTime currentTime0 = QDateTime::currentDateTime();
	qint64 secondsElapsed0 = timestampTime0.secsTo(currentTime0);
	QString result0;

	if (secondsElapsed0 < 60) {
		result0 = QString::number(secondsElapsed0) + "s";
	}
	else if (secondsElapsed0 < 3600) {
		result0 = QString::number(secondsElapsed0 / 60) + "m";
	}
	else {
		result0 = QString::number(secondsElapsed0 / 3600) + "h";
	}
	miniAvatarDate->setText(result0);
	QTimer::singleShot(0, [miniAvatarDate, miniAvatarName]() {
		miniAvatarDate->adjustSize();
		miniAvatarDate->move(miniAvatarName->pos().x() + miniAvatarName->width() + 5, miniAvatarName->pos().y() + 4);
		});




	if (users[currentUserID]->story.content == "" && users[currentUserID]->story.photoPath == "") {
		uploadedImageLabel->hide();
		currentStoryLabel->hide();
	}

	QGraphicsDropShadowEffect* shadow67 = new QGraphicsDropShadowEffect();
	shadow67->setBlurRadius(8);
	shadow67->setOffset(0, 0);
	shadow67->setColor(QColor(0, 0, 0, 222));
	QGraphicsDropShadowEffect* shadow68 = new QGraphicsDropShadowEffect();
	shadow68->setBlurRadius(10);
	shadow68->setOffset(0, 0);
	shadow68->setColor(QColor(0, 0, 0, 90));

	miniAvatarName->setGraphicsEffect(shadow67);
	miniAvatar->setGraphicsEffect(shadow68);
	QFont titleFont28("Poppins", 15, QFont::Bold);
	// ----- UNOPENED STORIES -----
	QLabel* unopenedLabel = new QLabel("Unopened Stories", scrollContent);
	unopenedLabel->setFont(titleFont28);
	if (users[currentUserID]->theme == 1) {
		unopenedLabel->setStyleSheet(R"(
		color: #31473a;
		margin-left: 6px;
	)");
	}
	else {
		unopenedLabel->setStyleSheet(R"(
		color: #222023;
		margin-left: 6px;
	)");
	}

	scrollLayout->addSpacing(6);
	scrollLayout->addWidget(unopenedLabel);
	scrollLayout->addSpacing(6);

	static int totalNumOfUsersInScreen1 = 0;
	static int totalNumOfUsersInScreen2 = 0;
	int scrollContentConst = 134;
	QVBoxLayout* unopenedLayout = new QVBoxLayout;
	QVBoxLayout* openedLayout = new QVBoxLayout;
	QLabel* userContactBtnDev2;
	// ----- UNOPENED STORIES -----


	// Get current user's contacts
	  set<int> currentUserContacts;
	for (const auto& [key, _] : users[currentUserID]->getContacts()) {
		currentUserContacts.insert(key);
	}
	bool tmp_1 = false;
	bool tmp_2 = false;

	for (auto& [id, user] : users) {
		if (id == currentUserID) continue;

		tmp_1 = false;
		tmp_2 = false;
		auto otherContacts = user->getContacts();

		for (const auto& number : currentUserContacts) {
			if (number == users[id]->getNumber()) {
				tmp_1 = true;
				break;
			}
		}


		for (const auto& number : otherContacts) {
			if (number.first == users[currentUserID]->getNumber()) {
				tmp_2 = true;
				break;
			}
		}

		if (tmp_1 && tmp_2) {
			bool isUnopened = find(user->story.viewers.begin(), user->story.viewers.end(), currentUserID) == user->story.viewers.end();

			if ((user->story.content != "" || user->story.photoPath != "") && user->profile.visibility && isUnopened) {
				totalNumOfUsersInScreen1++;
				QPushButton* contactBtn = customized_Story(QString::fromStdString(user->Fname), nullptr, QString::fromStdString(user->avatar));
				unopenedLayout->addWidget(contactBtn);

				userContactBtnDev2 = new QLabel(contactsArea);
				QLabel* StoryAvatar = contactBtn->findChild<QLabel*>("storyAvatar");
				QString storyAvatarPath = user->avatar != "" ? QString::fromStdString(user->avatar) : "icons/default.jpg";
				if (!storyAvatarPath.isEmpty()) {
					QPixmap pixmap(storyAvatarPath);
					QPixmap scaledPixmap = pixmap.scaled(42, 42, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

					QPixmap finalPixmap(42, 42);
					finalPixmap.fill(Qt::transparent);

					QPainter painter(&finalPixmap);
					painter.setRenderHint(QPainter::Antialiasing);

					QPainterPath path;
					path.addEllipse(0, 0, 42, 42);
					painter.setClipPath(path);

					painter.drawPixmap(0, 0, scaledPixmap);

					painter.setClipping(false);

					// Draw the light gray circle border
					QPen blackPen(QColor("#eef4f2"));
					blackPen.setWidth(3);
					painter.setPen(blackPen);
					painter.setBrush(Qt::NoBrush);
					painter.drawEllipse(2, 2, 38, 38);

					// Draw the green gradient "guardian" border
					QConicalGradient gradient(21, 21, 0);
					gradient.setColorAt(0.0, QColor("#00cc66"));
					gradient.setColorAt(0.25, QColor("#00e673"));
					gradient.setColorAt(0.5, QColor("#1aff66"));
					gradient.setColorAt(0.75, QColor("#66ff99"));
					gradient.setColorAt(1.0, QColor("#00cc66"));

					QPen greenPen(QBrush(gradient), 2);
					painter.setPen(greenPen);
					painter.setBrush(Qt::NoBrush);
					painter.drawEllipse(1, 1, 40, 40);

					painter.end();
					StoryAvatar->setPixmap(finalPixmap);
				}


				userContactBtnDev2->setFixedHeight(1);
				userContactBtnDev2->setFixedWidth(380);
				userContactBtnDev2->setStyleSheet("background-color: rgba(0,0,0,15); margin-left: 60px;");
				unopenedLayout->addWidget(userContactBtnDev2);

				QObject::connect(contactBtn, &QPushButton::clicked, [=, &scrollContentConst]() {
					chatArea->hide();
					contactsChatArea->show();
					if (unopenedLayout->indexOf(contactBtn) != -1) {
						if (!storyAvatarPath.isEmpty()) {
							QPixmap pixmap(storyAvatarPath);
							QPixmap scaledPixmap = pixmap.scaled(42, 42, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

							QPixmap finalPixmap(42, 42);
							finalPixmap.fill(Qt::transparent);

							QPainter painter(&finalPixmap);
							painter.setRenderHint(QPainter::Antialiasing);

							QPainterPath path;
							path.addEllipse(0, 0, 42, 42);
							painter.setClipPath(path);

							painter.drawPixmap(0, 0, scaledPixmap);

							painter.setClipping(false);

							// Draw the light gray circle border
							QPen blackPen(QColor("#eef4f2"));
							blackPen.setWidth(3);
							painter.setPen(blackPen);
							painter.setBrush(Qt::NoBrush);
							painter.drawEllipse(2, 2, 38, 38);

							// Draw the green gradient "guardian" border
							QConicalGradient gradient(21, 21, 0);
							gradient.setColorAt(0.0, QColor("#A9A9A9"));

							QPen greenPen(QBrush(gradient), 2);
							painter.setPen(greenPen);
							painter.setBrush(Qt::NoBrush);
							painter.drawEllipse(1, 1, 40, 40);

							painter.end();	StoryAvatar->setPixmap(finalPixmap);
						}

						totalNumOfUsersInScreen1--;
						totalNumOfUsersInScreen2++;
						if (unopenedLayout->indexOf(userContactBtnDev2) != -1) {
							openedLayout->addWidget(userContactBtnDev2);
							openedLayout->addWidget(contactBtn);
						}
						else {
							QLabel* userContactBtnDev3 = new QLabel(contactsArea);
							userContactBtnDev3->setFixedHeight(1);
							userContactBtnDev3->setFixedWidth(380);
							userContactBtnDev3->setStyleSheet("background-color: rgba(0,0,0,15); margin-left: 60px;");
							openedLayout->addWidget(userContactBtnDev3);
							openedLayout->addWidget(contactBtn);
							QLayoutItem* lastItem = unopenedLayout->takeAt(unopenedLayout->count() - 1);

							if (lastItem) {
								QWidget* lastWidget = lastItem->widget();
								if (lastWidget) {
									lastWidget->hide();
									lastWidget->deleteLater();
								}
								delete lastItem;
							}
						}
						if (totalNumOfUsersInScreen1 == 0) {
							QLabel* L = new QLabel(contactsArea);
							L->setText("Empty");
							L->setStyleSheet("  background-color: transparent; border: none; font-size: 12px; color: rgba(0, 0, 0, 95);");
							L->setFixedHeight(62);
							L->setFixedWidth(380);
							L->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
							L->setObjectName("unopenedEmpty");
							unopenedLayout->addWidget(L);
							scrollContentConst += 62;
							scrollContent->setMinimumHeight(scrollContent->height() + 62);

						}
					}

					QPixmap originalPixmap(QString::fromStdString(user->story.photoPath));

					QPixmap stretchedPixmap = originalPixmap.scaled(
						contactsUploadedImageLabel->width(),
						contactsUploadedImageLabel->height(),
						Qt::IgnoreAspectRatio,
						Qt::SmoothTransformation
					);
					contactsUploadedImageLabel->setPixmap(stretchedPixmap);
					contactsUploadedImageLabel->show();

					QPixmap pixmap66(user->avatar != "" ? QString::fromStdString(user->avatar) : "icons/default.jpg");
					QPixmap roundedPixmap66(pixmap66.size());
					roundedPixmap66.fill(Qt::transparent);
					QPainter painter66(&roundedPixmap66);

					painter66.setRenderHint(QPainter::Antialiasing);
					QPainterPath path66;
					path66.addEllipse(0, 0, pixmap66.width(), pixmap66.height());
					painter66.setClipPath(path66);
					painter66.drawPixmap(0, 0, pixmap66);
					painter66.end();
					contactsMiniAvatar->setPixmap(roundedPixmap66.scaled(30, 30, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
					contactsBigAvatar->setPixmap(roundedPixmap66.scaled(200, 200, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

					contactsBigAvatarName->setText(QString::fromStdString(user->Fname) +
						(user->Lname.empty() ? "" : " " + QString::fromStdString(user->Lname)));
					contactsBigAvatarNumber->setText("+20" + QString::fromStdString(to_string(user->getNumber())));
					contactsBigAvatarAbout->setText(user->profile.about != "" ? QString::fromStdString(user->profile.about) : "Hey there! I'm using What's Wrong");

					if (user->story.content != "") {
						contactsLabel->setText(QString::fromStdString(user->story.content));
						contactsLabel->show();
					}
					else {
						contactsLabel->hide();
					}

					QString timestamp = QString::fromStdString(user->story.publishedTime);
					QDateTime timestampTime = QDateTime::fromString(timestamp, "yyyy-MM-dd HH:mm:ss");
					QDateTime currentTime = QDateTime::currentDateTime();
					qint64 secondsElapsed = timestampTime.secsTo(currentTime);
					QString result;

					if (secondsElapsed < 60) {
						result = QString::number(secondsElapsed) + "s";
					}
					else if (secondsElapsed < 3600) {
						result = QString::number(secondsElapsed / 60) + "m";
					}
					else {
						result = QString::number(secondsElapsed / 3600) + "h";
					}
					contactsMiniAvatarName->setText(QString::fromStdString(user->Fname) +
						(user->Lname.empty() ? "" : " " + QString::fromStdString(user->Lname)));
					contactsMiniAvatarName->adjustSize();
					contactsMiniAvatarDate->setText(result);
					contactsMiniAvatarDate->adjustSize();
					contactsMiniAvatarDate->move(contactsMiniAvatarName->pos().x() + contactsMiniAvatarName->width() + 5, contactsMiniAvatarName->pos().y() + 4);

					for (int i = 0; i < unopenedLayout->count(); ++i) {
						QLayoutItem* item = unopenedLayout->itemAt(i);
						if (QPushButton* toolButton = qobject_cast<QPushButton*>(item->widget())) {
							toolButton->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
							)");
						}
					}
					for (int i = 0; i < openedLayout->count(); ++i) {
						QLayoutItem* item = openedLayout->itemAt(i);
						if (QPushButton* toolButton = qobject_cast<QPushButton*>(item->widget())) {
							toolButton->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
							)");
						}
					}
					userContactBtn->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
					)");
					contactBtn->setStyleSheet(R"(
					QPushButton {
					    background-color: #dde3e1;
					    text-align: left;
					    border: none;
					    padding-left: 70px;
					    font-size: 20px;
					    color: black;
					}
					)");

					for (int i = 0; i < openedLayout->count(); ++i) {
						QLabel* label = qobject_cast<QLabel*>(openedLayout->itemAt(i)->widget());
						if (label && label->objectName() == "openedEmpty") {
							openedLayout->removeWidget(label);
							label->deleteLater();
							scrollContentConst -= 62;
							scrollContent->setMinimumHeight(scrollContent->height() - 62);

							break;
						}
					}

					if (isUnopened) {
						if ( find(user->story.viewers.begin(), user->story.viewers.end(), currentUserID) == user->story.viewers.end()) {
							user->story.viewers.push_back(currentUserID);
							updateUsersToJson();
						}
					}

					});

			}
		}
	}
	if (totalNumOfUsersInScreen1 > 0) {
		QLayoutItem* lastItem = unopenedLayout->takeAt(unopenedLayout->count() - 1);

		if (lastItem) {
			QWidget* lastWidget = lastItem->widget();
			if (lastWidget) {
				lastWidget->hide();
				lastWidget->deleteLater();
			}
			delete lastItem;
		}
	}
	else {
		QLabel* L = new QLabel(contactsArea);
		L->setText("Empty");
		L->setStyleSheet("  background-color: transparent; border: none; font-size: 12px; color: rgba(0, 0, 0, 95);");
		L->setFixedHeight(62);
		L->setFixedWidth(380);
		L->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		L->setObjectName("unopenedEmpty");
		unopenedLayout->addWidget(L);
		scrollContentConst += 62;
	}
	scrollLayout->addLayout(unopenedLayout);

	// ----- OPENED STORIES -----
	QLabel* openedLabel = new QLabel("Opened Stories", scrollContent);
	openedLabel->setFont(titleFont28);
	if (users[currentUserID]->theme == 1) {
		openedLabel->setStyleSheet(R"(
		color: #31473a;
		margin-left: 6px;
	)");
	}
	else {
		openedLabel->setStyleSheet(R"(
		color: #222023;
		margin-left: 6px;
	)");
	}
	scrollLayout->addSpacing(10);
	scrollLayout->addWidget(openedLabel);
	scrollLayout->addSpacing(6);


	for (auto& [id, user] : users) {
		tmp_1 = false;
		tmp_2 = false;
		if (id == currentUserID) continue;

		auto otherContacts = user->getContacts();

		for (const auto& number : currentUserContacts) {
			if (number == users[id]->getNumber()) {
				tmp_1 = true;
				break;
			}
		}


		for (const auto& number : otherContacts) {
			if (number.first == users[currentUserID]->getNumber()) {
				tmp_2 = true;
				break;
			}
		}


		if (tmp_1 && tmp_2) {
			bool isOpened = find(user->story.viewers.begin(), user->story.viewers.end(), currentUserID) != user->story.viewers.end();


			if ((user->story.content != "" || user->story.photoPath != "") && user->profile.visibility && isOpened) {
				totalNumOfUsersInScreen2++;
				QPushButton* contactBtn = customized_Story(
					QString::fromStdString(user->Fname),
					nullptr,
					user->avatar != "" ? QString::fromStdString(user->avatar) : "icons/default.jpg");
				openedLayout->addWidget(contactBtn);
				QLabel* userContactBtnDev2 = new QLabel(contactsArea);
				userContactBtnDev2->setFixedHeight(1);
				userContactBtnDev2->setFixedWidth(380);
				userContactBtnDev2->setStyleSheet("background-color: rgba(0,0,0,15); margin-left: 60px;");
				openedLayout->addWidget(userContactBtnDev2);  // Centered horizontally
				QObject::connect(contactBtn, &QPushButton::clicked, [=]() {
					chatArea->hide();
					contactsChatArea->show();

					QPixmap originalPixmap(QString::fromStdString(user->story.photoPath));

					QPixmap stretchedPixmap = originalPixmap.scaled(
						contactsUploadedImageLabel->width(),
						contactsUploadedImageLabel->height(),
						Qt::IgnoreAspectRatio,
						Qt::SmoothTransformation
					);
					contactsUploadedImageLabel->setPixmap(stretchedPixmap);
					contactsUploadedImageLabel->show();

					QPixmap pixmap66(user->avatar != "" ? QString::fromStdString(user->avatar) : "icons/default.jpg");
					QPixmap roundedPixmap66(pixmap66.size());
					roundedPixmap66.fill(Qt::transparent);
					QPainter painter66(&roundedPixmap66);

					painter66.setRenderHint(QPainter::Antialiasing);
					QPainterPath path66;
					path66.addEllipse(0, 0, pixmap66.width(), pixmap66.height());
					painter66.setClipPath(path66);
					painter66.drawPixmap(0, 0, pixmap66);
					painter66.end();
					contactsMiniAvatar->setPixmap(roundedPixmap66.scaled(30, 30, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
					contactsBigAvatar->setPixmap(roundedPixmap66.scaled(200, 200, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

					contactsBigAvatarName->setText(QString::fromStdString(user->Fname) +
						(user->Lname.empty() ? "" : " " + QString::fromStdString(user->Lname)));
					contactsBigAvatarNumber->setText("+20" + QString::fromStdString(to_string(user->getNumber())));
					contactsBigAvatarAbout->setText(user->profile.about != "" ? QString::fromStdString(user->profile.about) : "Hey there! I'm using What's Wrong");

					QString timestamp = QString::fromStdString(user->story.publishedTime);
					QDateTime timestampTime = QDateTime::fromString(timestamp, "yyyy-MM-dd HH:mm:ss");
					QDateTime currentTime = QDateTime::currentDateTime();
					qint64 secondsElapsed = timestampTime.secsTo(currentTime);
					QString result;

					if (secondsElapsed < 60) {
						result = QString::number(secondsElapsed) + "s";
					}
					else if (secondsElapsed < 3600) {
						result = QString::number(secondsElapsed / 60) + "m";
					}
					else {
						result = QString::number(secondsElapsed / 3600) + "h";
					}
					contactsMiniAvatarName->setText(QString::fromStdString(user->Fname) +
						(user->Lname.empty() ? "" : " " + QString::fromStdString(user->Lname)));
					contactsMiniAvatarName->adjustSize();
					contactsMiniAvatarDate->setText(result);
					contactsMiniAvatarDate->adjustSize();
					contactsMiniAvatarDate->move(contactsMiniAvatarName->pos().x() + contactsMiniAvatarName->width() + 5, contactsMiniAvatarName->pos().y() + 4);



					if (user->story.content != "") {
						contactsLabel->setText(QString::fromStdString(user->story.content));
						contactsLabel->show();
					}
					else {
						contactsLabel->hide();
					}
					for (int i = 0; i < openedLayout->count(); ++i) {
						QLayoutItem* item = openedLayout->itemAt(i);
						if (QPushButton* toolButton = qobject_cast<QPushButton*>(item->widget())) {
							toolButton->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
							)");
						}
					}
					userContactBtn->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
					)");
					contactBtn->setStyleSheet(R"(
					QPushButton {
					    background-color: #dde3e1;
					    text-align: left;
					    border: none;
					    padding-left: 70px;
					    font-size: 20px;
					    color: black;
					}
					)");
					});

			}
		}

	}
	if (totalNumOfUsersInScreen2 > 0) {
		QLayoutItem* lastItem = openedLayout->takeAt(openedLayout->count() - 1);

		if (lastItem) {
			QWidget* lastWidget = lastItem->widget();
			if (lastWidget) {
				lastWidget->hide();       // Optional: Hide before deletion
				lastWidget->deleteLater(); // Safely delete the widget
			}
			delete lastItem; // Delete the layout item
		}
	}
	else {
		QLabel* L = new QLabel(contactsArea);
		L->setText("Empty");
		L->setStyleSheet("  background-color: transparent; border: none; font-size: 12px; color: rgba(0, 0, 0, 95);");
		L->setFixedHeight(62);
		L->setFixedWidth(380);
		L->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		L->setObjectName("openedEmpty");
		openedLayout->addWidget(L);
		scrollContentConst += 62;
	}
	scrollLayout->addLayout(openedLayout);

	// Stretch to push content to top
	scrollLayout->addStretch();

	scrollContent->setMinimumHeight(((totalNumOfUsersInScreen1 + totalNumOfUsersInScreen2) * 74) + scrollContentConst);  // Or dynamically calculate//////////////////////////////////////////////////////////////////////////////////////////////



	QWidget* topBar = new QWidget(container);
	topBar->setGeometry(61, 0, 380, 66);
	QWidget* topBarDevider = new QWidget(container);
	topBarDevider->setGeometry(441, 0, 1, 720);
	topBarDevider->setStyleSheet("background-color: #f9eded; border: none;");
	QWidget* leftBar = new QWidget(container);
	leftBar->setGeometry(0, 0, 60, 720);
	topBar->setStyleSheet("background-color: #eef4f2; border: none;");

	QWidget* leftBarDevider = new QWidget(container);
	leftBarDevider->setGeometry(60, 0, 1, 720);
	leftBarDevider->setStyleSheet("background-color: #f9eded; border: none;");

	QLabel* title = new QLabel("Stories", topBar);
	title->setFont(titleFont);

	title->adjustSize();
	title->move(14, 14);



	QString chatNameLabel = QString::fromStdString(users[currentUserID]->Fname);



	QFont AbdelazizstitleFont("Poppins", 16);
	QFont AbdelazizstitleFont2("Poppins", 19);
	QLabel* title_message = new QLabel("Add your Message", chatArea);
	title_message->setFont(AbdelazizstitleFont);
	title_message->adjustSize();
	title_message->setStyleSheet("color: #eef4f2;");
	title_message->move(41, 62 + 77);

	QLabel* noStoryError = new QLabel("You can't upload an empty story", chatArea);
	noStoryError->setFont(AbdelazizstitleFont);
	noStoryError->setGeometry(41, 585, 250, 30);
	noStoryError->setStyleSheet("color: #f44336; font-size: 15px; background: transparent; border:none;");
	noStoryError->hide();

	QLabel* doneStory = new QLabel("✓ Your story has been successfully updated", chatArea);
	doneStory->setFont(AbdelazizstitleFont);
	doneStory->setGeometry(41, 585, 400, 30);
	doneStory->setStyleSheet("color: green; font-size: 15px; background: transparent; border:none;");
	doneStory->hide();

	QTextEdit* storyField5 = new QTextEdit(chatArea);
	storyField5->setPlaceholderText("Write something...");
	storyField5->setGeometry(41, 99 + 77, 265, 129);
	//storyField5->setAttribute(Qt::WA_TransparentForMouseEvents);
	QObject::connect(storyField5, &QTextEdit::textChanged, [storyField5, noStoryError, currentStoryLabelTEST, doneStory]() {
		QString text = storyField5->toPlainText();
		currentStoryLabelTEST->setText(text);
		currentStoryLabelTEST->adjustSize();
		noStoryError->hide();
		doneStory->hide();

		// Check if width exceeds limit
		if (currentStoryLabelTEST->width() > 243) {
			// Find the maximum allowed characters that fit within 243px
			QFontMetrics fm(currentStoryLabelTEST->font());
			int maxChars = 0;
			QString testText;

			// Binary search to find optimal character count
			int low = 0;
			int high = text.length();
			while (low <= high) {
				int mid = (low + high) / 2;
				testText = text.left(mid);
				currentStoryLabelTEST->setText(testText);
				currentStoryLabelTEST->adjustSize();

				if (currentStoryLabelTEST->width() <= 243) {
					maxChars = mid;
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
			}

			// If we exceeded the limit, truncate
			if (maxChars < text.length()) {
				storyField5->blockSignals(true);
				storyField5->setPlainText(text.left(maxChars));

				// Move cursor to end
				QTextCursor cursor = storyField5->textCursor();
				cursor.movePosition(QTextCursor::End);
				storyField5->setTextCursor(cursor);

				storyField5->blockSignals(false);
			}
		}
		});

	storyField5->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	storyField5->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
	storyField5->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	storyField5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	if (users[currentUserID]->story.content != "") {
		storyField5->setText(QString::fromStdString(users[currentUserID]->story.content));
	}

	//////////////ABDELAZIZ////ABDELAZIZ////ABDELAZIZ////ABDELAZIZ////ABDELAZIZ//////////////No need for a button!
	QPushButton* sendButton = new QPushButton(chatArea);  //??!
	sendButton->setIcon(QIcon("icons/sending.png"));
	sendButton->setIconSize(QSize(13, 13));
	sendButton->setStyleSheet("border: none; background: transparent;");
	sendButton->setGeometry(storyField5->x() + storyField5->width() - 32, storyField5->y() + storyField5->height() - 32, 30, 30);


	QLabel* title_image = new QLabel("Upload a photo", chatArea);
	title_image->setFont(AbdelazizstitleFont);
	title_image->adjustSize();
	title_image->setStyleSheet("color: #eef4f2;");
	title_image->move(41, 293 + 77);

	QPushButton* avatarButton = new QPushButton(chatArea);
	avatarButton->setGeometry(41, 330 + 77, 161, 129);
	avatarButton->setText("+");
	avatarButton->setCursor(Qt::PointingHandCursor);


	QLabel* subsub_title = new QLabel("Share what's on your mind", chatArea);
	subsub_title->setFont(AbdelazizstitleFont2);
	subsub_title->adjustSize();
	subsub_title->setStyleSheet("color:  #eef4f2;");
	subsub_title->move(41, 62);

	QFont ButtonFont("Poppins", 15);


	// home Button
	QToolButton* home_Button = new QToolButton(leftBar);
	home_Button->setIcon(QIcon("icons/home.png"));
	home_Button->setGeometry(-10, 0, 80, 66);
	home_Button->setIconSize(QSize(28, 28)); // match the button size
	home_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	home_Button->setStyleSheet(R"(
    QToolButton {
        color: white;
        background: none;
        border: none;
    }
	)");

	// story Button
	QToolButton* story_Button = new QToolButton(leftBar);
	story_Button->setIcon(QIcon("icons/story.png"));
	story_Button->setIconSize(QSize(28, 28));
	story_Button->setGeometry(-10, 66, 80, 66);
	story_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	story_Button->setStyleSheet(R"(
    QToolButton {
        border: none;
        background-color: #2a272a;
    }
    )");

	// group Button
	QToolButton* group_Button = new QToolButton(leftBar);
	group_Button->setIcon(QIcon("icons/group-chat.png"));
	group_Button->setIconSize(QSize(30, 30));
	group_Button->setGeometry(-10, 132, 80, 66);
	group_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	group_Button->setStyleSheet(R"(
    QToolButton {
        background: none;
        border: none;
    }
    )");

	// Settings Button
	QToolButton* settings_Button = new QToolButton(leftBar);
	settings_Button->setIcon(QIcon("icons/setting.png"));
	settings_Button->setIconSize(QSize(28, 28));
	settings_Button->setGeometry(-10, 654, 80, 66);
	settings_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	settings_Button->setStyleSheet(R"(
    QToolButton {
        background: none;
        border: none;
    }
    )");



	QToolButton* submit = new QToolButton(chatArea);
	submit->setGeometry(41, 628, 161, 50);
	submit->setStyleSheet(
		"QToolButton {"
		"   color: black;"
		"   background-color: #d4d9d7;"
		"   border-radius: 10px;"
		"	border: none;"
		"}"
		"QToolButton:hover {"
		"   background-color: #e8ecea;"
		"}"
	);
	submit->setFont(ButtonFont);
	submit->setCursor(Qt::PointingHandCursor);
	if (users[currentUserID]->story.content != "" || users[currentUserID]->story.photoPath != "") {
		submit->setText("Update");
	}
	else {
		submit->setText("Submit");
		QLabel* StoryAvatar = userContactBtn->findChild<QLabel*>("storyAvatar");
		QString storyAvatarPath = users[currentUserID]->avatar != "" ? QString::fromStdString(users[currentUserID]->avatar) : "icons/default.jpg";
		if (!storyAvatarPath.isEmpty()) {
			QPixmap pixmap(storyAvatarPath);
			QPixmap scaledPixmap = pixmap.scaled(42, 42, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

			QPixmap finalPixmap(42, 42);
			finalPixmap.fill(Qt::transparent);

			QPainter painter(&finalPixmap);
			painter.setRenderHint(QPainter::Antialiasing);

			QPainterPath path;
			path.addEllipse(0, 0, 42, 42);
			painter.setClipPath(path);

			painter.drawPixmap(0, 0, scaledPixmap);

			painter.setClipping(false);
			QPen pen(Qt::transparent);
			pen.setWidth(0);
			painter.setPen(pen);
			painter.setBrush(Qt::NoBrush);
			painter.drawEllipse(1, 1, 40, 40);
			painter.end();
			StoryAvatar->setPixmap(finalPixmap);
		}
	}

	QToolButton* delete_Story = new QToolButton(chatArea);
	delete_Story->setText("Delete Story");
	delete_Story->setGeometry(215, 628, 161, 50);
	delete_Story->setStyleSheet(
		"QToolButton {"
		"   color: #d4d9d7;"
		"   background-color: #f44336;"
		"   border-radius: 10px;"
		"	border: none;"
		"}"
		"QToolButton:hover {"
		"   background-color: #e53935;"
		"}"
	);
	delete_Story->setFont(ButtonFont);
	delete_Story->setCursor(Qt::PointingHandCursor);
	if (users[currentUserID]->story.content != "" || users[currentUserID]->story.photoPath != "") {
		delete_Story->show();
	}
	else {
		delete_Story->hide();
	}

	QObject::connect(delete_Story, &QToolButton::clicked, [=]() {
		// Hide all error messages first
		noStoryError->hide();
		doneStory->hide();

		delete_Story->hide();
		submit->setText("Submit"); //if story doesn't have errors


		currentStoryLabel->clear();
		currentStoryLabel->hide();
		uploadedImageLabel->clear();
		uploadedImageLabel->hide();
		storyField5->setText("");

		QLabel* StoryAvatar = userContactBtn->findChild<QLabel*>("storyAvatar");
		QString storyAvatarPath = QString::fromStdString(users[currentUserID]->avatar);
		if (!storyAvatarPath.isEmpty()) {
			QPixmap pixmap(storyAvatarPath);
			QPixmap scaledPixmap = pixmap.scaled(42, 42, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

			QPixmap finalPixmap(42, 42);
			finalPixmap.fill(Qt::transparent);

			QPainter painter(&finalPixmap);
			painter.setRenderHint(QPainter::Antialiasing);

			QPainterPath path;
			path.addEllipse(0, 0, 42, 42);
			painter.setClipPath(path);

			painter.drawPixmap(0, 0, scaledPixmap);

			painter.setClipping(false);
			QPen pen(Qt::transparent);
			pen.setWidth(0);
			painter.setPen(pen);
			painter.setBrush(Qt::NoBrush);
			painter.drawEllipse(1, 1, 40, 40);
			painter.end();
			StoryAvatar->setPixmap(finalPixmap);
		}


		// Clear text content if exists
		if (!users[currentUserID]->story.content.empty()) {
			users[currentUserID]->story.content = "";
			currentStoryLabel->hide();
			currentStoryLabel->clear();
		}

		// Clear photo if exists
		if (!users[currentUserID]->story.photoPath.empty()) {
			users[currentUserID]->story.photoPath = "";
			uploadedImageLabel->hide();
			uploadedImageLabel->clear();
		}

		// Clear any viewers list
		users[currentUserID]->story.viewers.clear();
		users[currentUserID]->story.publishedTime.clear();

		// Save changes to database
		updateUsersToJson();

		});

	QObject::connect(userContactBtn, &QPushButton::clicked, [=]() {
		noStoryError->hide();
		doneStory->hide();
		chatArea->show();
		contactsChatArea->hide();
		userContactBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #dde3e1;
            text-align: left;
            border: none;
            padding-left: 70px;
            font-size: 20px;
            color: black;
        }
		)");

		for (int i = 0; i < openedLayout->count(); ++i) {
			QLayoutItem* item = openedLayout->itemAt(i);
			if (QPushButton* toolButton = qobject_cast<QPushButton*>(item->widget())) {
				toolButton->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
							)");
			}
		}
		for (int i = 0; i < unopenedLayout->count(); ++i) {
			QLayoutItem* item = unopenedLayout->itemAt(i);
			if (QPushButton* toolButton = qobject_cast<QPushButton*>(item->widget())) {
				toolButton->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
							)");
			}
		}
		});

	QObject::connect(avatarButton, &QPushButton::clicked, [=]() {
		noStoryError->hide();
		doneStory->hide();


		uploadedImageLabel->clear();

		// Open file dialog to select an image
		QString fileName = QFileDialog::getOpenFileName(contactsArea,
			"Select Story Picture",
			"",
			"Images (*.png *.jpg *.jpeg *.bmp)");

		if (!fileName.isEmpty()) {
			// Save the selected file path to the user's story
			users[currentUserID]->story.photoPath = fileName.toStdString();

			QPixmap originalPixmap(QString::fromStdString(users[currentUserID]->story.photoPath));
			if (originalPixmap.isNull()) {
				qWarning() << "Failed to load image";
				return;
			}

			QPixmap stretchedPixmap = originalPixmap.scaled(
				uploadedImageLabel->width(),
				uploadedImageLabel->height(),
				Qt::IgnoreAspectRatio,  // Allows stretching
				Qt::SmoothTransformation
			);

			uploadedImageLabel->setPixmap(stretchedPixmap);
			uploadedImageLabel->setStyleSheet("background: transparent;");
			uploadedImageLabel->show();
		}
		});



	QString publishedTimeStr = QString::fromStdString(users[currentUserID]->story.publishedTime);
	if (!publishedTimeStr.isEmpty()) {
		QDateTime publishedTime = QDateTime::fromString(publishedTimeStr, "yyyy-MM-dd hh:mm:ss");
		QDateTime currentTime = QDateTime::currentDateTime();
		if (publishedTime.isValid() && publishedTime.secsTo(currentTime) > 86400) { // 86400 seconds = 24 hours
			// Story is older than 24 hours — delete it
			users[currentUserID]->story.content.clear();
			users[currentUserID]->story.photoPath.clear();
			users[currentUserID]->story.publishedTime.clear();
			users[currentUserID]->story.viewers.clear();
			currentStoryLabel->clear();
			currentStoryLabel->hide();
			uploadedImageLabel->clear();
			uploadedImageLabel->hide();
			storyField5->setText("");

			updateUsersToJson();

			return;
		}
	}

	QObject::connect(submit, &QToolButton::clicked, [=]() {

		bool hasText;
		bool hasPhoto = !users[currentUserID]->story.photoPath.empty();

		if (storyField5->toPlainText() == "") {
			if (currentStoryLabel->text().toStdString() == "") {
				currentStoryLabel->hide();
			}
			hasText = false;
		}
		else {
			currentStoryLabel->setText(storyField5->toPlainText());
			currentStoryLabel->show();
			hasText = true;
		}


		// Validate input
		if (!hasText && !hasPhoto) {
			noStoryError->show();
			return;
		}
		noStoryError->hide();
		delete_Story->show(); //if story doesn't have errors
		uploadedImageLabel->show();
		if (submit->text() == "Update") {
			doneStory->show();
		}
		submit->setText("Update"); //if story doesn't have errors
		QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

		if (hasText) {
			users[currentUserID]->story.content = currentStoryLabel->text().toStdString();
			currentStoryLabel->show();
		}

		if (hasPhoto) {
			QString photoPath = QString::fromStdString(users[currentUserID]->story.photoPath);
		}

		users[currentUserID]->story.publishedTime = timestamp.toStdString();
		updateUsersToJson();

		});


	if (users[currentUserID]->theme == 1) {

		leftBar->setStyleSheet("background-color: #31473a; border: none;");
		title->setStyleSheet("color: #31473a; background: transparent;");
		story_Button->setStyleSheet(R"(
    QToolButton {
        border: none;
        background-color: #2f3f36;
    }
    )");

		storyField5->setStyleSheet(R"(
		background-color: #202f26;
		color: white;
		border-radius: 10px;
		padding: 8px;
		font-size: 14px;
		)");
		chatArea->setStyleSheet(R"(
    QWidget {

        background-color: #31473a;
        border: none;
    }
)");
		contactsChatArea->setStyleSheet(R"(
    QWidget {

        background-color: #31473a;
        border: none;
    }
)");
		avatarButton->setStyleSheet("padding-top: -12px; background-color: #202f26; color: #6d6d6e; border-radius: 10px; font-size: 55px;");

	}
	else {
		avatarButton->setStyleSheet("padding-top: -12px; background-color: #323133; color: #6d6d6e; border-radius: 10px; font-size: 55px;");

		leftBar->setStyleSheet("background-color: #222023; border: none;");
		story_Button->setStyleSheet(R"(
    QToolButton {
        border: none;
        background-color: #2a272a;
    }
    )");

		storyField5->setStyleSheet(R"(
		background-color: #323133;
		color: white;
		border-radius: 10px;
		padding: 8px;
		font-size: 14px;
		)");
		/*	delete_Story->setStyleSheet(R"(
		background-color: #222023;
		border: none;
		border-radius: 15px;
		color: #e4d9d7;
		)");
		*/

		leftBar->setStyleSheet("background-color: #222023; border: none;");
		title->setStyleSheet("color: #222023; background: transparent;");

		chatArea->setStyleSheet(R"(
    QWidget {

        background-color: #222023;
        border: none;
    }
)");
		contactsChatArea->setStyleSheet(R"(
    QWidget {

        background-color: #222023;
        border: none;
    }
)");


	}

	QObject::connect(home_Button, &QPushButton::clicked, [=]() {
		container->hide();
		totalNumOfUsersInScreen1 = 0;
		totalNumOfUsersInScreen2 = 0;
		project_Gui::chat_Screen(window);
		});

	QObject::connect(settings_Button, &QPushButton::clicked, [=]() {
		container->hide();
		totalNumOfUsersInScreen1 = 0;
		totalNumOfUsersInScreen2 = 0;
		project_Gui::setting_Screen(window);
		});
	QObject::connect(group_Button, &QPushButton::clicked, [=]() {
		container->hide();
		totalNumOfUsersInScreen1 = 0;
		totalNumOfUsersInScreen2 = 0;
		project_Gui::group_Screen(window);
		});

	container->show();
}

void project_Gui::setting_Screen(QWidget* window) {
	QWidget* container = new QWidget(window);
	container->setGeometry(0, 0, 1280, 720);


	//contacts room
	QWidget* contactsArea = new QWidget(container);
	contactsArea->setGeometry(61, 66, 380, 720);
	contactsArea->setStyleSheet("border: none; background-color: #eef4f2;");
	//chats room
	QWidget* chatArea = new QWidget(container);
	chatArea->setGeometry(442, 0, 838, 720);
	chatArea->setStyleSheet(R"(
    QWidget {
        background-color: transparent;
        border: none;
    }
	)");

	QWidget* bar = new QWidget(chatArea);
	bar->setGeometry(0, 0, 860, 66);

	/////////////////////////////////////////////////////////////////

	QLabel* HidechatArea = new QLabel(container);
	HidechatArea->setGeometry(442, 0, 838, 720);
	if (users[currentUserID]->theme == 1) {
		HidechatArea->setPixmap(QPixmap("icons/chatImg2.png"));
	}
	else {
		HidechatArea->setPixmap(QPixmap("icons/chatImg.png"));
	}
	HidechatArea->setScaledContents(true);
	HidechatArea->setStyleSheet("border: none; background-color: #222023;");
	QFont ButtonFont("Poppins", 10);


	QWidget* topBar = new QWidget(container);
	topBar->setGeometry(61, 0, 380, 66);
	topBar->setStyleSheet("background-color: #eef4f2; border: none;");
	QWidget* topBarDevider = new QWidget(container);
	topBarDevider->setGeometry(441, 0, 1, 720);
	topBarDevider->setStyleSheet("background-color: #f9eded; border: none;");
	QWidget* leftBar = new QWidget(container);
	leftBar->setGeometry(0, 0, 60, 720);

	QWidget* leftBarDevider = new QWidget(container);
	leftBarDevider->setGeometry(60, 0, 1, 720);
	leftBarDevider->setStyleSheet("background-color: #f9eded; border: none;");

	QLabel* title = new QLabel("Settings", topBar);
	QFont titleFont("Poppins", 21, QFont::Bold);
	title->setFont(titleFont);

	title->adjustSize();
	title->move(14, 14);

	// avatar
	QPushButton* avatarButton = new QPushButton(container);
	avatarButton->setGeometry(165.5, 80.5, 174, 174);
	avatarButton->setCursor(Qt::PointingHandCursor);
	avatarButton->setStyleSheet("border: none; border-radius: 85px;");
	QPixmap pixmap(QString::fromStdString(users[currentUserID]->avatar));
	pixmap = pixmap.scaled(174, 174, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
	QPixmap maskedPixmap(174, 174);
	maskedPixmap.fill(Qt::transparent);

	QPainter painter(&maskedPixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addEllipse(0, 0, 174, 174);
	painter.setClipPath(path);
	painter.drawPixmap(0, 0, pixmap);
	painter.end();
	avatarButton->setIcon(QIcon(maskedPixmap));
	avatarButton->setIconSize(QSize(174, 174));

	QLabel* photoLabel = new QLabel(container);
	QPixmap photo("icons/change_pic.png");
	photoLabel->setPixmap(photo);
	photoLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
	photoLabel->adjustSize();

	QObject::connect(avatarButton, &QPushButton::clicked, [=]() {
		QString fileName = QFileDialog::getOpenFileName(contactsArea,
			"Select Profile Picture",
			"",
			"Images (*.png *.jpg *.jpeg *.bmp)");
		if (!fileName.isEmpty()) {
			QPixmap newPixmap(fileName);
			newPixmap = newPixmap.scaled(174, 174, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

			QPixmap newMaskedPixmap(174, 174);
			newMaskedPixmap.fill(Qt::transparent);

			QPainter newPainter(&newMaskedPixmap);
			newPainter.setRenderHint(QPainter::Antialiasing);
			QPainterPath newPath;
			newPath.addEllipse(0, 0, 174, 174);
			newPainter.setClipPath(newPath);
			newPainter.drawPixmap(0, 0, newPixmap);
			newPainter.end();

			avatarButton->setIcon(QIcon(newMaskedPixmap));

			users[currentUserID]->avatar = fileName.toStdString();
			updateUsersToJson();
		}
		});

	// home Button
	QToolButton* home_Button = new QToolButton(leftBar);
	home_Button->setIcon(QIcon("icons/home.png"));
	home_Button->setGeometry(-10, 0, 80, 66);
	home_Button->setIconSize(QSize(28, 28)); // match the button size
	home_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	home_Button->setStyleSheet(R"(
	QToolButton {
		background: none;
		border: none;
	}
	)");

	// story Button
	QToolButton* story_Button = new QToolButton(leftBar);
	story_Button->setIcon(QIcon("icons/story.png"));
	story_Button->setIconSize(QSize(28, 28));
	story_Button->setGeometry(-10, 66, 80, 66);
	story_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	story_Button->setStyleSheet(R"(
    QToolButton {
        background: none;
        border: none;
    }
    )");

	// group Button
	QToolButton* group_Button = new QToolButton(leftBar);
	group_Button->setIcon(QIcon("icons/group-chat.png"));
	group_Button->setIconSize(QSize(30, 30));
	group_Button->setGeometry(-10, 132, 80, 66);
	group_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	group_Button->setStyleSheet(R"(
	QToolButton {
		background: none;
		border: none;
	}
    )");

	// Settings Button
	QToolButton* settings_Button = new QToolButton(leftBar);
	settings_Button->setIcon(QIcon("icons/setting.png"));
	settings_Button->setIconSize(QSize(28, 28));
	settings_Button->setGeometry(-10, 654, 80, 66);
	settings_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);


	QFont settingFont("Poppins", 12);
	QLabel* yourName = new QLabel("Your name", contactsArea);
	yourName->setGeometry(14, 200, 100, 60);
	yourName->setFont(settingFont);

	yourName->adjustSize();


	QLineEdit* nameField = new QLineEdit(contactsArea);
	nameField->setPlaceholderText("First name");
	nameField->setText(QString::fromStdString(users[currentUserID]->Fname));
	nameField->setGeometry(14, 225, 170, 26);
	nameField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 15px;
        border: none;
        border-radius: 9px;
        font-size: 14px;
		background-color: #d4d9d7;
		color: black;
    }
    )");
	QLineEdit* nameField2 = new QLineEdit(contactsArea);
	nameField2->setPlaceholderText("Lats name");
	nameField2->setText(QString::fromStdString(users[currentUserID]->Lname));
	nameField2->setGeometry(192, 225, 170, 26);
	nameField2->setStyleSheet(R"(
    QLineEdit {
        padding-left: 15px;
        border: none;
        border-radius: 9px;
        font-size: 14px;
		background-color: #d4d9d7;
		color: black;
    }
    )");

	QLabel* yourPass = new QLabel("Password", contactsArea);
	yourPass->setGeometry(14, 270, 100, 60);
	yourPass->setFont(settingFont);
	yourPass->adjustSize();

	// Add the password field
	QLineEdit* passField = new QLineEdit(contactsArea);
	passField->setPlaceholderText("Make it strong - like your coffee!");
	passField->setText(QString::fromStdString(users[currentUserID]->getPassword()));
	passField->setGeometry(14, 295, 348, 26);
	passField->setEchoMode(QLineEdit::Password);
	passField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 15px;
        padding-right: 30px;
        border: none;
        border-radius: 9px;
        font-size: 14px;
        background-color: #d4d9d7;
		color: black;
    }
	)");

	// Add eye toggle button inside the QLineEdit
	QToolButton* toggleButton = new QToolButton(passField);
	toggleButton->setIcon(QIcon("icons/eye.png"));
	toggleButton->setCursor(Qt::PointingHandCursor);
	toggleButton->setStyleSheet("QToolButton { border: none; padding: 0px; background-color: transparent; }");
	toggleButton->setFixedSize(20, 20);
	toggleButton->move(passField->width() - toggleButton->width() - 5, (passField->height() - toggleButton->height()) / 2);
	toggleButton->raise();
	toggleButton->show();

	// Handle click to toggle password visibility
	QObject::connect(toggleButton, &QToolButton::clicked, [=]() {
		if (passField->echoMode() == QLineEdit::Password) {
			passField->setEchoMode(QLineEdit::Normal);
			toggleButton->setIcon(QIcon("icons/hidden.png"));
		}
		else {
			passField->setEchoMode(QLineEdit::Password);
			toggleButton->setIcon(QIcon("icons/eye.png"));
		}
		});

	QLabel* yourabout = new QLabel("About", contactsArea);
	yourabout->setGeometry(14, 335, 100, 60);
	yourabout->setFont(settingFont);
	yourabout->adjustSize();

	QLineEdit* aboutField = new QLineEdit(contactsArea);
	aboutField->setPlaceholderText("Tell us something cool about yourself!");
	aboutField->setText(QString::fromStdString(users[currentUserID]->profile.about));
	aboutField->setGeometry(14, 360, 348, 26);
	aboutField->setStyleSheet(R"(
    QLineEdit {
        padding-left: 15px;
        border: none;
        border-radius: 9px;
        font-size: 14px;
		background-color: #d4d9d7;
		color: black;
    }
    )");


	QAction* toggleAction2 = new QAction(QIcon("icons/pen.png"), "");
	nameField->addAction(toggleAction2, QLineEdit::TrailingPosition);
	nameField2->addAction(toggleAction2, QLineEdit::TrailingPosition);
	aboutField->addAction(toggleAction2, QLineEdit::TrailingPosition);

	QLabel* Theme = new QLabel("Theme", contactsArea);
	Theme->setGeometry(14, 405, 100, 60);
	Theme->setFont(settingFont);

	Theme->adjustSize();

	// Create a container widget
	QWidget* toggleWidget1 = new QWidget(contactsArea);
	toggleWidget1->setGeometry(14, 430, 348, 26); // Adjust size
	toggleWidget1->setCursor(Qt::PointingHandCursor);

	// Create ON button
	QPushButton* darkButton = new QPushButton("Dark", toggleWidget1);
	darkButton->setGeometry(0, 0, toggleWidget1->width() / 2, 26); // Half width
	darkButton->setCheckable(true);
	darkButton->setChecked(true); // ON by default

	// Create OFF button
	QPushButton* lightButton = new QPushButton("Light", toggleWidget1);
	lightButton->setGeometry(toggleWidget1->width() / 2, 0, toggleWidget1->width() / 2, 26);
	lightButton->setCheckable(true);



	QLabel* ppv = new QLabel("Account privacy", contactsArea);
	ppv->setGeometry(14, 470, 100, 60);
	ppv->setFont(settingFont);

	ppv->adjustSize();

	// Create a container widget
	QWidget* toggleWidget = new QWidget(contactsArea);
	toggleWidget->setGeometry(14, 495, 348, 26); // Adjust size
	toggleWidget->setCursor(Qt::PointingHandCursor);

	// Create ON button
	QPushButton* privacyButtonOn = new QPushButton("Public", toggleWidget);
	privacyButtonOn->setGeometry(0, 0, toggleWidget->width() / 2, 26); // Half width
	privacyButtonOn->setCheckable(true);

	// Create OFF button
	QPushButton* privacyButtonOff = new QPushButton("Private", toggleWidget);
	privacyButtonOff->setGeometry(toggleWidget->width() / 2, 0, toggleWidget->width() / 2, 26);
	privacyButtonOff->setCheckable(true);

	QFont settingFont2("Poppins", 10);

	QPushButton* saveBtn = new QPushButton("Save", contactsArea);
	saveBtn->setGeometry(14, 560, 348, 26); //560
	saveBtn->setCursor(Qt::PointingHandCursor);


	QPushButton* logoutBtn = new QPushButton("Logout", contactsArea);
	logoutBtn->setGeometry(14, 606, 348, 26);
	logoutBtn->setCursor(Qt::PointingHandCursor);
	logoutBtn->setStyleSheet(R"(
    QPushButton {
        border: none;
        border-radius: 9px;
        font-size: 14px;
		color: #d4d9d7;
		background-color: #f44336;
    }
	QPushButton:hover {
        background-color: #e53935;
    }
    )");

	QWidget* popUpContainer = new QWidget(container);
	popUpContainer->setGeometry(0, 0, 1280, 720);
	popUpContainer->setStyleSheet("background-color: rgba(0,0,0,200);");
	popUpContainer->hide();

	QWidget* popUpContacts = new QWidget(popUpContainer);
	popUpContacts->setGeometry(497.5, 290, 285, 138);
	popUpContacts->setStyleSheet("background-color: #eef4f2; border-radius: 7px;");

	QToolButton* popAddButton = new QToolButton(popUpContacts);
	popAddButton->setText("No");
	popAddButton->setGeometry(220, 100, 50, 25);
	popAddButton->setCursor(Qt::PointingHandCursor);
	QString popBgColor = (users[currentUserID]->theme == 1) ? "#31473a" : "#222023";

	popAddButton->setStyleSheet(QString(R"(
    background-color: %1;
    border: none;
    border-radius: 7px;
    color: #e4d9d7;
	)").arg(popBgColor));

	popAddButton->setFont(ButtonFont);
	
	QToolButton* popCloseButton = new QToolButton(popUpContacts);
	popCloseButton->setText("Yes");
	popCloseButton->setGeometry(15, 100, 50, 25);
	popCloseButton->setCursor(Qt::PointingHandCursor);
	popCloseButton->setStyleSheet(R"(
		background-color: #d4d9d7;
		border: none;
		border-radius: 7px;
		color: #222023;
	)");
	popCloseButton->setFont(ButtonFont);

	QLabel* logOutLabel0 = new QLabel("Confirm Logout", popUpContacts);
	logOutLabel0->setGeometry(15, 15, 100, 30);
	logOutLabel0->setFont(settingFont);
	logOutLabel0 ->setStyleSheet("color: black;");
	logOutLabel0->adjustSize();

	QLabel* logOutLabel = new QLabel("Are you sure you want to log out? ⚠️", popUpContacts);
	logOutLabel->setGeometry(15, 55, 100, 30);
	logOutLabel->setFont(settingFont2);
	logOutLabel->setStyleSheet("color: black;");
	logOutLabel->adjustSize();

	saveBtn->setFont(ButtonFont);
	logoutBtn->setFont(ButtonFont);

	QLabel* emptyNameLabel = new QLabel("Name field cannot be empty", contactsArea);
	emptyNameLabel->setGeometry(0, 538, contactsArea->width(), 20);
	emptyNameLabel->setAlignment(Qt::AlignHCenter);
	emptyNameLabel->setStyleSheet("color: red; font-size: 13px; background-color: transparent;");
	emptyNameLabel->setFont(settingFont2);
	emptyNameLabel->hide();

	QLabel* emptyPasswordLabel = new QLabel("Password cannot be empty", contactsArea);
	emptyPasswordLabel->setGeometry(0, 538, contactsArea->width(), 20);
	emptyPasswordLabel->setAlignment(Qt::AlignHCenter);
	emptyPasswordLabel->setStyleSheet("color: red; font-size: 13px; background-color: transparent;");
	emptyPasswordLabel->setFont(settingFont2);
	emptyPasswordLabel->hide();

	QLabel* wrongPasswordLabel = new QLabel("Password must be at least 6 characters long", contactsArea);
	wrongPasswordLabel->setGeometry(0, 538, contactsArea->width(), 20);
	wrongPasswordLabel->setAlignment(Qt::AlignHCenter);
	wrongPasswordLabel->setStyleSheet("color: red; font-size: 13px; background-color: transparent;");
	wrongPasswordLabel->setFont(settingFont2);
	wrongPasswordLabel->hide();

	QLabel* doneLabel = new QLabel("✓ Your information has been changed", contactsArea);
	doneLabel->setGeometry(0, 538, contactsArea->width(), 20);
	doneLabel->setAlignment(Qt::AlignHCenter);
	doneLabel->setStyleSheet("color: green; font-size: 13px; background-color: transparent;");
	doneLabel->setFont(settingFont2);
	doneLabel->hide();

	QObject::connect(nameField, &QLineEdit::editingFinished, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();
		});
	QObject::connect(nameField2, &QLineEdit::editingFinished, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();
		});
	QObject::connect(passField, &QLineEdit::editingFinished, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();
		});
	QObject::connect(aboutField, &QLineEdit::editingFinished, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();
		});

	QObject::connect(saveBtn, &QPushButton::clicked, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();

		QString name1 = nameField->text();
		QString name2 = nameField2->text();
		QString pass = passField->text();
		QString about = aboutField->text();

		if (name1.isEmpty()) {
			emptyNameLabel->show();
		}
		else if (pass.isEmpty()) {
			emptyPasswordLabel->show();
		}
		else if (pass.length() < 6) {
			wrongPasswordLabel->show();
		}
		else if (!name1.isEmpty() && pass.length() >= 6) {
			doneLabel->show();
			users[currentUserID]->Fname = name1.toStdString();
			users[currentUserID]->Lname = name2.toStdString();
			users[currentUserID]->setPassword(pass.toStdString());
			users[currentUserID]->profile.about = about.toStdString();
			updateUsersToJson();
		}
		});


	QObject::connect(logoutBtn, &QPushButton::clicked, [=]() {
		popUpContainer->show();
		});
	QObject::connect(popAddButton, &QPushButton::clicked, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();
		popUpContainer->hide();
		});
	QObject::connect(popCloseButton, &QPushButton::clicked, [=]() {
		users[currentUserID]->selected = false;
		updateUsersToJson();
		currentUserID = 0;
		container->hide();
		project_Gui::login_Screen(window);
		});


	// Styles
	QString activeStyle = R"(
    QPushButton {
        background-color: #222023;
        color: white;
        border: none;
        border-top-left-radius: 9px;
        border-bottom-left-radius: 9px;
        font-weight: bold;
    }
	QPushButton:hover {
		background-color: #2e2c2f;
	}
	)";

	QString inactiveStyle = R"(
    QPushButton {
        background-color: #d4d9d7;
        color: black;
        border: none;
        border-top-right-radius: 9px;
        border-bottom-right-radius: 9px;
        font-weight: normal;
    }
	QPushButton:hover {
		background-color: #e0e0e0;
	}
	)";

	//Profile Picture visibility
	// Connect them to toggle


	if (users[currentUserID]->profile.visibility == 1) {
		privacyButtonOn->setChecked(true);
		privacyButtonOff->setChecked(false);

		QString activeLeftStyle = activeStyle;
		QString inactiveRightStyle = inactiveStyle;
		inactiveRightStyle.replace("border-top-left-radius", "border-top-right-radius");
		inactiveRightStyle.replace("border-bottom-left-radius", "border-bottom-right-radius");

		privacyButtonOn->setStyleSheet(activeLeftStyle);
		privacyButtonOff->setStyleSheet(inactiveRightStyle);
	}
	else {
		privacyButtonOn->setChecked(false);
		privacyButtonOff->setChecked(true);

		QString activeRightStyle = activeStyle;
		activeRightStyle.replace("border-top-left-radius", "border-top-right-radius");
		activeRightStyle.replace("border-bottom-left-radius", "border-bottom-right-radius");

		QString inactiveLeftStyle = inactiveStyle;
		inactiveLeftStyle.replace("border-top-right-radius", "border-top-left-radius");
		inactiveLeftStyle.replace("border-bottom-right-radius", "border-bottom-left-radius");

		privacyButtonOff->setStyleSheet(activeRightStyle);
		privacyButtonOn->setStyleSheet(inactiveLeftStyle);
	}


	// Ensure correct button state on startup
	if (users[currentUserID]->theme == 1) { // Light mode
		lightButton->setChecked(true);
		darkButton->setChecked(false);

		// Apply styles for light mode
		lightButton->setStyleSheet(R"(
        QPushButton {
            background-color: #31473a;
            color: white;
            border: none;
            border-top-right-radius: 9px;
            border-bottom-right-radius: 9px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #3a5947;
        }
    )");

		darkButton->setStyleSheet(R"(
        QPushButton {
            background-color: #d4d9d7;
            color: black;
            border: none;
            border-top-left-radius: 9px;
            border-bottom-left-radius: 9px;
            font-weight: normal;
        }
        QPushButton:hover {
            background-color: #e0e0e0;
        }
    )");

		// Set the rest of the UI for light mode
		title->setStyleSheet("color: #30473a; background: transparent;");
		leftBar->setStyleSheet("background-color: #30473a; border: none;");
		bar->setStyleSheet("border: none; background-color: #30473a;");
		settings_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
            background-color: #2f3f36;
        }
    )");
		yourName->setStyleSheet("color: #30473a; background: transparent;");
		yourPass->setStyleSheet("color: #30473a; background: transparent;");
		yourabout->setStyleSheet("color: #30473a; background: transparent;");
		Theme->setStyleSheet("color: #30473a; background: transparent;");
		ppv->setStyleSheet("color: #30473a; background: transparent;");
		saveBtn->setStyleSheet(R"(
	QPushButton {
		border: none;
		border-radius: 9px;
		font-size: 14px;
		color: #d4d9d7;
		background-color: #31473a;
	}
	QPushButton:hover {
		background-color: #3a5947;
	}
	)");

		activeStyle = R"(
			QPushButton {
				background-color: #31473a;
				color: white;
				border: none;
				border-top-left-radius: 9px;
				border-bottom-left-radius: 9px;
				font-weight: bold;
			}
			QPushButton:hover {
				background-color: #3a5947;
			}
		)";
		inactiveStyle = R"(
			QPushButton {
				background-color: #d4d9d7;
				color: black;
				border: none;
				border-top-right-radius: 9px;
				border-bottom-right-radius: 9px;
				font-weight: normal;
			}
			QPushButton:hover {
				background-color: #e0e0e0;
			}
		)";


		privacyButtonOn->setStyleSheet(activeStyle);
		privacyButtonOff->setStyleSheet(inactiveStyle);
	}
	else {

		saveBtn->setStyleSheet(R"(
	QPushButton {
		border: none;
		border-radius: 9px;
		font-size: 14px;
		color: #d4d9d7;
		background-color: #222023;
	}
	QPushButton:hover {
		background-color: #2e2c2f;
	}
	)");
		darkButton->setChecked(true);
		lightButton->setChecked(false);

		// Apply styles for dark mode
		darkButton->setStyleSheet(R"(
        QPushButton {
            background-color: #222023;
            color: white;
            border: none;
            border-top-left-radius: 9px;
            border-bottom-left-radius: 9px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #2e2c2f;
        }
    )");

		lightButton->setStyleSheet(R"(
        QPushButton {
            background-color: #d4d9d7;
            color: black;
            border: none;
            border-top-right-radius: 9px;
            border-bottom-right-radius: 9px;
            font-weight: normal;
        }
        QPushButton:hover {
            background-color: #e0e0e0;
        }
    )");

		// Set the rest of the UI for dark mode
		title->setStyleSheet("color: #222023; background: transparent;");
		leftBar->setStyleSheet("background-color: #222023; border: none;");
		bar->setStyleSheet("border: none; background-color: #222023;");
		settings_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
            background-color: #2a272a;
        }
    )");
		yourName->setStyleSheet("color: black; background: transparent;");
		yourPass->setStyleSheet("color: black; background: transparent;");
		yourabout->setStyleSheet("color: black; background: transparent;");
		Theme->setStyleSheet("color: black; background: transparent;");
		ppv->setStyleSheet("color: black; background: transparent;");
	}

	// After this, you can proceed with your button connect logic for theme toggling
	QObject::connect(privacyButtonOn, &QPushButton::clicked, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();

		privacyButtonOn->setChecked(true);
		privacyButtonOff->setChecked(false);
		users[currentUserID]->profile.visibility = 1;

		QString activeStyle, inactiveStyle;
		if (users[currentUserID]->theme == 1) { // light mode
			activeStyle = R"(
			QPushButton {
				background-color: #30473a;
				color: white;
				border: none;
				border-top-left-radius: 9px;
				border-bottom-left-radius: 9px;
				font-weight: bold;
			}
			QPushButton:hover {
				background-color: #639378;
			}
		)";
			inactiveStyle = R"(
			QPushButton {
				background-color: #d4d9d7;
				color: black;
				border: none;
				border-top-right-radius: 9px;
				border-bottom-right-radius: 9px;
				font-weight: normal;
			}
			QPushButton:hover {
				background-color: #e0e0e0;
			}
		)";

		}
		else { // dark mode
			activeStyle = R"(
			QPushButton {
				background-color: #222023;
				color: white;
				border: none;
				border-top-left-radius: 9px;
				border-bottom-left-radius: 9px;
				font-weight: bold;
			}
			QPushButton:hover {
				background-color: #2e2c2f;
			}
		)";
			inactiveStyle = R"(
			QPushButton {
				background-color: #d4d9d7;
				color: black;
				border: none;
				border-top-right-radius: 9px;
				border-bottom-right-radius: 9px;
				font-weight: normal;
			}
			QPushButton:hover {
				background-color: #e0e0e0;
			}
		)";
		}


		privacyButtonOn->setStyleSheet(activeStyle);
		privacyButtonOff->setStyleSheet(inactiveStyle);
		updateUsersToJson();
		});

	QObject::connect(privacyButtonOff, &QPushButton::clicked, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();

		privacyButtonOff->setChecked(true);
		privacyButtonOn->setChecked(false);
		users[currentUserID]->profile.visibility = 0;

		QString activeStyle, inactiveStyle;
		if (users[currentUserID]->theme == 1) { // light mode
			activeStyle = R"(
			QPushButton {
				background-color: #30473a;
				color: white;
				border: none;
				border-top-right-radius: 9px;
				border-bottom-right-radius: 9px;
				font-weight: bold;
			}
			QPushButton:hover {
				background-color: #639378;
			}
		)";
			inactiveStyle = R"(
			QPushButton {
				background-color: #d4d9d7;
				color: black;
				border: none;
				border-top-left-radius: 9px;
				border-bottom-left-radius: 9px;
				font-weight: normal;
			}
			QPushButton:hover {
				background-color: #e0e0e0;
			}
		)";
		}
		else { // dark mode
			activeStyle = R"(
			QPushButton {
				background-color: #222023;
				color: white;
				border: none;
				border-top-right-radius: 9px;
				border-bottom-right-radius: 9px;
				font-weight: bold;
			}
			QPushButton:hover {
				background-color: #2e2c2f;
			}
		)";
			inactiveStyle = R"(
			QPushButton {
				background-color: #d4d9d7;
				color: black;
				border: none;
				border-top-left-radius: 9px;
				border-bottom-left-radius: 9px;
				font-weight: normal;
			}
			QPushButton:hover {
				background-color: #e0e0e0;
			}
		)";
		}

		privacyButtonOff->setStyleSheet(activeStyle);
		privacyButtonOn->setStyleSheet(inactiveStyle);
		updateUsersToJson();
		});

	// Connect them to toggle4
	QObject::connect(darkButton, &QPushButton::clicked, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();

		darkButton->setChecked(true);
		lightButton->setChecked(false);
		HidechatArea->setPixmap(QPixmap("icons/chatImg.png"));

		users[currentUserID]->theme = 0;
		updateUsersToJson();

		saveBtn->setStyleSheet(R"(
	QPushButton {
		border: none;
		border-radius: 9px;
		font-size: 14px;
		color: #d4d9d7;
		background-color: #222023;
	}
	QPushButton:hover {
		background-color: #2e2c2f;
	}
	)");

		QString activeLeftStyle = R"(
	QPushButton {
		background-color: #222023;
		color: white;
		border: none;
		border-top-left-radius: 9px;
		border-bottom-left-radius: 9px;
		font-weight: bold;
	}
	QPushButton:hover {
		background-color: #2e2c2f;
	}
	)";
		QString inactiveRightStyle = R"(
	QPushButton {
		background-color: #d4d9d7;
		color: black;
		border: none;
		border-top-right-radius: 9px;
		border-bottom-right-radius: 9px;
		font-weight: normal;
	}
	QPushButton:hover {
		background-color: #e0e0e0;
	}
	)";

		darkButton->setStyleSheet(activeLeftStyle);
		lightButton->setStyleSheet(inactiveRightStyle);

		// Update visibility button styles too
		if (users[currentUserID]->profile.visibility == 1) {
			privacyButtonOn->setChecked(true);
			privacyButtonOff->setChecked(false);

			QString activeLeftStyleP = activeLeftStyle;
			QString inactiveRightStyleP = inactiveRightStyle;

			privacyButtonOn->setStyleSheet(activeLeftStyleP);
			privacyButtonOff->setStyleSheet(inactiveRightStyleP);
		}
		else {
			privacyButtonOn->setChecked(false);
			privacyButtonOff->setChecked(true);

			QString activeRightStyle = activeLeftStyle;
			activeRightStyle.replace("border-top-left-radius", "border-top-right-radius");
			activeRightStyle.replace("border-bottom-left-radius", "border-bottom-right-radius");

			QString inactiveLeftStyle = inactiveRightStyle;
			inactiveLeftStyle.replace("border-top-right-radius", "border-top-left-radius");
			inactiveLeftStyle.replace("border-bottom-right-radius", "border-bottom-left-radius");

			privacyButtonOff->setStyleSheet(activeRightStyle);
			privacyButtonOn->setStyleSheet(inactiveLeftStyle);
		}

		// Update theme colors
		title->setStyleSheet("color: #222023; background: transparent;");
		leftBar->setStyleSheet("background-color: #222023; border: none;");
		bar->setStyleSheet("border: none; background-color: #222023;");
		settings_Button->setStyleSheet(R"(
	QToolButton {
		background: none;
		border: none;
		background-color: #2a272a;
	}
	)");
		yourName->setStyleSheet("color: #222023; background: transparent;");
		yourPass->setStyleSheet("color: #222023; background: transparent;");
		yourabout->setStyleSheet("color: #222023; background: transparent;");
		Theme->setStyleSheet("color: #222023; background: transparent;");
		ppv->setStyleSheet("color: #222023; background: transparent;");


		updateUsersToJson(); // Save the theme preference
		});

	QObject::connect(lightButton, &QPushButton::clicked, [=]() {
		emptyNameLabel->hide();
		emptyPasswordLabel->hide();
		wrongPasswordLabel->hide();
		doneLabel->hide();

		saveBtn->setStyleSheet(R"(
	QPushButton {
		border: none;
		border-radius: 9px;
		font-size: 14px;
		color: #d4d9d7;
		background-color: #30473a;
	}
	QPushButton:hover {
		background-color: #639378;
	}
	)");
		HidechatArea->setPixmap(QPixmap("icons/chatImg2.png"));
		lightButton->setChecked(true);
		darkButton->setChecked(false);
		users[currentUserID]->theme = 1;
		updateUsersToJson();

		QString activeRightStyle = R"(
	QPushButton {
		background-color: #30473a;
		color: white;
		border: none;
		border-top-right-radius: 9px;
		border-bottom-right-radius: 9px;
		font-weight: bold;
	}
	QPushButton:hover {
		background-color: #639378;
	}
	)";
		QString inactiveLeftStyle = R"(
	QPushButton {
		background-color: #d4d9d7;
		color: black;
		border: none;
		border-top-left-radius: 9px;
		border-bottom-left-radius: 9px;
		font-weight: normal;
	}
	QPushButton:hover {
		background-color: #e0e0e0;
	}
	)";

		lightButton->setStyleSheet(activeRightStyle);
		darkButton->setStyleSheet(inactiveLeftStyle);

		// Update visibility buttons' styles and states
		if (users[currentUserID]->profile.visibility == 1) {
			privacyButtonOn->setChecked(true);
			privacyButtonOff->setChecked(false);

			QString activeLeftStyleP = activeRightStyle;
			activeLeftStyleP.replace("border-top-right-radius", "border-top-left-radius");
			activeLeftStyleP.replace("border-bottom-right-radius", "border-bottom-left-radius");

			QString inactiveRightStyleP = inactiveLeftStyle;
			inactiveRightStyleP.replace("border-top-left-radius", "border-top-right-radius");
			inactiveRightStyleP.replace("border-bottom-left-radius", "border-bottom-right-radius");

			privacyButtonOn->setStyleSheet(activeLeftStyleP);
			privacyButtonOff->setStyleSheet(inactiveRightStyleP);
		}
		else {
			privacyButtonOn->setChecked(false);
			privacyButtonOff->setChecked(true);

			QString activeRightStyleP = activeRightStyle;
			QString inactiveLeftStyleP = inactiveLeftStyle;

			privacyButtonOff->setStyleSheet(activeRightStyleP);
			privacyButtonOn->setStyleSheet(inactiveLeftStyleP);
		}

		// Theme color updates
		title->setStyleSheet("color: #30473a; background: transparent;");
		leftBar->setStyleSheet("background-color: #30473a; border: none;");
		bar->setStyleSheet("border: none; background-color: #30473a;");
		settings_Button->setStyleSheet(R"(
	QToolButton {
		background: none;
		border: none;
		background-color: #30473a;
	}
	)");
		yourName->setStyleSheet("color: #30473a; background: transparent;");
		yourPass->setStyleSheet("color: #30473a; background: transparent;");
		yourabout->setStyleSheet("color: #30473a; background: transparent;");
		Theme->setStyleSheet("color: #30473a; background: transparent;");
		ppv->setStyleSheet("color: #30473a; background: transparent;");

		updateUsersToJson(); // Save theme selection
		});


	QObject::connect(story_Button, &QPushButton::clicked, [=]() {
		container->hide();
		project_Gui::story_Screen(window);
		});

	QObject::connect(home_Button, &QPushButton::clicked, [=]() {
		container->hide();
		project_Gui::chat_Screen(window);
		});

	QObject::connect(group_Button, &QPushButton::clicked, [=]() {
		container->hide();
		project_Gui::group_Screen(window);
		});

	container->show();
}

void project_Gui::group_Screen(QWidget* window) {
	QWidget* container = new QWidget(window);
	container->setGeometry(0, 0, 1280, 720);
	QFont ButtonFont("Poppins", 10);
	QFont ButtonFont6("Poppins", 11);
	QFont popFont("Poppins", 13, QFont::Bold);

	// Chat wallpaper
	QLabel* chatWallpaper = new QLabel(container);
	chatWallpaper->setGeometry(442, 0, 838, 720);
	chatWallpaper->setPixmap(QPixmap("icons/chatWallpaper.png"));
	chatWallpaper->setScaledContents(true);
	chatWallpaper->setStyleSheet("border: none;");

	// Contacts room
	QWidget* contactsArea = new QWidget(container);
	contactsArea->setGeometry(61, 66, 380, 720);
	contactsArea->setStyleSheet("border: none; background-color: #eef4f2;");

	// Chats room
	QWidget* chatArea = new QWidget(container);
	chatArea->setGeometry(442, 0, 838, 720);
	chatArea->setStyleSheet(R"(
        QWidget {
            background-color: transparent;
            border: none;
        }
    )");

	// Scrolling area
	QScrollArea* contactScrollArea = new QScrollArea(contactsArea);
	contactScrollArea->setGeometry(0, 87, 380, 567);
	contactScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	contactScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	contactScrollArea->setWidgetResizable(true);
	contactScrollArea->setStyleSheet(R"(
        QScrollBar:vertical, QScrollBar:horizontal {
            width: 0px;
            height: 0px;
            background: transparent;
        }
    )");

	QScrollArea* chatScrollArea = new QScrollArea(chatArea);
	chatScrollArea->setGeometry(0, 87, 838, 567);
	chatScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	chatScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	chatScrollArea->setWidgetResizable(true);
	chatScrollArea->setStyleSheet(R"(
        QScrollBar:vertical, QScrollBar:horizontal {
            width: 0px;
            height: 0px;
            background: transparent;
        }
    )");

	QWidget* contactListWidget = new QWidget();
	contactListWidget->setStyleSheet("background-color: transparent; background-color: #eef4f2;");
	contactScrollArea->setWidget(contactListWidget);

	QWidget* chatMessagesWidget = new QWidget();
	chatMessagesWidget->setStyleSheet("background-color: transparent;");
	chatScrollArea->setWidget(chatMessagesWidget);

	// Search bar
	QLineEdit* searchField = new QLineEdit(contactsArea);
	searchField->setPlaceholderText("Search");
	searchField->setGeometry(14, 3, 348, 30);
	searchField->setStyleSheet(R"(
        QLineEdit {
            background-color: #222023;
            padding-left: 20px;
            border: none;
            border-radius: 7px;
            font-size: 15px;
            color: #eef4f2;
        }
    )");

	QWidget* SearchDevider1 = new QWidget(contactsArea);
	SearchDevider1->setGeometry(17, 82, 348, 1);
	SearchDevider1->setStyleSheet("background-color: #b4b7b7; border: none;");
	QWidget* SearchDevider2 = new QWidget(contactsArea);
	SearchDevider2->setGeometry(17, 84, 348, 1);
	SearchDevider2->setStyleSheet("background-color: #b4b7b7; border: none;");

	QToolButton* Button4 = new QToolButton(contactsArea);
	Button4->setText("Add Group");
	Button4->setGeometry(14, 40, 120, 30);
	Button4->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 15px;
        color: #e4d9d7;
    )");
	Button4->setFont(ButtonFont);
	Button4->setCursor(Qt::PointingHandCursor);


	QToolButton* searchIcon = new QToolButton(searchField);
	searchIcon->setIcon(QIcon("icons/search.png"));
	searchIcon->setGeometry(0, -5, 40, 40);
	searchIcon->setIconSize(QSize(19, 19));
	searchIcon->setStyleSheet("border: none; background-color: transparent; padding-left: 10px;");
	searchField->addAction(new QWidgetAction(searchIcon), QLineEdit::LeadingPosition);

	// Top and bottom bars
	QWidget* bar = new QWidget(chatArea);
	bar->setGeometry(0, 0, 860, 66);

	QWidget* bar2 = new QWidget(chatArea);
	bar2->setGeometry(0, 654, 860, 66);
	if (users[currentUserID]->theme == 1) {
		bar->setStyleSheet("border: none; background-color: #31473a;");
		bar2->setStyleSheet("border: none; background-color: #31473a;");
	}
	else {
		bar->setStyleSheet("border: none; background-color: #222023;");
		bar2->setStyleSheet("border: none; background-color: #222023;");
	}

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
	shadow->setBlurRadius(20);
	shadow->setOffset(0, 1);
	shadow->setColor(QColor(0, 0, 0, 80));
	bar->setGraphicsEffect(shadow);

	QGraphicsDropShadowEffect* shadow2 = new QGraphicsDropShadowEffect();
	shadow2->setBlurRadius(20);
	shadow2->setOffset(0, -1);
	shadow2->setColor(QColor(0, 0, 0, 80));
	bar2->setGraphicsEffect(shadow2);

	// Chat name button
	QPushButton* chatNameButton = new QPushButton(bar);
	chatNameButton->setGeometry(70, 12, 400, 40);
	QFont nameFont("Poppins", 16, QFont::Bold);
	chatNameButton->setFont(nameFont);
	chatNameButton->setStyleSheet(R"(
        QPushButton {
            background: transparent;
            border: none;
            color: #e4d9d7;
            text-align: left;
            padding: 0;
        }
    )");
	chatNameButton->setCursor(Qt::PointingHandCursor);
	chatNameButton->setFlat(true);

	// Avatar button
	QPushButton* avatarButton = new QPushButton(bar);
	avatarButton->setGeometry(20, 13, 40, 40);
	avatarButton->setStyleSheet(R"(
        QPushButton {
            border: 2px solid #222023;
            border-radius: 20px;
            background: transparent;
            padding: 0;
        }
        QPushButton:hover {
            border-color: #e4d9d7;
        }
    )");
	avatarButton->setCursor(Qt::PointingHandCursor);
	avatarButton->setFlat(true);

	QLabel* avatarLabel = new QLabel(avatarButton);
	avatarLabel->setGeometry(0, 0, 40, 40);
	avatarLabel->setScaledContents(true);
	avatarLabel->setStyleSheet("border-radius: 20px;");

	// Hide chat area
	QLabel* HidechatArea = new QLabel(container);
	HidechatArea->setGeometry(442, 0, 838, 720);
	if(users[currentUserID]->theme == 1) HidechatArea->setPixmap(QPixmap("icons/chatImg2.png"));
	else HidechatArea->setPixmap(QPixmap("icons/chatImg.png"));
	HidechatArea->setScaledContents(true);
	HidechatArea->setStyleSheet("border: none; background-color: #222023;");

	// Right-click context menu
	QWidget* rightClickContainer = new QWidget(container);
	rightClickContainer->setStyleSheet(R"(
        QWidget {
            border-radius: 3px;
            border: none;
            background-color: #eef4f2;
        }
    )");
	rightClickContainer->hide();

	QWidget* rightClickDiv = new QWidget(rightClickContainer);
	rightClickDiv->setStyleSheet("background-color: transparent;");

	QWidget* rightClickColors = new QWidget(rightClickContainer);
	rightClickColors->setStyleSheet(R"(
        QWidget {
            border-top-left-radius: 3px;
            border-top-right-radius: 3px;
            border-bottom-left-radius: 0px;
            border-bottom-right-radius: 0px;
            background-color: #f44400;
        }
    )");

	QToolButton* deleteBtn = new QToolButton(rightClickContainer);
	deleteBtn->setText(" Delete");
	deleteBtn->setStyleSheet(R"(
        QToolButton {
            background-color: transparent;
            border: none;
            color: #e4d9d7;
        }
    )");
	deleteBtn->setFont(ButtonFont6);
	QIcon icon("icons/trash.png");
	deleteBtn->setIcon(icon);
	deleteBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

	QToolButton* closeBtn = new QToolButton(rightClickContainer);
	closeBtn->setText("Close");
	closeBtn->setStyleSheet(R"(
        QToolButton {
            background-color: transparent;
            border: none;
            color: #f44400;
        }
    )");
	closeBtn->setFont(ButtonFont6);

	closeBtn->setGeometry(0, 30, 85, 30);
	rightClickDiv->setGeometry(0, 29, 85, 1);
	rightClickColors->setGeometry(0, 0, 85, 30);
	deleteBtn->setGeometry((85 - 67) / 2, 0, 67, 30);

	// Message field
	QLineEdit* messageField = new QLineEdit(chatArea);
	messageField->setPlaceholderText("Type a message");
	messageField->setGeometry(55, 669, 745, 38);
	messageField->setStyleSheet(R"(
        QLineEdit {
            padding-left: 18px;
            border: none;
            border-radius: 7px;
            font-size: 14px;
            background: #2d2c2d;
            color: #ffffff;
        }
    )");

	QAction* iconAction = new QAction(QIcon("icons/sending.png"), "", messageField);
	messageField->addAction(iconAction, QLineEdit::TrailingPosition);

	// Contact buttons for group chats
	struct ContactInfo {
		QPushButton* button;
		QString name;
		int number;
		int originalIndex;
		QString avatar;
		int chatRoomID;
	};
	QVector<ContactInfo> contactInfos;
	int contactHeight = 81;
	int index = 0;

	QSet<int> processedChatRooms;
	vector<string> predefinedColors = {
	"#FF0000", // Red
	"#008000", // Green
	"#0000FF", // Blue
	"#FFA500", // Orange
	"#800080", // Purple
	"#A52A2A", // Brown
	"#008080", // Teal
	"#DC143C", // Crimson (stronger than pink)
	"#1E90FF"  // DodgerBlue (brighter blue)
	};

	random_device rd;
	mt19937 g(rd());
	shuffle(predefinedColors.begin(), predefinedColors.end(), g);

	map<int,string> userColors;
	size_t colorIndex = 0;

	for (const auto& room : users[currentUserID]->chatRooms) {
		if (room.type() == "Group" && !processedChatRooms.contains(room.getChatRoomID())) {
			for (auto userId : room.getUserIDs()) {
				if (userColors.find(userId) == userColors.end()) {
					userColors[userId] = predefinedColors[colorIndex % predefinedColors.size()];
					++colorIndex;
				}
			}
		}
	}

	for (const auto& room : users[currentUserID]->chatRooms) {
		if (room.type() == "Group" && !processedChatRooms.contains(room.getChatRoomID())) {
			int sharedRoomID = room.getChatRoomID();
			QString name = room.gcName == "" ? QString("Group %1").arg(sharedRoomID) : QString::fromStdString(room.gcName); // Use chat room ID for unique name
			int selectedID = -1;
			for (int userId : room.getUserIDs()) {
				if (userId != currentUserID) {
					selectedID = userId;
					break;
				}
			}
			if (selectedID == -1) continue; 

			int number = users[selectedID]->getNumber();
			QString avatar = QString::fromStdString(room.gcAvatar);
			QPushButton* contactBtn = customized_Contact(name, contactListWidget, index * contactHeight, avatar);
			contactBtn->setFixedHeight(contactHeight);
			contactBtn->setObjectName("contactBtn");

			vector<Message> messages = room.getMessages();
			if (!messages.empty()) {
				vector<Message> SortedMessages = sortMessagesBySentTime(messages);
				Message latestMessage = SortedMessages.back(); 
				QString messageText = QString::fromStdString(latestMessage.text);
				QString Qtime24 = QString::fromStdString(latestMessage.timeSent);
				QTime Qtime = QTime::fromString(Qtime24, "HH:mm:ss");
				QString Qtime12 = Qtime.toString("hh:mm AP");

				QLabel* messageLabel = contactBtn->findChild<QLabel*>("messageLabel");
				QLabel* messageLabelTime = contactBtn->findChild<QLabel*>("messageLabelTime");
				if (messageLabel) {
					QFontMetrics metrics(messageLabel->font());
					if (metrics.horizontalAdvance(messageText) > 225) {
						messageText = metrics.elidedText(
							messageText,
							Qt::ElideRight,  
							225
						);
					}

					messageLabel->setText(messageText);
					messageLabelTime->setText(Qtime12);
				}
			}
			else {
				QLabel* messageLabel = contactBtn->findChild<QLabel*>("messageLabel");
				if (messageLabel) {
					messageLabel->setText("Start chatting now!");
				}
			}

			// Connect button click
			QObject::connect(contactBtn, &QPushButton::clicked, [=]() {
				QPushButton* TEMPbtn = nullptr;
				for (QPushButton* btn : contactListWidget->findChildren<QPushButton*>("contactBtn")) {
					if (btn == contactBtn && TEMPbtn != nullptr) {
						QLabel* Tempy = TEMPbtn->findChild<QLabel*>("userDev2");
						Tempy->setGeometry(43, 80, 380, 0);
					}
					else {
						QLabel* Tempy = btn->findChild<QLabel*>("userDev2");
						Tempy->setGeometry(43, 80, 380, 1);
					}
					btn->setStyleSheet(R"(
							QPushButton {
							    background-color: #eef4f2;
							    text-align: left;
							    border: none;
							    padding-left: 70px;
							    padding-bottom: 17px;
							    font-size: 20px;
							    color: black;
							}
							QPushButton:hover {
							    background-color: #eaedec;
							}
							)");
					TEMPbtn = btn;
				}


				contactBtn->setStyleSheet(R"(
						QPushButton {
							background-color: #dde3e1;
							text-align: left;
							border: none;
							padding-left: 70px;
							padding-bottom: 17px;
							font-size: 20px;
							color: black;
						}
						)");

				messageField->clear();
				chatNameButton->setText(name);
				QPixmap originalPixmap(avatar);
				QPixmap circularPixmap(40, 40);
				circularPixmap.fill(Qt::transparent);
				QPainter painter(&circularPixmap);
				painter.setRenderHint(QPainter::Antialiasing);
				QPainterPath path;
				path.addEllipse(0, 0, 40, 40);
				painter.setClipPath(path);
				painter.drawPixmap(0, 0, 40, 40, originalPixmap);
				avatarLabel->setPixmap(circularPixmap);
				HidechatArea->hide();
				chatMessagesWidget->show();
				selectedNumber = number;
				selectedAvatar = avatar;
				selectedChatRoom = sharedRoomID;
				rightClickContainer->hide();


				for (ChatRoom& room : users[currentUserID]->chatRooms) {
					if (room.getChatRoomID() == selectedChatRoom) {
						vector<int> userIDs = room.getUserIDs();
						vector<Message> currentUserMessages = room.getMessages();
						vector<Message> updatedMessages = currentUserMessages;

						for (Message& msg : updatedMessages) {
							if (msg.getUserID() != currentUserID) {
								msg.addViewer(currentUserID);
								vector<int> viewedBy = msg.getViewedBy();
								bool allViewed = true;
								for (int userId : userIDs) {
									if (userId != msg.getUserID()) { 
										if (find(viewedBy.begin(), viewedBy.end(), userId) == viewedBy.end()) {
											allViewed = false;
											break;
										}
									}
								}
								msg.setStatus(allViewed ? "seen" : "unseen");
							}
						}

						for (int userId : userIDs) {
							if (userId != currentUserID) {
								for (ChatRoom& otherRoom : users[userId]->chatRooms) {
									if (otherRoom.getChatRoomID() == selectedChatRoom) {
										vector<Message> otherMsgs = otherRoom.getMessages();
										bool updated = false;
										for (Message& otherMsg : otherMsgs) {
											for (const Message& updatedMsg : updatedMessages) {
												if (otherMsg.getMessageID() == updatedMsg.getMessageID()) {
													otherMsg.setViewedBy(updatedMsg.getViewedBy());
													otherMsg.setStatus(updatedMsg.getStatus());
													updated = true;
													break;
												}
											}
										}
										if (updated) {
											otherRoom.setMessages(otherMsgs);
										}
										break;
									}
								}
							}
						}

						room.setMessages(updatedMessages);
						break;
					}
				}

				updateUsersToJson();
				// Clear and display messages
				QLayout* layout = chatMessagesWidget->layout();
				if (!layout) {
					layout = new QVBoxLayout(chatMessagesWidget);
					chatMessagesWidget->setLayout(layout);
				}
				QVBoxLayout* messagesLayout = qobject_cast<QVBoxLayout*>(layout);
				QLayoutItem* item;
				while ((item = messagesLayout->takeAt(0)) != nullptr) {
					if (item->widget()) delete item->widget();
					delete item;
				}
				messagesLayout->setAlignment(Qt::AlignTop);
				messagesLayout->setSpacing(5);
				int y = 0;
				srand(static_cast<unsigned int>(time(0)));


				for (ChatRoom& room : users[currentUserID]->chatRooms) {
					if (room.getChatRoomID() == sharedRoomID) {
						vector<Message> sortedMessages = sortMessagesBySentTime(room.getMessages());
						for (const Message& msg : sortedMessages) {
							QString msgText = QString::fromStdString(msg.text);
							QLabel* messageLabel = new QLabel(wrapMessage(msgText), chatMessagesWidget);
							QFont nameFont("Poppins", 14);
							messageLabel->setFont(nameFont);
							messageLabel->setWordWrap(true);

							int chatAreaWidth = 838;
							int labelWidth = 500;
							int marginRightSent = 10;
							int marginLeftSent = chatAreaWidth - labelWidth - marginRightSent;
							int marginLeftReceived = 10;
							int marginRightReceived = chatAreaWidth - labelWidth - marginLeftReceived;

							QWidget* alignmentContainer = new QWidget(chatMessagesWidget);
							QHBoxLayout* alignmentLayout = new QHBoxLayout(alignmentContainer);
							alignmentLayout->setContentsMargins(0, 0, 0, 0);
							alignmentLayout->setSpacing(0);

							auto rightClickFilter = new LambdaEventFilter(
								[=](QObject* watched, QEvent* event) -> bool {
									if (event->type() == QEvent::MouseButtonPress) {
										QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
										if (mouseEvent->button() == Qt::RightButton && msg.getUserID() == currentUserID) {
											QPoint globalPos = QCursor::pos();
											rightClickContainer->move(globalPos);
											if (globalPos.x() > 1194) {
												rightClickContainer->setGeometry(1194, globalPos.y() - 20, 85, 60);
											}
											else {
												rightClickContainer->setGeometry(globalPos.x(), globalPos.y() - 20, 85, 60);
											}
											rightClickContainer->setProperty("messageId", msg.getMessageID());
											rightClickContainer->setProperty("alignmentContainer", QVariant::fromValue(alignmentContainer));
											rightClickContainer->show();
											return true;
										}
									}
									return false;
								},
								messageLabel
							);
							messageLabel->installEventFilter(rightClickFilter);
							QLabel* messageNameLabel = new QLabel(QString::fromStdString(users[msg.getUserID()]->Fname), messageLabel);
							QString style = (msg.getUserID() == currentUserID) ?
								QString(R"(
                                    color: white;
                                    background-color: #222023;
                                    border: 1px solid #444;
                                    border-radius: 7px;
                                    padding: 10px;
                                    padding-bottom: 20px;
                                )") : QString(R"(
                                    color: black;
                                    background-color: #eef4f2;
                                    border: 1px solid rgba(0, 0, 0, 30);
                                    border-radius: 7px;
                                    padding: 10px;
                                    padding-top: 22px;
                                    padding-bottom: 18px;
                                )");

							if (users[currentUserID]->theme == 1) {
								style = (msg.getUserID() == currentUserID) ?
									QString(R"(
                                    color: white;
                                    background-color: #31473a;
                                    border: 1px solid #444;
                                    border-radius: 7px;
                                    padding: 10px;
                                    padding-bottom: 20px;
                                )") : QString(R"(
                                    color: black;
                                    background-color: #eef4f2;
									border: 1px solid rgba(0, 0, 0, 30);
                                    border-radius: 7px;
                                    padding: 10px;
                                    padding-top: 22px;
                                    padding-bottom: 18px;
                                )");
							} 
							if (messageLabel->text().isEmpty()) {
								style += R"(
                                    min-height: 30px;
                                )";
							}
							messageLabel->setStyleSheet(style);
							messageLabel->adjustSize();
							if (messageLabel->width() < 89) {
								messageLabel->setMinimumWidth(89);
							}
							messageLabel->setMinimumHeight(messageLabel->height() + 10);

							QWidget* messageContainer = new QWidget(chatMessagesWidget);
							messageContainer->setProperty("messageId", msg.getMessageID());
							messageContainer->raise();

							QVBoxLayout* containerLayout = new QVBoxLayout(messageContainer);
							containerLayout->setContentsMargins(0, 0, 0, 0);
							containerLayout->setSpacing(2);

							containerLayout->addWidget(messageLabel);

							QWidget* bottomRow = new QWidget(messageContainer);
							QHBoxLayout* bottomLayout = new QHBoxLayout(bottomRow);
							bottomLayout->setContentsMargins(0, 0, 0, 0);
							bottomLayout->setSpacing(5);

							QString timeStr = QString::fromStdString(msg.timeSent).left(5);
							QTime time = QTime::fromString(timeStr, "HH:mm");
							QString formattedTime = time.toString("h:mm AP");
							QLabel* timestampLabel = new QLabel(formattedTime, messageLabel);
							QFont timestampFont("Poppins", 8);
							QFont timestampFont2("Poppins", 8, QFont::Bold);
							timestampLabel->setFont(timestampFont);
							timestampLabel->setStyleSheet(R"(
                                color: rgba(135, 135, 135, 127);
                                background: transparent;
                                padding: 0px;
                                qproperty-alignment: AlignLeft;
                                border: none;
                            )");
							timestampLabel->adjustSize();


							messageNameLabel->adjustSize();
							messageNameLabel->setFont(timestampFont2);
							QString color = QString::fromStdString(userColors.at(msg.getUserID()));

							QString style22 = QString(
								"color: %1;"
								"background: transparent;"
								"padding: 0px;"
								"qproperty-alignment: AlignLeft;"
								"padding-top: 7px;"
								"padding-left: 4px;"
								"border: none;"
							).arg(color);

							messageNameLabel->setStyleSheet(style22);

							if (msg.getUserID() == currentUserID) {
								messageNameLabel->hide();
								timestampLabel->move(messageLabel->width() - timestampLabel->width() - 28, messageLabel->height() - timestampLabel->height() - 4);
							}
							else {
								messageNameLabel->show();
								timestampLabel->move(messageLabel->width() - timestampLabel->width() - 7, messageLabel->height() - timestampLabel->height() - 4);
							}

							if (msg.getUserID() == currentUserID) {
								QString iconPath = (msg.status == "seen") ? "icons/Doublecheck2.png" : "icons/Doublecheck.png";
								QLabel* seenLabel = new QLabel(messageLabel);
								QPixmap iconPixmap(iconPath);
								seenLabel->setPixmap(iconPixmap.scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
								seenLabel->setStyleSheet("background: transparent; border: none;");
								seenLabel->adjustSize();
								seenLabel->move(messageLabel->width() - seenLabel->width() + 3, messageLabel->height() - timestampLabel->height() - 13);
							}

							containerLayout->addWidget(bottomRow);

							if (msg.getUserID() == currentUserID) {
								alignmentLayout->addStretch();
								alignmentLayout->addWidget(messageContainer);
							}
							else {
								alignmentLayout->addWidget(messageContainer);
								alignmentLayout->addStretch();
							}

							messagesLayout->addWidget(alignmentContainer);
							y += messageContainer->height() + 5;
						}
						break;
					}
				}

				chatMessagesWidget->adjustSize();
				chatMessagesWidget->setMinimumHeight(chatMessagesWidget->sizeHint().height());
				QTimer::singleShot(0, [=]() {
					if (chatMessagesWidget->height() > chatScrollArea->viewport()->height()) {
						chatScrollArea->verticalScrollBar()->setValue(chatScrollArea->verticalScrollBar()->maximum());
					}
					});
				});

			contactInfos.append({ contactBtn, name, number, index, avatar, sharedRoomID });
			processedChatRooms.insert(sharedRoomID);
			index++;
		}
	}

	// Set up contact layout
	QVBoxLayout* contactLayout = new QVBoxLayout(contactListWidget);
	contactLayout->setContentsMargins(0, 0, 0, 0);
	contactLayout->setSpacing(0);
	contactLayout->setAlignment(Qt::AlignTop);
	for (const auto& info : contactInfos) {
		contactLayout->addWidget(info.button);
	}
	contactListWidget->setMinimumHeight(contactInfos.size() * contactHeight);
	contactListWidget->setFixedWidth(380);

	// Search functionality
	QObject::connect(searchField, &QLineEdit::textChanged, [=](const QString& text) {
		QString searchText = text.trimmed().toLower();
		int visibleCount = 0;
		for (auto& info : contactInfos) {
			bool isVisible = (searchText.isEmpty() || info.name.toLower().startsWith(searchText));
			info.button->setVisible(isVisible);
			if (isVisible) {
				visibleCount++;
			}
		}

		QVector<ContactInfo> sortedInfos = contactInfos;
		   sort(sortedInfos.begin(), sortedInfos.end(), [](const ContactInfo& a, const ContactInfo& b) {
			if (a.button->isVisible() != b.button->isVisible())
				return a.button->isVisible();
			return a.originalIndex < b.originalIndex;
			});

		QLayoutItem* item;
		while ((item = contactLayout->takeAt(0)) != nullptr) {
			delete item;
		}
		for (const auto& info : sortedInfos) {
			contactLayout->addWidget(info.button);
		}

		contactListWidget->setMinimumHeight(visibleCount * contactHeight);
		contactScrollArea->verticalScrollBar()->setValue(0);

		if (visibleCount == 0) {
			HidechatArea->show();
			chatMessagesWidget->hide();
			avatarLabel->clear();
			chatNameButton->setText("");
			selectedAvatar = nullptr;
			selectedNumber = -1;
		}
		});

	// Message sending
	QObject::connect(messageField, &QLineEdit::returnPressed, [=]() {
		QString Fmessage = messageField->text().trimmed();
		if (!Fmessage.isEmpty() && selectedChatRoom != 0) { 
			int addedHeight = customized_chat(Fmessage, chatMessagesWidget, selectedChatRoom);
			chatMessagesWidget->setMinimumHeight(chatMessagesWidget->height() + addedHeight);
			messageField->clear();
			chatScrollArea->ensureVisible(0, chatMessagesWidget->height());

			// 2n 
			for (const auto& info : contactInfos) {
				for (ChatRoom& room : users[currentUserID]->chatRooms) {
					if (room.getChatRoomID() == selectedChatRoom) {
						// Match the contact button to the chat room
						vector<int> userIDs = room.getUserIDs();
						int otherUserID = (userIDs[0] != currentUserID) ? userIDs[0] : userIDs[1];
						if (info.number == users[otherUserID]->getNumber()) {
				
							vector<Message> messages = room.getMessages();
							if (!messages.empty()) {
								vector<Message> sortedMessages = sortMessagesBySentTime(messages);
								Message latestMessage = sortedMessages.back();
								QString messageText = QString::fromStdString(latestMessage.text);
								QString Qtime24 = QString::fromStdString(latestMessage.timeSent);
								QTime Qtime = QTime::fromString(Qtime24, "HH:mm:ss");
								QString Qtime12 = Qtime.toString("hh:mm AP");

								QLabel* messageLabel = info.button->findChild<QLabel*>("messageLabel");
								QLabel* messageLabelTime = info.button->findChild<QLabel*>("messageLabelTime");

								if (messageLabel) {
									QFontMetrics metrics(messageLabel->font());
									if (metrics.horizontalAdvance(messageText) > 225) {
										messageText = metrics.elidedText(
											messageText,
											Qt::ElideRight, 
											225
										);
									}

									messageLabel->setText(messageText);
									messageLabelTime->setText(Qtime12);
								}
							}
							break;
						}
					}
				}
			}
		}
		});

	QObject::connect(iconAction, &QAction::triggered, [=]() {
		QString Fmessage = messageField->text().trimmed();
		if (!Fmessage.isEmpty() && selectedChatRoom != 0) {
			int addedHeight = customized_group(Fmessage, chatMessagesWidget, selectedChatRoom);
			chatMessagesWidget->setMinimumHeight(chatMessagesWidget->height() + addedHeight);
			messageField->clear();
			chatScrollArea->ensureVisible(0, chatMessagesWidget->height());

			for (const auto& info : contactInfos) {
				for (ChatRoom& room : users[currentUserID]->chatRooms) {
					if (room.getChatRoomID() == selectedChatRoom && room.getChatRoomID() == info.chatRoomID) {
						vector<Message> messages = room.getMessages();
						if (!messages.empty()) {
							vector<Message> sortedMessages = sortMessagesBySentTime(messages);
							Message latestMessage = sortedMessages.back();
							QString messageText = QString::fromStdString(latestMessage.text);
							if (messageText.length() > 30) {
								messageText = messageText.left(27) + "...";
							}
							QLabel* messageLabel = info.button->findChild<QLabel*>("messageLabel");
							if (messageLabel) {
								messageLabel->setText(messageText);
							}
						}
						break;
					}
				}
			}
		}
		});

	QObject::connect(deleteBtn, &QToolButton::clicked, [=]() {
		int messageId = rightClickContainer->property("messageId").toInt();
		QWidget* alignmentContainer = rightClickContainer->property("alignmentContainer").value<QWidget*>();
		if (rightClickContainer && alignmentContainer && messageId != 0) {
			rightClickContainer->hide();
			deleteMessage(messageId, alignmentContainer, selectedChatRoom);
		}
		});

	QObject::connect(closeBtn, &QPushButton::clicked, [=]() {
		rightClickContainer->hide();
		});


	// Top bar and dividers
	QWidget* topBar = new QWidget(container);
	topBar->setGeometry(61, 0, 380, 66);
	topBar->setStyleSheet("background-color: #eef4f2; border: none;");
	QWidget* topBarDevider = new QWidget(container);
	topBarDevider->setGeometry(441, 0, 1, 720);
	topBarDevider->setStyleSheet("background-color: #f9eded; border: none;");
	QWidget* leftBar = new QWidget(container);
	leftBar->setGeometry(0, 0, 60, 720);
	QWidget* leftBarDevider = new QWidget(container);
	leftBarDevider->setGeometry(60, 0, 1, 720);
	leftBarDevider->setStyleSheet("background-color: #f9eded; border: none;");

	QLabel* title = new QLabel("Groups", topBar);
	QFont titleFont("Poppins", 21, QFont::Bold);
	title->setFont(titleFont);
	title->setStyleSheet("color: #222023; background: transparent;");
	title->adjustSize();
	title->move(14, 14);

	// Navigation buttons
	QToolButton* home_Button = new QToolButton(leftBar);
	home_Button->setIcon(QIcon("icons/home.png"));
	home_Button->setGeometry(-10, 0, 80, 66);
	home_Button->setIconSize(QSize(28, 28));
	home_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	home_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
        }
    )");

	QToolButton* story_Button = new QToolButton(leftBar);
	story_Button->setIcon(QIcon("icons/story.png"));
	story_Button->setIconSize(QSize(28, 28));
	story_Button->setGeometry(-10, 66, 80, 66);
	story_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	story_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
        }
    )");

	QToolButton* group_Button = new QToolButton(leftBar);
	group_Button->setIcon(QIcon("icons/group-chat.png"));
	group_Button->setIconSize(QSize(30, 30));
	group_Button->setGeometry(-10, 132, 80, 66);
	group_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	group_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
        }
    )");

	QToolButton* settings_Button = new QToolButton(leftBar);
	settings_Button->setIcon(QIcon("icons/setting.png"));
	settings_Button->setIconSize(QSize(28, 28));
	settings_Button->setGeometry(-10, 654, 80, 66);
	settings_Button->setToolButtonStyle(Qt::ToolButtonIconOnly);
	settings_Button->setStyleSheet(R"(
        QToolButton {
            background: none;
            border: none;
        }
    )");

	// Pop-up for user info
	QWidget* infoPopUpContainer = new QWidget(container);
	infoPopUpContainer->setGeometry(0, 0, 1280, 720);
	infoPopUpContainer->setStyleSheet("background-color: rgba(0,0,0,200);");
	infoPopUpContainer->hide();

	QWidget* infoPopUp = new QWidget(infoPopUpContainer);
	infoPopUp->move(491, 200);
	infoPopUp->setMinimumWidth(300);
	infoPopUp->setStyleSheet("background-color: #eef4f2; border-radius: 7px;");

	QLabel* infoName = new QLabel(infoPopUp);
	infoName->move(10, 160);

	infoName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	infoName->setStyleSheet("color: #222023; background: transparent; font-size: 16px; font-weight: bold;");

	QLabel* infoGroupName = new QLabel(infoPopUp);
	infoGroupName->move(0, 120);
	infoGroupName->setStyleSheet("color: #222023; background: transparent; font-size: 19px; font-weight: bold;");

	QLabel* infoNumber = new QLabel(infoPopUp);
	infoNumber->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	infoNumber->setStyleSheet("color: rgba(34, 32, 35, 190); background: transparent; font-size: 16px;");

	QToolButton* closeInfoButton = new QToolButton(infoPopUp);
	closeInfoButton->setText("Close");
	closeInfoButton->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	closeInfoButton->setFont(ButtonFont);
	closeInfoButton->setCursor(Qt::PointingHandCursor);

	QLabel* UserPopavatar = new QLabel(infoPopUp);

	// Show user info
	auto showUserInfo = [=]() {
		if (selectedNumber != -1) {
			int userId = getUserByNumber(selectedNumber);
			QString fullName = "";
			QString GCname = "";
			QString infonumber = "";
			QString selectedGCAvatar = "";
			for (const auto& room : users[currentUserID]->chatRooms) {
				if (room.type() == "Group" && room.getChatRoomID() == selectedChatRoom) {
					for (auto userIDD : room.getUserIDs()) {
						fullName += QString::fromStdString(users[userIDD]->Fname + " " + users[userIDD]->Lname + "\n");
						infonumber += ("+20" + QString::fromStdString(to_string(users[userIDD]->getNumber())) + "\n");
					}
					selectedGCAvatar = QString::fromStdString(room.gcAvatar);
					GCname = room.gcName == "" ? QString("Group %1").arg(room.getChatRoomID()) : QString::fromStdString(room.gcName);
					fullName.chop(1);
					infonumber.chop(1);
				}
			}

			if (userId != -1) {

				User* user = users[userId];
				infoName->setText(fullName);
				infoNumber->setText(infonumber);
				infoGroupName->setText(GCname);
				UserPopavatar->setGeometry(100, 20, 100, 100);
				UserPopavatar->setStyleSheet("background-color: transparent; border-radius: 50px;");
				QPixmap pixmap(selectedGCAvatar);
				QPixmap roundedPixmap(pixmap.size());
				roundedPixmap.fill(Qt::transparent);

				QPainter painter(&roundedPixmap);
				painter.setRenderHint(QPainter::Antialiasing);
				QPainterPath path;
				path.addEllipse(0, 0, pixmap.width(), pixmap.height());
				painter.setClipPath(path);
				painter.drawPixmap(0, 0, pixmap);
				painter.end();
				UserPopavatar->setPixmap(roundedPixmap.scaled(100, 100, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
				UserPopavatar->setStyleSheet("border-radius: 50px;");

				infoName->adjustSize();
				infoNumber->adjustSize();
				infoNumber->move(10 + infoName->width() + 50, 160);
				infoPopUp->adjustSize();
				infoNumber->move(infoPopUp->width() - 10 - infoNumber->width(), 160);
				closeInfoButton->setGeometry((infoPopUp->width() - 70) / 2, infoName->geometry().bottom() + 30, 70, 30);
				UserPopavatar->setGeometry((infoPopUp->width() - 100) / 2, 20, 100, 100);
				infoGroupName->setFixedWidth(infoPopUp->width());
				infoGroupName->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				infoPopUp->adjustSize();

				infoPopUp->move(491, (720 - infoPopUp->height()) / 2);
				infoPopUpContainer->show();
			}
		}
		};

	QObject::connect(chatNameButton, &QPushButton::clicked, showUserInfo);
	QObject::connect(avatarButton, &QPushButton::clicked, showUserInfo);
	QObject::connect(closeInfoButton, &QToolButton::clicked, [=]() {
		infoPopUpContainer->hide();
		});

	// Pop-up for Add Group
	QWidget* popUpContainer2 = new QWidget(container);
	popUpContainer2->setGeometry(0, 0, 1280, 720);
	popUpContainer2->setStyleSheet("background-color: rgba(0,0,0,200);");
	popUpContainer2->hide();

	QWidget* popUpContacts2 = new QWidget(popUpContainer2);
	popUpContacts2->setGeometry(442, 227.5, 398, 265);
	popUpContacts2->setStyleSheet("background-color: #eef4f2; border-radius: 7px;");
	popUpContacts2->show();

	QWidget* popUpContactsName2 = new QWidget(popUpContainer2);
	popUpContactsName2->setGeometry(442, 297.5, 398, 125);
	popUpContactsName2->setStyleSheet("background-color: #eef4f2; border-radius: 7px;");
	popUpContactsName2->hide();

	QLineEdit* popUpNameField2 = new QLineEdit(popUpContactsName2);
	popUpNameField2->setPlaceholderText("Group name");
	popUpNameField2->setGeometry(20, 20, 358, 30);
	QString inputBgColor = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";

	popUpNameField2->setStyleSheet(QString(R"(
    QLineEdit {
        background-color: %1;
        padding-left: 20px;
        border: none;
        border-radius: 7px;
        font-size: 15px;
        color: #222023;
    }
	)").arg(inputBgColor));


	QToolButton* popNameOKButton2 = new QToolButton(popUpContactsName2);
	popNameOKButton2->setText("Create");
	popNameOKButton2->setGeometry(164, 77, 70, 30);
	QString okBtnColor = (users[currentUserID]->theme == 1) ? "#31473a" : "#222023";

	popNameOKButton2->setStyleSheet(QString(R"(
    background-color: %1;
    border: none;
    border-radius: 7px;
    color: #e4d9d7;
)").arg(okBtnColor));

	popNameOKButton2->setFont(ButtonFont);

	QLabel* popLabel2 = new QLabel(popUpContacts2);
	popLabel2->setText("Add Group");
	popLabel2->setGeometry(14, 4, 115, 40);
	popLabel2->setFont(popFont);
	popLabel2->setStyleSheet("color: #222023; background: transparent;");

	QScrollArea* scrollArea = new QScrollArea(popUpContacts2);
	scrollArea->setGeometry(20, 46, 358, 158);
	scrollArea->setWidgetResizable(true);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setStyleSheet("background-color: transparent; border: none;");

	QWidget* scrollPopContainer = new QWidget();
	scrollPopContainer->setStyleSheet("background-color: transparent;");

	QVBoxLayout* layout = new QVBoxLayout(scrollPopContainer);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(12);

	QToolButton* popAddButton2 = new QToolButton(popUpContacts2);
	popAddButton2->setText("Add");
	popAddButton2->setGeometry(20, 218, 50, 30);
	popAddButton2->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	popAddButton2->setFont(ButtonFont);

	QToolButton* popCloseButton2 = new QToolButton(popUpContacts2);
	popCloseButton2->setText("Close");
	popCloseButton2->setGeometry(313, 218, 65, 30);
	popCloseButton2->setStyleSheet(R"(
        background-color: #222023;
        border: none;
        border-radius: 7px;
        color: #e4d9d7;
    )");
	popCloseButton2->setFont(ButtonFont);

	// Error labels
	QLabel* userNotFoundLabel = new QLabel("One or more numbers don't have an account", popUpContacts2);
	userNotFoundLabel->setGeometry(71, 225, 243, 20);
	userNotFoundLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	userNotFoundLabel->setAlignment(Qt::AlignHCenter);
	userNotFoundLabel->hide();

	QLabel* groupExistsLabel = new QLabel("Group with these members already exists", popUpContacts2);
	groupExistsLabel->setGeometry(71, 225, 243, 20);
	groupExistsLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	groupExistsLabel->setAlignment(Qt::AlignHCenter);
	groupExistsLabel->hide();

	QLabel* minUsersLabel = new QLabel("Select at least 2 contacts", popUpContacts2);
	minUsersLabel->setGeometry(71, 225, 243, 20);
	minUsersLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	minUsersLabel->setAlignment(Qt::AlignHCenter);
	minUsersLabel->hide();

	QLabel* maxUsersLabel = new QLabel("You can't select more than 9 contacts", popUpContacts2);
	maxUsersLabel->setGeometry(71, 225, 243, 20);
	maxUsersLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	maxUsersLabel->setAlignment(Qt::AlignHCenter);
	maxUsersLabel->hide();

	QLabel* GCNameEmptyLabel = new QLabel("Name can't be empty", popUpContactsName2);
	GCNameEmptyLabel->setGeometry(0, 57, 398, 20);
	GCNameEmptyLabel->setStyleSheet("color: red; font-size: 12px; background: transparent; border:none;");
	GCNameEmptyLabel->setAlignment(Qt::AlignHCenter);
	GCNameEmptyLabel->hide();

	// Contact list for pop-up
	static QSet<int> selectedContacts;
	static QVector<QPushButton*> btn;
	int indexi = 0;
	for (const auto& [num, name] : users[currentUserID]->getContacts()) {
		QString Qname = QString::fromStdString(name);
		btn.push_back(customizedPop_Contact(num, Qname, scrollPopContainer, -35));
		btn[indexi]->setFixedSize(358, 30);
		layout->addWidget(btn[indexi]);

		QObject::connect(btn[indexi], &QPushButton::clicked, [=]() mutable {
			userNotFoundLabel->hide();
			groupExistsLabel->hide();
			minUsersLabel->hide();
			maxUsersLabel->hide();

			if (selectedContacts.contains(num)) {
				selectedContacts.remove(num);
				QString bgColor = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";
				QString hoverColor = (users[currentUserID]->theme == 1) ? "#dce9e2" : "#e0e4e2";

				btn[indexi]->setStyleSheet(QString(R"(
                QPushButton {
                    background-color: %1;
                    text-align: left;
                    border: none;
                    padding-left: 10px;
                }
                QPushButton:hover {
                    background-color: %2;
                }
                QLabel {
                    color: rgba(34,32,35,110);
                    background: transparent;
                }
                QLabel#numberLabel {
                    color: rgba(34, 32, 35, 255);
                    background: transparent;
                }
                QLabel#nameLabel {
                    color: rgba(34, 32, 35, 110);
                    background: transparent;
                }
            )").arg(bgColor).arg(hoverColor));
			}
			else {
				selectedContacts.insert(num);
				QString bgColor = (users[currentUserID]->theme == 1) ? "#31473a" : "#222023";

				btn[indexi]->setStyleSheet(QString(R"(
                QPushButton {
                    background-color: %1;
                    text-align: left;
                    border: none;
                    padding-left: 10px;
                }
                QLabel {
                    color: rgba(238, 244, 242, 127);
                    background: transparent;
                }
                QLabel#numberLabel {
                    color: #eef4f2;
                    background: transparent;
                }
                QLabel#nameLabel {
                    color: rgba(238, 244, 242, 127);
                    background: transparent;
                }
            )").arg(bgColor));
			}
			});

		indexi++;
	}	scrollArea->setWidget(scrollPopContainer);

	// Add group logic
	QObject::connect(popAddButton2, &QPushButton::clicked, [=]() {
		if (selectedContacts.size() < 2) {
			minUsersLabel->show();
			return;
		}
		else if (selectedContacts.size() > 9) {
			maxUsersLabel->show();
			return;
		}

		vector<int> selectedUserIDs;
		bool allUsersExist = true;
		for (int num : selectedContacts) {
			int userId = getUserByNumber(num);
			if (userId == -1) {
				allUsersExist = false;
				break;
			}
			selectedUserIDs.push_back(userId);
		}

		if (!allUsersExist) {
			userNotFoundLabel->show();
			return;
		}

		// Create the group
		createGroupChat(selectedUserIDs);

		// Reset UI
		for (auto& button : btn) {
			QString bgColor2 = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";
			QString hoverColor2 = (users[currentUserID]->theme == 1) ? "#dce9e2" : "#e0e4e2";

			button->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QPushButton:hover {
        background-color: %2;
    }
    QLabel {
        color: rgba(34,32,35,110);
        background: transparent;
    }
    QLabel#numberLabel {
        color: rgba(34, 32, 35, 255);
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(0, 0, 0, 110); /* Change to rgba(34, 32, 35, 110) after testing */
        background: transparent;
    }
)").arg(bgColor2).arg(hoverColor2));
		}
		selectedContacts.clear();
		btn.clear();
		QLayoutItem* item;
		while ((item = layout->takeAt(0)) != nullptr) {
			if (QWidget* widget = item->widget()) {
				delete widget;
			}
			delete item;
		}
		popUpContacts2->hide();
		popUpContactsName2->show();
		});

	//add gc name
	QObject::connect(popNameOKButton2, &QPushButton::clicked, [=]() {
		if (popUpNameField2->text().isEmpty()) {
			GCNameEmptyLabel->show();
		}
		else {
			for (auto& user : users) {
				for (auto& room : user.second->chatRooms) {
					if (room.type() == "Group" && room.getChatRoomID() == maxChatID()) {
						room.gcName = popUpNameField2->text().toStdString();
						updateUsersToJson();
					}
				}
			}
			popUpContainer2->hide();
			container->hide();
			group_Screen(window);
		}
		});

	// Close pop-up
	QObject::connect(popCloseButton2, &QPushButton::clicked, [=]() {
		for (auto& button : btn) {
			QString bgColor2 = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";
			QString hoverColor2 = (users[currentUserID]->theme == 1) ? "#dce9e2" : "#e0e4e2";

			button->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QPushButton:hover {
        background-color: %2;
    }
    QLabel {
        color: rgba(34,32,35,110);
        background: transparent;
    }
    QLabel#numberLabel {
        color: rgba(34, 32, 35, 255);
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(0, 0, 0, 110); /* Change to rgba(34, 32, 35, 110) after testing */
        background: transparent;
    }
)").arg(bgColor2).arg(hoverColor2));
		}
		userNotFoundLabel->hide();
		groupExistsLabel->hide();
		minUsersLabel->hide();
		maxUsersLabel->hide();
		selectedContacts.clear();
		popUpContainer2->hide();
		});


	// Navigation
	QObject::connect(story_Button, &QPushButton::clicked, [=]() {
		container->hide();
		btn.clear();
		QLayoutItem* item;
		while ((item = layout->takeAt(0)) != nullptr) {
			if (QWidget* widget = item->widget()) {
				delete widget;
			}
			delete item;
		}
		selectedContacts.clear();
		project_Gui::story_Screen(window);
		});

	QObject::connect(settings_Button, &QPushButton::clicked, [=]() {
		container->hide();
		btn.clear();
		QLayoutItem* item;
		while ((item = layout->takeAt(0)) != nullptr) {
			if (QWidget* widget = item->widget()) {
				delete widget;
			}
			delete item;
		}
		selectedContacts.clear();
		project_Gui::setting_Screen(window);
		});

	QObject::connect(home_Button, &QPushButton::clicked, [=]() {
		container->hide();
		btn.clear();
		QLayoutItem* item;
		while ((item = layout->takeAt(0)) != nullptr) {
			if (QWidget* widget = item->widget()) {
				delete widget;
			}
			delete item;
		}
		selectedContacts.clear();
		project_Gui::chat_Screen(window);
		});

	QObject::connect(Button4, &QPushButton::clicked, [=]() {
		popUpContainer2->show();
		});

	// Theme
	if (users[currentUserID]->theme == 1) {
		popLabel2->setStyleSheet("color: #31473a; background: transparent;");
		leftBar->setStyleSheet("background-color: #31473a; border: none;");

		group_Button->setStyleSheet(R"(
            QToolButton {
                color: white;
                background: none;
                background-color: #2f3f36;
                border: none;
            }
        )");
		searchField->setStyleSheet(R"(
            QLineEdit {
                background-color: #31473a;
                padding-left: 20px;
                border: none;
                border-radius: 7px;
                font-size: 15px;
                color: #eef4f2;
            }
        )");
		Button4->setStyleSheet(R"(
            background-color: #31473a;
            border: none;
            border-radius: 15px;
            color: #e4d9d7;
        )");
		leftBar->setStyleSheet("background-color: #31473a; border: none;");
		title->setStyleSheet("color: #31473a; background: transparent;");
		messageField->setStyleSheet(R"(
            QLineEdit {
                padding-left: 18px;
                border: none;
                border-radius: 7px;
                font-size: 14px;
                background: #4b6d59;
                color: #ffffff;
            }
        )");
		popAddButton2->setStyleSheet(R"(
    background-color: #31473a;
    border: none;
    border-radius: 7px;
    color: #e4d9d7;
)");
		popCloseButton2->setStyleSheet(R"(
    background-color: #31473a;
    border: none;
    border-radius: 7px;
    color: #e4d9d7;
)");
	}
	else {
		leftBar->setStyleSheet("background-color: #222023; border: none;");

		group_Button->setStyleSheet(R"(
            QToolButton {
                color: white;
                background: none;
                background-color: #2a272a;
                border: none;
            }
        )");
		searchField->setStyleSheet(R"(
            QLineEdit {
                background-color: #222023;
                padding-left: 20px;
                border: none;
                border-radius: 7px;
                font-size: 15px;
                color: #eef4f2;
            }
        )");
		Button4->setStyleSheet(R"(
            background-color: #222023;
            border: none;
            border-radius: 15px;
            color: #e4d9d7;
        )");
		leftBar->setStyleSheet("background-color: #222023; border: none;");
		title->setStyleSheet("color: #222023; background: transparent;");
		messageField->setStyleSheet(R"(
            QLineEdit {
                padding-left: 18px;
                border: none;
                border-radius: 7px;
                font-size: 14px;
                background: #2d2c2d;
                color: #ffffff;
            }
        )");

	}

	container->show();
}

void project_Gui::createGroupChat(const vector<int>& selectedUserIDs) {

	vector<int> sortedUserIDs = selectedUserIDs;
	sort(sortedUserIDs.begin(), sortedUserIDs.end());


	// Create new group chat room
	vector<int> allUserIDs = sortedUserIDs;
	allUserIDs.push_back(currentUserID);
	ChatRoom newGroup(maxChatID() + 1, allUserIDs);

	vector<string> avatarOptions = {
		"icons/gc1.jpg",
		"icons/gc2.jpg",
		"icons/gc3.jpg"
	};
	srand(static_cast<unsigned int>(time(nullptr)));
	int randomIndex = rand() % avatarOptions.size();
	newGroup.gcAvatar = avatarOptions[randomIndex];

	for (int userId : allUserIDs) {
		users[userId]->addChatRoom(newGroup);
	}

	updateUsersToJson();

}

int project_Gui::customized_chat(const QString& message, QWidget* parent, int chatRoomID) {
	cout << "In customized_chat function" << endl;

	QLabel* messagelabel = new QLabel(wrapMessage(message), parent);
	if (!messagelabel) {
		cout << "Error: QLabel creation failed!" << endl;
		return 0;
	}
	///////////////////SAMA////////////////SAMA///////////////SAMA////////////////
	QFont nameFont("Poppins", 14);
	messagelabel->setFont(nameFont);
	messagelabel->setWordWrap(true);
	int chatAreaWidth = 838; // From chatScrollArea geometry
	int labelWidth = 500; // From setFixedWidth below
	int marginRight = 10; // Desired padding from right
	int marginLeft = chatAreaWidth - labelWidth - marginRight; // Dynamically calculate
	QString styleSheet = "";
	if (users[currentUserID]->theme == 1) {
		styleSheet = QString(R"(
        color: white;
        background-color: #31473a;
        border: 1px solid #444;
        border-radius: 7px;
        padding: 10px;
        padding-bottom: 20px;
    )");
	}
	else {
		styleSheet = QString(R"(
        color: white;
        background-color: #222023;
        border: 1px solid #444;
        border-radius: 7px;
        padding: 10px;
        padding-bottom: 20px;
    )");
	}

	if (messagelabel->text().isEmpty()) {
		styleSheet += R"(
            min-height: 30px;
        )";
	}
	messagelabel->setStyleSheet(styleSheet + R"(
        /* Add "seen" text with initial style */
        ::after {
            content: "seen";
            position: absolute;
            bottom: 5px;
            right: 10px;
            font-family: Poppins;
            font-size: 10px;
            color: rgba(64, 64, 64, 0.8); /* Red with 80% opacity for unseen */
            background: transparent;
        }
    )");

	messagelabel->setStyleSheet(styleSheet);
	messagelabel->adjustSize();
	if (messagelabel->width() < 89) {
		messagelabel->setMinimumWidth(89);
	}
	messagelabel->setMinimumHeight(messagelabel->height() + 10);

	cout << "Message created for: " << message.toStdString() << " with stylesheet: " << styleSheet.toStdString() << endl;

	// Define currentTime once and reuse it
	QDateTime currentTime = QDateTime::currentDateTime();
	QString timeSent = currentTime.toString("HH:mm:ss");


	// Create new message with the same currentTime
	Message newMsg(maxMessID() + 1, currentUserID, message.toStdString());
	newMsg.dateSent = currentTime.toString("yyyy-MM-dd").toStdString();
	newMsg.timeSent = currentTime.toString("HH:mm:ss").toStdString();


	// Create timestamp label
	QString timeStr = timeSent.left(5); // Get HH:mm
	QTime time = QTime::fromString(timeStr, "HH:mm"); // Convert to QTime
	QString formattedTime = time.toString("h:mm AP"); // Convert to 12-hour format with AM/PM
	QLabel* timestampLabel = new QLabel(formattedTime, messagelabel);
	QFont timestampFont("Poppins", 8);
	timestampLabel->setFont(timestampFont);
	timestampLabel->setStyleSheet(R"(
		color: rgba(135, 135, 135, 127);
        background: transparent;
        padding: 0px;
        qproperty-alignment: AlignLeft;
		border: none;
    )");
	timestampLabel->adjustSize();
	timestampLabel->move(messagelabel->width() - timestampLabel->width() - 28, messagelabel->height() - timestampLabel->height() - 4);


	QString iconPath = (newMsg.status == "seen") ? "icons/Doublecheck2.png" : "icons/Doublecheck.png";
	QLabel* seenLabel = new QLabel(messagelabel);
	QPixmap iconPixmap(iconPath);
	seenLabel->setPixmap(iconPixmap.scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	seenLabel->setStyleSheet("background: transparent; border: none;");
	seenLabel->adjustSize();
	seenLabel->move(messagelabel->width() - seenLabel->width() + 3, messagelabel->height() - timestampLabel->height() - 13);

	bool messageAdded = false;
	vector<Message> updatedMessages;
	for (ChatRoom& senderRoom : users[currentUserID]->chatRooms) {
		if (senderRoom.getChatRoomID() == chatRoomID) {
			senderRoom.addMesaages(newMsg);
			updatedMessages = senderRoom.getMessages(); // Get the updated messages vector

			// Update the other user's chat room with the same messages vector
			vector<int> ids = senderRoom.getUserIDs();
			for (int userId : ids) {
				if (userId == currentUserID) continue;
				for (ChatRoom& otherRoom : users[userId]->chatRooms) {
					if (otherRoom.getChatRoomID() == chatRoomID) {
						otherRoom.setMessages(updatedMessages);
						break;
					}
				}
			}
			messageAdded = true;
			break;
		}
	}
	if (messageAdded) {
		updateUsersToJson();
		// Add the new message to the layout
		QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(parent->layout());
		if (!layout) {
			layout = new QVBoxLayout(parent);
			layout->setAlignment(Qt::AlignTop);
			layout->setSpacing(5);
			layout->setContentsMargins(0, 0, 0, 0); // Ensure no extra padding
			parent->setLayout(layout);
		}

		// Create a container for the message, timestamp, and "seen" 
		QWidget* messageContainer = new QWidget(parent);
		QVBoxLayout* containerLayout = new QVBoxLayout(messageContainer);
		containerLayout->setContentsMargins(0, 0, 0, 0);
		containerLayout->setSpacing(2); // Spacing between message and timestamp/seen row

		// Add the message label to the container
		containerLayout->addWidget(messagelabel);

		// Create a horizontal layout for timestamp and seen label
		QWidget* bottomRow = new QWidget(messageContainer);
		QHBoxLayout* bottomLayout = new QHBoxLayout(bottomRow);
		bottomLayout->setContentsMargins(0, 0, 0, 0);
		bottomLayout->setSpacing(5); // Small spacing between timestamp and seen

		// Add the bottom row to the container layout
		containerLayout->addWidget(bottomRow);

		// Create a horizontal layout for alignment
		QWidget* alignmentContainer = new QWidget(parent);
		QHBoxLayout* alignmentLayout = new QHBoxLayout(alignmentContainer);
		alignmentLayout->setContentsMargins(0, 0, 0, 0);
		alignmentLayout->setSpacing(0);

		alignmentLayout->addStretch();
		alignmentLayout->addWidget(messageContainer);

		layout->addWidget(alignmentContainer);
		messagelabel->show();
		seenLabel->show();
		timestampLabel->show();
		cout << "Message label shown." << endl;
		return messagelabel->height() + 10;

	}
	delete messagelabel;
	delete seenLabel;
	delete timestampLabel;
	return 0;
	///////////////////////SAMA////SAMA////SAMA////SAMA////SAMA////SAMA////////////////////////////
}

int project_Gui::customized_group(const QString& message, QWidget* parent, int chatRoomID) {
	cout << "In customized_chat function" << endl;

	QLabel* messagelabel = new QLabel(wrapMessage(message), parent);
	if (!messagelabel) {
		cout << "Error: QLabel creation failed!" << endl;
		return 0;
	}
	///////////////////SAMA////////////////SAMA///////////////SAMA////////////////
	QFont nameFont("Poppins", 14);
	messagelabel->setFont(nameFont);
	messagelabel->setWordWrap(true);
	int chatAreaWidth = 838; // From chatScrollArea geometry
	int labelWidth = 500; // From setFixedWidth below
	int marginRight = 10; // Desired padding from right
	int marginLeft = chatAreaWidth - labelWidth - marginRight; // Dynamically calculate
	QString styleSheet = QString(R"(
        color: white;
        background-color: #222023;
        border: 1px solid #444;
        border-radius: 7px;
        padding: 10px;
        padding-bottom: 20px;
    )");

	if (messagelabel->text().isEmpty()) {
		styleSheet += R"(
            min-height: 30px;
        )";
	}
	messagelabel->setStyleSheet(styleSheet + R"(
        /* Add "seen" text with initial style */
        ::after {
            content: "seen";
            position: absolute;
            bottom: 5px;
            right: 10px;
            font-family: Poppins;
            font-size: 10px;
            color: rgba(64, 64, 64, 0.8); /* Red with 80% opacity for unseen */
            background: transparent;
        }
    )");

	messagelabel->setStyleSheet(styleSheet);
	messagelabel->adjustSize();
	if (messagelabel->width() < 89) {
		messagelabel->setMinimumWidth(89);
	}
	messagelabel->setMinimumHeight(messagelabel->height() + 10);

	cout << "Message created for: " << message.toStdString() << " with stylesheet: " << styleSheet.toStdString() << endl;

	// Define currentTime once and reuse it
	QDateTime currentTime = QDateTime::currentDateTime();
	QString timeSent = currentTime.toString("HH:mm:ss");


	// Create new message with the same currentTime
	Message newMsg(maxMessID() + 1, currentUserID, message.toStdString());
	newMsg.dateSent = currentTime.toString("yyyy-MM-dd").toStdString();
	newMsg.timeSent = currentTime.toString("HH:mm:ss").toStdString();


	// Create timestamp label
	QString timeStr = timeSent.left(5); // Get HH:mm
	QTime time = QTime::fromString(timeStr, "HH:mm"); // Convert to QTime
	QString formattedTime = time.toString("h:mm AP"); // Convert to 12-hour format with AM/PM
	QLabel* timestampLabel = new QLabel(formattedTime, messagelabel);
	QFont timestampFont("Poppins", 8);
	timestampLabel->setFont(timestampFont);
	timestampLabel->setStyleSheet(R"(
		color: rgba(135, 135, 135, 127);
        background: transparent;
        padding: 0px;
        qproperty-alignment: AlignLeft;
		border: none;
    )");
	timestampLabel->adjustSize();
	timestampLabel->move(messagelabel->width() - timestampLabel->width() - 28, messagelabel->height() - timestampLabel->height() - 4);


	QString iconPath = (newMsg.status == "seen") ? "icons/Doublecheck2.png" : "icons/Doublecheck.png";
	QLabel* seenLabel = new QLabel(messagelabel);
	QPixmap iconPixmap(iconPath);
	seenLabel->setPixmap(iconPixmap.scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	seenLabel->setStyleSheet("background: transparent; border: none;");
	seenLabel->adjustSize();
	seenLabel->move(messagelabel->width() - seenLabel->width() + 3, messagelabel->height() - timestampLabel->height() - 13);

	bool messageAdded = false;
	vector<Message> updatedMessages;
	for (ChatRoom& senderRoom : users[currentUserID]->chatRooms) {
		if (senderRoom.getChatRoomID() == chatRoomID) {
			senderRoom.addMesaages(newMsg);
			updatedMessages = senderRoom.getMessages(); 

			vector<int> ids = senderRoom.getUserIDs();
			for (int userId : ids) {
				if (userId == currentUserID) continue;
				for (ChatRoom& otherRoom : users[userId]->chatRooms) {
					if (otherRoom.getChatRoomID() == chatRoomID) {
						otherRoom.setMessages(updatedMessages); // Set the entire messages vector
						break;
					}
				}
			}
			messageAdded = true;
			break;
		}
	}
	if (messageAdded) {
		updateUsersToJson();
		// Add the new message to the layout
		QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(parent->layout());
		if (!layout) {
			layout = new QVBoxLayout(parent);
			layout->setAlignment(Qt::AlignTop);
			layout->setSpacing(5);
			layout->setContentsMargins(0, 0, 0, 0); // Ensure no extra padding
			parent->setLayout(layout);
		}

		// Create a container for the message, timestamp, and "seen" text
		QWidget* messageContainer = new QWidget(parent);
		QVBoxLayout* containerLayout = new QVBoxLayout(messageContainer);
		containerLayout->setContentsMargins(0, 0, 0, 0);
		containerLayout->setSpacing(2); // Spacing between message and timestamp/seen row

		// Add the message label to the container
		containerLayout->addWidget(messagelabel);

		// Create a horizontal layout for timestamp and "seen" label
		QWidget* bottomRow = new QWidget(messageContainer);
		QHBoxLayout* bottomLayout = new QHBoxLayout(bottomRow);
		bottomLayout->setContentsMargins(0, 0, 0, 0);
		bottomLayout->setSpacing(5); // Small spacing between timestamp and "seen"

		// Add the bottom row to the container layout
		containerLayout->addWidget(bottomRow);

		// Create a horizontal layout for alignment
		QWidget* alignmentContainer = new QWidget(parent);
		QHBoxLayout* alignmentLayout = new QHBoxLayout(alignmentContainer);
		alignmentLayout->setContentsMargins(0, 0, 0, 0);
		alignmentLayout->setSpacing(0);

		alignmentLayout->addStretch();
		alignmentLayout->addWidget(messageContainer);

		layout->addWidget(alignmentContainer);
		messagelabel->show();
		seenLabel->show();
		timestampLabel->show();
		cout << "Message label shown." << endl;
		return messagelabel->height() + 10;

	}
	delete messagelabel;
	delete seenLabel;
	delete timestampLabel;
	return 0;
	///////////////////////SAMA////SAMA////SAMA////SAMA////SAMA////SAMA////////////////////////////
}

QString project_Gui::wrapMessage(const QString& message, int wrapLength) {
	QString wrapped;
	for (int i = 0; i < message.length(); i += wrapLength) {
		wrapped += message.mid(i, wrapLength);
		if (i + wrapLength < message.length())
			wrapped += "\n";
	}
	return wrapped;
}

QPushButton* project_Gui::customized_setting(const QString& name, QWidget* parent, int y) {

	QWidget* container = new QWidget(parent);
	container->setGeometry(0, y, 400, 131);
	container->setStyleSheet("background-color: #eef4f2;");

	QPushButton* contactButton = new QPushButton(container);
	contactButton->setGeometry(0, 0, 400, 130);
	contactButton->setStyleSheet(R"(
        QPushButton {
            background-color: #eef4f2;
            text-align: left;
            border: none;
            padding-left: 70px;
            font-size: 20px;
            color: black;
        }
        QPushButton:hover {
            background-color: #dde3e1;
        }
    )");
	QWidget* Devider = new QWidget(container);
	Devider->setGeometry(43, 129, 300, 1);
	Devider->setStyleSheet("background-color: #d2d7d6; border: none;");

	contactButton->setText(name);

	return contactButton;
}

QPushButton* project_Gui::customized_Contact(QString name, QWidget* parent, int y, const QString& avatarPath = "") {

	QWidget* container = new QWidget(parent);
	container->setGeometry(0, y, 400, 81);
	container->setStyleSheet("background-color: #eef4f2;");

	QPushButton* contactButton = new QPushButton(container);
	contactButton->setGeometry(0, 0, 400, 80);
	contactButton->setStyleSheet(R"(
        QPushButton {
            background-color: #eef4f2;
            text-align: left;
            border: none;
            padding-left: 70px;
            padding-bottom: 17px;
            font-size: 20px;
            color: black;
        }
        QPushButton:hover {
            background-color: #eaedec;
        }
    )");
	contactButton->setObjectName("contactChatButton");
	QLabel* userContactBtnDev2 = new QLabel(contactButton);
	userContactBtnDev2->setGeometry(43, 80, 380, 1);
	userContactBtnDev2->setStyleSheet("background-color: #dde3e1; margin-left: 60px;");
	userContactBtnDev2->setObjectName("userDev2");


	contactButton->setText(name);

	QLabel* avatar = new QLabel(contactButton);
	avatar->setGeometry(18, 20, 42, 42);
	avatar->setObjectName("chatAvatar");
	avatar->setStyleSheet("background-color: transparent; border-radius: 20px;");

	

	// Optional avatar image
	if (!avatarPath.isEmpty()) {
		QPixmap pixmap(avatarPath);
		QPixmap roundedPixmap(pixmap.size());
		roundedPixmap.fill(Qt::transparent);

		QPainter painter(&roundedPixmap);
		painter.setRenderHint(QPainter::Antialiasing);
		QPainterPath path;
		path.addEllipse(0, 0, pixmap.width(), pixmap.height());
		painter.setClipPath(path);
		painter.drawPixmap(0, 0, pixmap);
		painter.end();

		avatar->setPixmap(roundedPixmap.scaled(42, 42, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
		avatar->setStyleSheet("border-radius: 20px;");
	}
	///////////////////////SAMA////SAMA////SAMA////SAMA////SAMA////SAMA////////////////////////////
	// Add a label for the most recent message
	QLabel* messageLabel = new QLabel(contactButton);
	messageLabel->setObjectName("messageLabel");
	messageLabel->setGeometry(70, 42, 240, 20);
	QFont messageFont("Poppins", 10);
	messageLabel->setFont(messageFont);
	messageLabel->setStyleSheet("color: rgb(171, 171, 171); background: transparent;");

	QLabel* messageLabelTime = new QLabel(contactButton);
	messageLabelTime->setObjectName("messageLabelTime");
	messageLabelTime->setGeometry(305, 42, 60, 20);
	messageLabelTime->setFont(messageFont);
	messageLabelTime->setAlignment(Qt::AlignRight);
	messageLabelTime->setStyleSheet("color: rgb(171, 171, 171); background: transparent;");
	///////////////////////SAMA////SAMA////SAMA////SAMA////SAMA////SAMA////////////////////////////

	return contactButton;
}

QPushButton* project_Gui::customized_Story(QString name, QWidget* parent, const QString& avatarPath) {
	QPushButton* button = new QPushButton(parent);
	button->setFixedSize(380, 73);
	button->setStyleSheet(R"(
        QPushButton {
            background-color: #eef4f2;
            text-align: left;
            border: none;
            padding-left: 70px;
            font-size: 20px;
            color: black;
        }
        QPushButton:hover {
            background-color: #eaedec;
        }
    )");
	button->setText(name);

	// Add divider
	QWidget* divider = new QWidget(button);
	divider->setGeometry(43, 70, 300, 0);
	divider->setStyleSheet("background-color: #d2d7d6; border: none;");

	// Add avatar
	QLabel* avatar = new QLabel(button);
	avatar->setGeometry(14, 19, 42, 42);
	avatar->setObjectName("storyAvatar");
	avatar->setStyleSheet("background-color: transparent; border-radius: 20px;");
	if (!avatarPath.isEmpty()) {
		QPixmap pixmap(avatarPath);
		QPixmap scaledPixmap = pixmap.scaled(42, 42, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

		QPixmap finalPixmap(42, 42);
		finalPixmap.fill(Qt::transparent);

		QPainter painter(&finalPixmap);
		painter.setRenderHint(QPainter::Antialiasing);

		QPainterPath path;
		path.addEllipse(0, 0, 42, 42);
		painter.setClipPath(path);

		painter.drawPixmap(0, 0, scaledPixmap);

		painter.setClipping(false);

		// Draw the light gray circle border
		QPen blackPen(QColor("#eef4f2"));
		blackPen.setWidth(3);
		painter.setPen(blackPen);
		painter.setBrush(Qt::NoBrush);
		painter.drawEllipse(2, 2, 38, 38);

		// Draw the green gradient "guardian" border
		QConicalGradient gradient(21, 21, 0);
		gradient.setColorAt(0.0, QColor("#A9A9A9"));

		QPen greenPen(QBrush(gradient), 2);
		painter.setPen(greenPen);
		painter.setBrush(Qt::NoBrush);
		painter.drawEllipse(1, 1, 40, 40);

		painter.end();
		avatar->setPixmap(finalPixmap);
	}


	return button;
}

QPushButton* project_Gui::customizedPop_Contact(int number, QString name, QWidget* parent, int y) {

	QWidget* container = new QWidget(parent);
	container->setGeometry(0, y, 400, 35);
	container->setStyleSheet("background-color: #eef4f2;");

	QFont popFont("Poppins", 13, QFont::Bold);
	QFont popFont2("Poppins", 13);

	QPushButton* contactButton = new QPushButton(container);
	contactButton->setGeometry(20, 4, 358, 30);
	QString bgColor = (users[currentUserID]->theme == 1) ? "#d3e4dc" : "#d4d9d7";
	QString hoverColor = (users[currentUserID]->theme == 1) ? "#dce9e2" : "#e0e4e2";

	contactButton->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        text-align: left;
        border: none;
        padding-left: 10px;
    }
    QPushButton:hover {
        background-color: %2;
    }
    QLabel {
        color: rgba(34,32,35,110);
        background: transparent;
    }
    QLabel#numberLabel {
        color: rgba(34, 32, 35, 255);
        background: transparent;
    }
    QLabel#nameLabel {
        color: rgba(0, 0, 0, 110); /* Change to rgba(34, 32, 35, 110) after testing */
        background: transparent;
    }
)").arg(bgColor).arg(hoverColor));


	QString Qnumber = QString::fromStdString(to_string(number));

	// Create label for the NUMBER (left)
	QLabel* numberLabel = new QLabel(contactButton);
	numberLabel->setGeometry(10, 0, 150, 30); // x=10, width=150
	numberLabel->setFont(popFont);
	numberLabel->setText("+20" + Qnumber);
	numberLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	numberLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
	numberLabel->setObjectName("numberLabel");

	// Create label for the NAME (right)
	QLabel* nameLabel = new QLabel(contactButton);
	nameLabel->setObjectName("nameLabel");
	nameLabel->setGeometry(160, 0, 188, 30); // shifted to the right
	nameLabel->setFont(popFont2);
	nameLabel->setText("~" + name);
	nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	nameLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

	return contactButton;
}

vector<Message>project_Gui::sortMessagesBySentTime(const vector<Message>& messages) {
	vector<Message> sortedMessages = messages;
	sort(sortedMessages.begin(), sortedMessages.end(), [](const Message& a, const Message& b) {
		// Parse date and time into QDateTime for comparison
		QDateTime aTime = QDateTime::fromString(
			QString::fromStdString(a.dateSent + " " + a.timeSent),
			"yyyy-MM-dd HH:mm"
		);
		QDateTime bTime = QDateTime::fromString(
			QString::fromStdString(b.dateSent + " " + b.timeSent),
			"yyyy-MM-dd HH:mm"
		);
		return aTime < bTime;
		});
	return sortedMessages;
}
 
void project_Gui::deleteMessage(int messageId, QWidget* alignmentContainer, int chatRoomID) {
	bool messageDeleted = false;
	for (auto& [userId, user] : users) {
		for (ChatRoom& room : user->chatRooms) {
			if (room.getChatRoomID() == chatRoomID) {
				room.removeMessage(messageId); 
				messageDeleted = true;
			}
		}
	}

	if (messageDeleted) {
		updateUsersToJson();
		if (alignmentContainer) {
			alignmentContainer->deleteLater();
		}
		cout << "Message with ID " << messageId << " deleted." << endl;
	}
	else {
		cout << "Message with ID " << messageId << " not found!" << endl;
	}
	///////////////////////SAMA////SAMA////SAMA////SAMA////SAMA////SAMA/////////////////////////
}

void project_Gui::removeExpiredStories() {
	QDateTime currentTime = QDateTime::currentDateTime();

	for (auto& pair : users) {
		User* user = pair.second;
		if (!user->story.publishedTime.empty()) {
			QDateTime publishedTime = QDateTime::fromString(QString::fromStdString(user->story.publishedTime), "yyyy-MM-dd hh:mm:ss");
			if (publishedTime.isValid() && publishedTime.secsTo(currentTime) > 86400) {
				user->story.content.clear();
				user->story.photoPath.clear();
				user->story.publishedTime.clear();
				user->story.viewers.clear();
				cout << "Expired story deleted for user: " << pair.first << endl;
			}
		}
	}

	updateUsersToJson();
}

