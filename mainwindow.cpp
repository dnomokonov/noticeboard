#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "createadvertising.h"
#include "favourites.h"
#include "shoppingcart.h"
#include "profile.h"
#include "adsfound.h"
#include "listadverts.h"
#include "viewingad.h" // временное решение

#include <QDebug>

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

    QWidget *header = new QWidget(this);
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    header->setFixedHeight(80);
    header->setObjectName("header");

    QPushButton *logo = new QPushButton(this);
    logo->setObjectName("onlyIconButton");
    logo->setFixedSize(200, 30);

    QPixmap logoPixmap(":/biz/logo");
    QIcon logoPixmapIcon(logoPixmap);
    logo->setIcon(logoPixmapIcon);
    logo->setIconSize(QSize(200, 30));

    header->setContentsMargins(50, 0, 0, 0);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);
    headerLayout->addWidget(logo, 0, Qt::AlignLeft);

    QWidget *controlPanel = new QWidget(header);
    QHBoxLayout *controlPanelLayout = new QHBoxLayout(controlPanel);

    // category, search, geo
    QPixmap iconMenu(":/icons/burgermenu");
    QIcon categoryButtonIcon(iconMenu);

    QPushButton *categoryButton = new QPushButton(controlPanel);
    categoryButton->setObjectName("customIconBtn");
    categoryButton->setFixedSize(30, 30);
    categoryButton->setIcon(categoryButtonIcon);

    QLineEdit *searchInput = new QLineEdit(controlPanel);
    searchInput->setObjectName("searchInput");
    searchInput->setPlaceholderText("Поиск...");

    QPushButton *searchButton = new QPushButton("Найти", controlPanel);
    searchButton->setObjectName("customBtn");
    searchButton->setFixedSize(80, 30);
    searchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton *geoButton = new QPushButton(controlPanel);
    geoButton->setObjectName("onlyIconButton");

    QPixmap iconGeo(":/icons/geo");
    QIcon geoButtonIcon(iconGeo);

    geoButton->setIcon(geoButtonIcon);
    geoButton->setIconSize(QSize(18, 22));

    controlPanelLayout->addWidget(categoryButton);
    controlPanelLayout->addSpacing(5);
    controlPanelLayout->addWidget(searchInput);
    controlPanelLayout->addWidget(searchButton);
    controlPanelLayout->addWidget(geoButton);

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

    QPushButton *favBtn = new QPushButton(userPanel);
    QPushButton *shopbagBtn = new QPushButton(userPanel);
    QPushButton *profileBtn = new QPushButton(userPanel);

    favBtn->setObjectName("onlyIconButton");
    shopbagBtn->setObjectName("onlyIconButton");
    profileBtn->setObjectName("onlyIconButton");

    QPixmap iconFav(":/icons/likes");
    QPixmap iconShopbag(":/icons/shopbag");
    QPixmap iconProfile(":/icons/profile");

    QIcon favButtonIcon(iconFav);
    QIcon shopbagButtonIcon(iconShopbag);
    QIcon profileButtonIcon(iconProfile);

    favBtn->setFixedSize(30, 30);
    shopbagBtn->setFixedSize(30, 30);
    profileBtn->setFixedSize(30, 30);

    favBtn->setIcon(favButtonIcon);
    shopbagBtn->setIcon(shopbagButtonIcon);
    profileBtn->setIcon(profileButtonIcon);
    favBtn->setIconSize(QSize(24, 22));
    shopbagBtn->setIconSize(QSize(22, 22));
    profileBtn->setIconSize(QSize(22, 22));

    userPanelLayout->addWidget(favBtn);
    userPanelLayout->addSpacing(4);
    userPanelLayout->addWidget(shopbagBtn);
    userPanelLayout->addSpacing(4);
    userPanelLayout->addWidget(profileBtn);

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

    listAdverts *allAdvertsList = new listAdverts();
    createadvertising *createAdComponent = new createadvertising(this, this);
    favourites *favouritesComponent = new favourites();
    shoppingcart *shoppingcartComponent = new shoppingcart();
    profile *profileComponent = new profile();

    stackedWidget->addWidget(allAdvertsList);
    stackedWidget->addWidget(createAdComponent);
    stackedWidget->addWidget(profileComponent);
    stackedWidget->addWidget(favouritesComponent);
    stackedWidget->addWidget(shoppingcartComponent);


    bodyLayout->addWidget(stackedWidget);
    body->setLayout(bodyLayout);

    // <--- Dialog's --->

    QDialog *citySelectDialog = new QDialog(this);
    citySelectDialog->setObjectName("citySelectDialog");
    citySelectDialog->setWindowTitle("Выбор города");
    //citySelectDialog->setModal(true);
    citySelectDialog->setFixedSize(200, 140);

    QGridLayout *cityDialogLayout = new QGridLayout(citySelectDialog);

    QLabel *citySelectLabel = new QLabel("Выберите свой город", citySelectDialog);
    citySelectLabel->setObjectName("citySelectLabel");
    QComboBox *citySelectCombo = new QComboBox(citySelectDialog);
    citySelectCombo->setObjectName("categoryCustom");
    citySelectCombo->setFixedWidth(150);
    citySelectCombo->addItems(
        {
            "Москва",
            "Новосибирск",
            "Омск",
            "Санкт-Петербург",
            "Нижний Новгород",
            "Краснодар",
            "Чита",
            "Красноярск",
            "Якутск",
            "Благовещенск",
            "Хабаровск"
        }
    );

    QPushButton *btnCityDialog = new QPushButton("Сохранить", citySelectDialog);
    btnCityDialog->setObjectName("defaultColorButton");
    btnCityDialog->setFixedSize(110, 30);

    cityDialogLayout->addWidget(citySelectLabel, 0, 0, Qt::AlignCenter);
    cityDialogLayout->addWidget(citySelectCombo, 1, 0, Qt::AlignCenter);
    cityDialogLayout->setSpacing(12);
    cityDialogLayout->addWidget(btnCityDialog, 2, 0, Qt::AlignCenter);


    // <--- Grid Layout Add's --->
    gridLayout->addWidget(header, 0, 0, 1, 2);
    gridLayout->addWidget(body, 1, 0);
    gridLayout->setRowStretch(1, 1);


    // <--- Connects --->
    connect(logo, &QPushButton::clicked, this, [=]() {
        qDebug() << "Hello, allAdvertsList!";
        stackedWidget->setCurrentWidget(allAdvertsList);
    });

    connect(btnAddNotice, &QPushButton::clicked, this, [=]() {
        qDebug() << "Hello, btnAddNotice!";
        stackedWidget->setCurrentWidget(createAdComponent);
    });

    connect(favBtn, &QPushButton::clicked, this, [=]() {
        qDebug() << "Hello, favBtn!";
        stackedWidget->setCurrentWidget(favouritesComponent);
    });

    connect(shopbagBtn, &QPushButton::clicked, this, [=]() {
        qDebug() << "Hello, shopbagBtn!";
        stackedWidget->setCurrentWidget(shoppingcartComponent);
    });

    connect(profileBtn, &QPushButton::clicked, this, [=]() {
        qDebug() << "Hello, profileBtn!";
        stackedWidget->setCurrentWidget(profileComponent);
    });

    connect(geoButton, &QPushButton::clicked, this, [=]() {
        citySelectDialog->exec();
    });

    connect(btnCityDialog, &QPushButton::clicked, citySelectDialog, [=]{
        locationCityNow = citySelectCombo->currentText();
        citySelectDialog->accept();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStackedWidget* MainWindow::getStackedWidget() {
    return stackedWidget;
}
