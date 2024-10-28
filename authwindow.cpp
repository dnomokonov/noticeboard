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

    QLabel *headerLoginName = new QLabel("Login");
    headerLoginName->setObjectName("headerName");

    QLineEdit *loginUsernameField = new QLineEdit(loginPage);
    QLineEdit *loginPasswordField = new QLineEdit(loginPage);

    loginUsernameField->setPlaceholderText("Username");
    loginPasswordField->setPlaceholderText("Password");

    loginUsernameField->setObjectName("defaultField");
    loginPasswordField->setObjectName("defaultField");

    QHBoxLayout *headerFormLayout = new QHBoxLayout();
    headerFormLayout->addStretch();
    headerFormLayout->addWidget(headerLoginName);
    headerFormLayout->addStretch();

    QPushButton *loginBtn = new QPushButton("Login", loginPage);
    loginBtn->setObjectName("authBtn");
    loginBtn->setFixedSize(250, 30);

    QPushButton *switchToRegisterBtn = new QPushButton("Sign Up", loginPage);
    switchToRegisterBtn->setObjectName("authBtn");
    switchToRegisterBtn->setFixedSize(250, 30);

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

    QLabel *headerRegisterName = new QLabel("Register");
    headerRegisterName->setObjectName("headerName");

    QLineEdit *registerNameField = new QLineEdit(registerPage);
    QLineEdit *registerSurnameField = new QLineEdit(registerPage);
    QLineEdit *registerMiddleNameField = new QLineEdit(registerPage);
    QLineEdit *registerUsernameField = new QLineEdit(registerPage);
    QLineEdit *registerPasswordField = new QLineEdit(registerPage);
    QLineEdit *confirmPasswordField = new QLineEdit(registerPage);

    registerNameField->setPlaceholderText("Name");
    registerSurnameField->setPlaceholderText("Surname");
    registerMiddleNameField->setPlaceholderText("MiddleName");
    registerUsernameField->setPlaceholderText("Username");
    registerPasswordField->setPlaceholderText("Password");
    confirmPasswordField->setPlaceholderText("Confirm Password");
    registerPasswordField->setEchoMode(QLineEdit::Password);
    confirmPasswordField->setEchoMode(QLineEdit::Password);

    registerNameField->setObjectName("defaultField");
    registerSurnameField->setObjectName("defaultField");
    registerMiddleNameField->setObjectName("defaultField");
    registerUsernameField->setObjectName("defaultField");
    registerPasswordField->setObjectName("defaultField");
    confirmPasswordField->setObjectName("defaultField");

    QHBoxLayout *headerFormRegLayout = new QHBoxLayout();
    headerFormRegLayout->addStretch();
    headerFormRegLayout->addWidget(headerRegisterName);
    headerFormRegLayout->addStretch();

    QPushButton *registerBtn = new QPushButton("Register", registerPage);
    registerBtn->setFixedSize(250, 30);

    QPushButton *switchToLoginBtn = new QPushButton("Back to Login", registerPage);
    switchToLoginBtn->setFixedSize(250, 30);

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
    registerLayout->addWidget(registerMiddleNameField);
    registerLayout->addWidget(registerUsernameField);
    registerLayout->addWidget(registerPasswordField);
    registerLayout->addWidget(confirmPasswordField);
    registerLayout->addLayout(regbtnLayout);
    registerLayout->addLayout(logbtnLayout);

    stackedWidget->addWidget(registerPage);
    gridLayout->addWidget(body, 1, 0);
    gridLayout->setRowStretch(1, 1);

    // <--- Connects --->

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
