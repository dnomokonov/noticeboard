#include "authwindow.h"
#include "ui_authwindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFile>

AuthWindow::AuthWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthWindow)
{
    ui->setupUi(this);

    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    if (connectToDatabase()) {
        qDebug() << "Connect successfully!";
    }

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QGridLayout *gridLayout = new QGridLayout(centralWidget);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(0);

    QWidget *header = new QWidget(this);
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    header->setFixedHeight(80);

    QLabel *logoLabel = new QLabel(this);
    QPixmap logoPixmap(":/biz/logo");
    logoLabel->setPixmap(logoPixmap);
    logoLabel->setFixedSize(200, 30);
    logoLabel->setScaledContents(true);

    header->setContentsMargins(50, 0, 0, 0);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);
    header->setStyleSheet("background-color: #F5F5F5;");
    headerLayout->addWidget(logoLabel, 0, Qt::AlignLeft);
    gridLayout->addWidget(header, 0, 0, 1, 2);

    QWidget *body = new QWidget(this);
    QVBoxLayout *bodyLayout = new QVBoxLayout(body);
    bodyLayout->setAlignment(Qt::AlignCenter);

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    stackedWidget->setObjectName("blockFormAuth");
    stackedWidget->setFixedSize(540, 580);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(stackedWidget);
    bodyLayout->addLayout(centerLayout);

    // <--- Login --->

    QWidget *loginPage = new QWidget();
    QVBoxLayout *loginLayout = new QVBoxLayout(loginPage);
    loginLayout->setAlignment(Qt::AlignCenter);

    QLabel *headerLoginName = new QLabel("Вход");
    headerLoginName->setObjectName("headerName");

    QLineEdit *loginUsernameField = new QLineEdit(loginPage);
    QLineEdit *loginPasswordField = new QLineEdit(loginPage);
    loginPasswordField->setEchoMode(QLineEdit::Password);

    loginUsernameField->setPlaceholderText("Username");
    loginPasswordField->setPlaceholderText("Password");

    loginUsernameField->setObjectName("defaultField");
    loginPasswordField->setObjectName("defaultField");

    QHBoxLayout *headerFormLayout = new QHBoxLayout();
    headerFormLayout->addStretch();
    headerFormLayout->addWidget(headerLoginName);
    headerFormLayout->addStretch();

    QPushButton *loginBtn = new QPushButton("Войти", loginPage);
    loginBtn->setObjectName("defaultColorButton");
    loginBtn->setFixedSize(200, 32);

    QPushButton *switchToRegisterBtn = new QPushButton("Регистрация", loginPage);
    switchToRegisterBtn->setObjectName("defaultColorButton");
    switchToRegisterBtn->setFixedSize(200, 32);

    QHBoxLayout *loginBtnLayout = new QHBoxLayout();
    loginBtnLayout->addStretch();
    loginBtnLayout->addWidget(loginBtn);
    loginBtnLayout->addStretch();
    QHBoxLayout *registerBtnLayout = new QHBoxLayout();
    registerBtnLayout->addStretch();
    registerBtnLayout->addWidget(switchToRegisterBtn);
    registerBtnLayout->addStretch();

    loginLayout->addLayout(headerFormLayout);
    loginLayout->addWidget(loginUsernameField);
    loginLayout->addWidget(loginPasswordField);
    loginLayout->addLayout(loginBtnLayout);
    loginLayout->addLayout(registerBtnLayout);

    stackedWidget->addWidget(loginPage);

    // <--- Registration --->

    QWidget *registerPage = new QWidget(stackedWidget);
    QVBoxLayout *registerLayout = new QVBoxLayout(registerPage);
    registerLayout->setAlignment(Qt::AlignCenter);

    QLabel *headerRegisterName = new QLabel("Регистрация");
    headerRegisterName->setObjectName("headerName");

    QLineEdit *registerNameField = new QLineEdit(registerPage);
    QLineEdit *registerSurnameField = new QLineEdit(registerPage);
    QLineEdit *registerUsernameField = new QLineEdit(registerPage);
    QLineEdit *registerPasswordField = new QLineEdit(registerPage);
    QLineEdit *confirmPasswordField = new QLineEdit(registerPage);

    registerNameField->setPlaceholderText("Имя");
    registerSurnameField->setPlaceholderText("Фамилия");
    registerUsernameField->setPlaceholderText("Имя пользователя");
    registerPasswordField->setPlaceholderText("Пароль");
    confirmPasswordField->setPlaceholderText("Повторите пароль");
    registerPasswordField->setEchoMode(QLineEdit::Password);
    confirmPasswordField->setEchoMode(QLineEdit::Password);

    registerNameField->setObjectName("defaultField");
    registerSurnameField->setObjectName("defaultField");
    registerUsernameField->setObjectName("defaultField");
    registerPasswordField->setObjectName("defaultField");
    confirmPasswordField->setObjectName("defaultField");

    QHBoxLayout *headerFormRegLayout = new QHBoxLayout();
    headerFormRegLayout->addStretch();
    headerFormRegLayout->addWidget(headerRegisterName);
    headerFormRegLayout->addStretch();

    QPushButton *registerBtn = new QPushButton("Зарегистрироваться", registerPage);
    registerBtn->setObjectName("defaultColorButton");
    registerBtn->setFixedSize(200, 32);

    QPushButton *switchToLoginBtn = new QPushButton("Вход", registerPage);
    switchToLoginBtn->setObjectName("defaultColorButton");
    switchToLoginBtn->setFixedSize(200, 32);

    QHBoxLayout *regbtnLayout = new QHBoxLayout();
    QHBoxLayout *logbtnLayout = new QHBoxLayout();

    regbtnLayout->addStretch();
    regbtnLayout->addWidget(registerBtn);
    regbtnLayout->addStretch();

    logbtnLayout->addStretch();
    logbtnLayout->addWidget(switchToLoginBtn);
    logbtnLayout->addStretch();

    registerLayout->addLayout(headerFormRegLayout);
    registerLayout->addWidget(registerNameField);
    registerLayout->addWidget(registerSurnameField);
    registerLayout->addWidget(registerUsernameField);
    registerLayout->addWidget(registerPasswordField);
    registerLayout->addWidget(confirmPasswordField);
    registerLayout->addLayout(regbtnLayout);
    registerLayout->addLayout(logbtnLayout);

    stackedWidget->addWidget(registerPage);
    gridLayout->addWidget(body, 1, 0);
    gridLayout->setRowStretch(1, 1);

    // <--- Connects --->

    connect(loginBtn, &QPushButton::clicked, this, [=]{
        QString username = loginUsernameField->text();
        QString password = loginPasswordField->text();

        if (username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Заполните все поля");
            return;
        }

        QSqlQuery query;
        query.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (!query.exec() || !query.next()) {
            QMessageBox::warning(this, "Ошибка", "Неправильный логин или пароль.");
        } else {
            QMessageBox::information(this, "Успех", "Добро пожаловать, " + query.value("name").toString() + "!");

        }
    });

    connect(registerBtn, &QPushButton::clicked, this, [=]{
        QString username = registerUsernameField->text();
        QString password = registerPasswordField->text();
        QString confirmPassword = confirmPasswordField->text();
        QString name = registerNameField->text();
        QString surname = registerSurnameField->text();

        if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty() || name.isEmpty() || surname.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля");
            return;
        }

        if (confirmPassword != password) {
            QMessageBox::warning(this, "Ошибка", "Пароли не совпадают");
            return;
        }

        QSqlQuery query;
        query.prepare("INSERT INTO Users (username, password, name, surname) VALUES (:username, :password, :name, :surname)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.bindValue(":name", name);
        query.bindValue(":surname", surname);

        if (!query.exec()) {
            QMessageBox::warning(this, "Ошибка", "Ошибка регистрации: " + query.lastError().text());
        } else {
            QMessageBox::information(this, "Успех", "Регистрация прошла успешно.");
            stackedWidget->setCurrentWidget(loginPage);
        }
    });

    connect(switchToRegisterBtn, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(registerPage);
    });

    connect(switchToLoginBtn, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(loginPage);
    });
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

bool AuthWindow::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbPath = QCoreApplication::applicationDirPath() + "../../../noticeboard.db";
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
        return false;
    }

    qDebug() << "База данных успешно подключена!";

    return true;
}
