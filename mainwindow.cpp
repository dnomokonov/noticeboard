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

    QWidget *controlPanel = new QWidget(header);
    QHBoxLayout *controlPanelLayout = new QHBoxLayout(controlPanel);

    // category, search, geo
    QLabel *searchIconLabel = new QLabel(controlPanel);
    searchIconLabel->setPixmap(QPixmap(":/icons/search"));
    searchIconLabel->setFixedSize(20, 20);
    searchIconLabel->setScaledContents(true);

    QLineEdit *searchInput = new QLineEdit(controlPanel);
    searchInput->setFixedHeight(30);
    searchInput->setPlaceholderText("Search...");
    searchInput->setStyleSheet("border: 2px solid #8000FF; border-radius: 15px; padding-left: 10px;");

    QPushButton *searchButton = new QPushButton("Найти", controlPanel);
    searchButton->setFixedSize(80, 30);
    searchButton->setStyleSheet("background-color: #8000FF; color: white; border-radius: 15px;");

    controlPanelLayout->addWidget(searchIconLabel);
    controlPanelLayout->addWidget(searchInput);
    controlPanelLayout->addWidget(searchButton);

    headerLayout->addWidget(controlPanel, 1, Qt::AlignCenter);

    //bagshop, favourite, profile


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
