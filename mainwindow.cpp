#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "createadvertising.h"
#include "favourites.h"
#include "shoppingcart.h"
#include "profile.h"
#include "listadverts.h"
#include "viewingad.h"
#include "authwindow.h"
#include "editannouncement.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    keeper->loadFromSettings();

    if (connectToDatabase()) {
        qDebug() << "Connect successfully!";
    }

    if (keeper->getAuthStatus()) {
        QString username = keeper->getUsername();
        qDebug() << "Загружен пользователь:" << username;

        QSqlQuery query;
        query.prepare("SELECT id, name, surname, rating, sales FROM Users WHERE username = :username");
        query.bindValue(":username", username);

        if (query.exec() && query.next()) {
            int id_user = query.value("id").toInt();
            QString name = query.value("name").toString();
            QString surname = query.value("surname").toString();
            double ratingUser = query.value("rating").toDouble();
            int salesCount = query.value("sales").toInt();

            keeper->setUserID(id_user);
            keeper->setNamePerson(name);
            keeper->setSurnamePerson(surname);
            keeper->setRatingUser(ratingUser);
            keeper->setSalesUser(salesCount);

        } else {
            qDebug() << "Не удалось загрузить данные пользователя:" << query.lastError().text();
        }
    }

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

    listAdverts *allAdvertsList = new listAdverts(this, this);
    createadvertising *createAdComponent = new createadvertising(this, this);
    favourites *favouritesComponent = new favourites(this, this);
    shoppingcart *shoppingcartComponent = new shoppingcart(this, this);
    profile *profileComponent = new profile(this, this);
    viewingad *viewAnnouncement = new viewingad(this, this);
    EditAnnouncement *editPage = new EditAnnouncement(this, this);

    stackedWidget->addWidget(allAdvertsList); // 0
    stackedWidget->addWidget(createAdComponent); // 1
    stackedWidget->addWidget(profileComponent); // 2
    stackedWidget->addWidget(favouritesComponent); // 3
    stackedWidget->addWidget(shoppingcartComponent); // 4
    stackedWidget->addWidget(viewAnnouncement); // 5
    stackedWidget->addWidget(editPage); // 6

    bodyLayout->addWidget(stackedWidget);
    body->setLayout(bodyLayout);

    // <--- Dialog's --->

    QDialog *categoriesDialog = new QDialog(this);
    categoriesDialog->setWindowTitle("Категории");
    categoriesDialog->setFixedSize(320, 250);

    QGridLayout *categDialogLayout = new QGridLayout(categoriesDialog);

    QLabel *categSelectLabel = new QLabel("Выбирите категории товаров", categoriesDialog);
    categSelectLabel->setObjectName("categSelectLabel");

    QListWidget *listCategories = new QListWidget();
    listCategories->setObjectName("customQListWidget");
    QStringList categories = {"Электроника", "Одежда", "Дом и сад", "Авто", "Недвижимость", "Услуги"};
    listCategories->setSelectionMode(QAbstractItemView::MultiSelection);
    listCategories->addItems(categories);

    QHBoxLayout *btnCategDialogLayout = new QHBoxLayout(categoriesDialog);

    QPushButton *saveCategSelect = new QPushButton("Применить", categoriesDialog);
    saveCategSelect->setObjectName("defaultColorButton");
    saveCategSelect->setFixedSize(120, 30);

    QPushButton *clearCategSelect = new QPushButton("Очистить", categoriesDialog);
    clearCategSelect->setObjectName("defaultButton");
    clearCategSelect->setFixedSize(120, 30);

    btnCategDialogLayout->addWidget(saveCategSelect, 0);
    btnCategDialogLayout->addWidget(clearCategSelect, 1);

    categDialogLayout->addWidget(categSelectLabel, 0, 0);
    categDialogLayout->addWidget(listCategories, 1, 0);
    categDialogLayout->addLayout(btnCategDialogLayout, 2, 0, Qt::AlignCenter);

    QDialog *citySelectDialog = new QDialog(this);
    citySelectDialog->setObjectName("citySelectDialog");
    citySelectDialog->setWindowTitle("Геолокация");
    citySelectDialog->setFixedSize(220, 150);

    QGridLayout *cityDialogLayout = new QGridLayout(citySelectDialog);

    QLabel *citySelectLabel = new QLabel("Выберите город", citySelectDialog);
    citySelectLabel->setObjectName("citySelectLabel");
    QComboBox *citySelectCombo = new QComboBox(citySelectDialog);
    citySelectCombo->setObjectName("categoryCustom");
    citySelectCombo->setFixedWidth(180);
    citySelectCombo->setMaxVisibleItems(5);
    citySelectCombo->addItems(
        {
            "Все города",
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

    QPushButton *btnCityDialog = new QPushButton("Применить", citySelectDialog);
    QPushButton *btnCityClearDialog = new QPushButton("Отмена", citySelectDialog);

    btnCityDialog->setObjectName("defaultColorButton");
    btnCityDialog->setFixedSize(90, 35);
    btnCityClearDialog->setObjectName("defaultButton");
    btnCityClearDialog->setFixedSize(90, 35);

    cityDialogLayout->addWidget(citySelectLabel, 0, 0, 1, 2, Qt::AlignCenter);
    cityDialogLayout->addWidget(citySelectCombo, 1, 0, 1, 2, Qt::AlignCenter);
    cityDialogLayout->setSpacing(10);
    cityDialogLayout->addWidget(btnCityDialog, 2, 0, Qt::AlignRight);
    cityDialogLayout->addWidget(btnCityClearDialog, 2, 1, Qt::AlignLeft);

    // <--- Grid Layout Add's --->
    gridLayout->addWidget(header, 0, 0, 1, 2);
    gridLayout->addWidget(body, 1, 0);
    gridLayout->setRowStretch(1, 1);


    // <--- Connects --->
    connect(logo, &QPushButton::clicked, this, [=]() {
        QStringList categories;

        listAdverts* allAdvertsList = qobject_cast<listAdverts*>(stackedWidget->widget(0));
        if (allAdvertsList) {
            allAdvertsList->setFilters("", categories, "");
            allAdvertsList->updateFiltersAndReload();
        }

        stackedWidget->setCurrentWidget(allAdvertsList);
    });

    connect(btnAddNotice, &QPushButton::clicked, this, [=]() {
        if (keeper->getAuthStatus()) {
            stackedWidget->setCurrentWidget(createAdComponent);
        } else {
            openWindowAuth();
            this->close();
        }
    });

    connect(favBtn, &QPushButton::clicked, this, [=]() {
        if (keeper->getAuthStatus()) {
            stackedWidget->setCurrentWidget(favouritesComponent);
        } else {
            openWindowAuth();
            this->close();
        }
    });

    connect(shopbagBtn, &QPushButton::clicked, this, [=]() {
        if (keeper->getAuthStatus()) {
            stackedWidget->setCurrentWidget(shoppingcartComponent);
        } else {
            openWindowAuth();
            this->close();
        }
    });

    connect(profileBtn, &QPushButton::clicked, this, [=]() {
        if (keeper->getAuthStatus()) {
            stackedWidget->setCurrentWidget(profileComponent);
        } else {
            openWindowAuth();
            this->close();
        }
    });

    connect(geoButton, &QPushButton::clicked, this, [=]() {
        citySelectDialog->exec();
    });

    connect(btnCityDialog, &QPushButton::clicked, citySelectDialog, [=]{
        locationCityNow = citySelectCombo->currentText();

        keeper->setCurrentLocation(locationCityNow);

        citySelectDialog->accept();
    });

    connect(btnCityClearDialog, &QPushButton::clicked, citySelectDialog, [=]{
        locationCityNow = "Все города";
        citySelectCombo->setCurrentIndex(0);

        keeper->setCurrentLocation(locationCityNow);

        citySelectDialog->accept();
    });

    connect(categoryButton, &QPushButton::clicked, this, [=]{
        categoriesDialog->exec();
    });

    connect(saveCategSelect, &QPushButton::clicked, categoriesDialog, [=]{
        QList<QListWidgetItem *> selectedItems = listCategories->selectedItems();
        QStringList selectedCategories;

        for (QListWidgetItem *item : selectedItems) {
            selectedCategories << item->text();
        }

        keeper->setSelectedCategories(selectedCategories);

        categoriesDialog->accept();
    });

    connect(clearCategSelect, &QPushButton::clicked, categoriesDialog, [=]{
        listCategories->clearSelection();
    });

    connect(searchButton, &QPushButton::clicked, this, [=]() {
        QString searchWords = searchInput->text();
        QString location = citySelectCombo->currentText();

        if (location == "Все города") {
            location = "";
        }

        QStringList categories;
        for (int i = 0; i < listCategories->count(); ++i) {
            QListWidgetItem *item = listCategories->item(i);
            if (item->checkState() == Qt::Checked) {
                categories.append(item->text());
            }
        }

        if (allAdvertsList) {
            allAdvertsList->setFilters(searchWords, categories, location);
            allAdvertsList->updateFiltersAndReload();
        }

        stackedWidget->setCurrentWidget(allAdvertsList);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
    delete keeper;

    // QSettings settings("bydn", "noticeboard");
    // settings.clear();
}

QStackedWidget* MainWindow::getStackedWidget() {
    return stackedWidget;
}

bool MainWindow::connectToDatabase() {
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

void MainWindow::openWindowAuth() {
    AuthWindow *authWindow = new AuthWindow();
    authWindow->show();
}

KeeperData* MainWindow::getKeeperData() {
    return keeper;
}
