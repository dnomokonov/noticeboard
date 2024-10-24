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

    // Header

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

    // Body

    QWidget *body = new QWidget(this);
    QHBoxLayout *bodyLayout = new QHBoxLayout(body);

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    stackedWidget->setObjectName("blockFormAuth");
    stackedWidget->setFixedSize(540, 690);

    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(stackedWidget, Qt::AlignCenter);
    bodyLayout->addLayout(centerLayout);

    gridLayout->addWidget(body, 1, 0);
    gridLayout->setRowStretch(1, 1);
}

AuthWindow::~AuthWindow()
{
    delete ui;
}
