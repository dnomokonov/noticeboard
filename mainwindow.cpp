#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    // <--- Header --->

    QWidget *header = new QWidget(this);
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    header->setFixedHeight(80);
    header->setObjectName("header");

    QLabel *logoLabel = new QLabel(this);
    QPixmap logoPixmap(":/biz/logo");
    logoLabel->setPixmap(logoPixmap);
    logoLabel->setFixedSize(200, 30);
    logoLabel->setScaledContents(true);

    header->setContentsMargins(50, 0, 0, 0);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);
    headerLayout->addWidget(logoLabel, 0, Qt::AlignLeft);

    QWidget *controlPanel = new QWidget(header);
    QHBoxLayout *controlPanelLayout = new QHBoxLayout(controlPanel);

    // category, search, geo
    QPixmap iconMenu(":/icons/burgermenu");
    QIcon categoryButtonIcon(iconMenu);

    QPushButton *categoryButton = new QPushButton(controlPanel);
    categoryButton->setObjectName("customIconBtn");
    categoryButton->setFixedSize(30, 30);
    categoryButton->setIcon(iconMenu);

    QLineEdit *searchInput = new QLineEdit(controlPanel);
    searchInput->setObjectName("searchInput");
    searchInput->setPlaceholderText("Search...");

    QPushButton *searchButton = new QPushButton("Найти", controlPanel);
    searchButton->setObjectName("customBtn");
    searchButton->setFixedSize(80, 30);
    searchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel *geoBtnLabel = new QLabel(controlPanel);
    geoBtnLabel->setPixmap(QPixmap(":/icons/geo"));
    geoBtnLabel->setFixedSize(18, 22);
    geoBtnLabel->setScaledContents(true);

    controlPanelLayout->addWidget(categoryButton);
    controlPanelLayout->addWidget(searchInput);
    controlPanelLayout->addWidget(searchButton);
    controlPanelLayout->addWidget(geoBtnLabel);

    // btn add notice
    QWidget *btnAdd = new QWidget(header);
    QHBoxLayout *btnAddLayout = new QHBoxLayout(btnAdd);

    QPushButton *btnAddNotice = new QPushButton("Разместить объявление", btnAdd);
    btnAddNotice->setFixedSize(200, 30);
    btnAddNotice->setObjectName("customBtn");

    btnAddLayout->addWidget(btnAddNotice);

    //bagshop, favourite, profile
    QWidget *userPanel = new QWidget(header);
    QHBoxLayout *userPanelLayout = new QHBoxLayout(userPanel);
    userPanel->setContentsMargins(0, 0, 50, 0);

    QLabel *favBtnLabel = new QLabel(userPanel);
    QLabel *shopbagBtnLabel = new QLabel(userPanel);
    QLabel *profileBtnnLabel = new QLabel(userPanel);

    favBtnLabel->setPixmap(QPixmap(":/icons/likes"));
    shopbagBtnLabel->setPixmap(QPixmap(":/icons/shopbag"));
    profileBtnnLabel->setPixmap(QPixmap(":/icons/profile"));

    favBtnLabel->setFixedSize(24, 22);
    shopbagBtnLabel->setFixedSize(22, 22);
    profileBtnnLabel->setFixedSize(22, 22);
    favBtnLabel->setScaledContents(true);
    shopbagBtnLabel->setScaledContents(true);
    profileBtnnLabel->setScaledContents(true);

    userPanelLayout->addWidget(favBtnLabel);
    userPanelLayout->addSpacing(16);
    userPanelLayout->addWidget(shopbagBtnLabel);
    userPanelLayout->addSpacing(16);
    userPanelLayout->addWidget(profileBtnnLabel);

    headerLayout->addSpacing(50);
    headerLayout->addWidget(controlPanel, 1, Qt::AlignCenter);
    headerLayout->addStretch();
    headerLayout->addWidget(btnAdd, 0, Qt::AlignRight);
    headerLayout->addStretch();
    headerLayout->addWidget(userPanel, 0, Qt::AlignRight);

    // <--- Body --->

    QWidget *body = new QWidget(this);
    QVBoxLayout *bodyLayout = new QVBoxLayout(body);
    bodyLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->setAlignment(Qt::AlignCenter);
    bodyLayout->addLayout(centerLayout);


    // <--- Grid Layout Add's --->
    gridLayout->addWidget(header, 0, 0, 1, 2);
    gridLayout->addWidget(body, 1, 0);
    gridLayout->setRowStretch(1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
