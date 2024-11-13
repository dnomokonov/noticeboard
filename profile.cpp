#include "profile.h"

profile::profile(QWidget *parent) : QWidget(parent) {
    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QGridLayout *gridLayout = new QGridLayout(this);

    QWidget *personBlock = new QWidget(this);
    QWidget *personeAdversBlock = new QWidget(this);

    personBlock->setStyleSheet("background-color: #f5f5f5;");
    personeAdversBlock->setStyleSheet("background-color: #e0e0e0;");

    gridLayout->addWidget(personBlock, 0, 0);
    gridLayout->addWidget(personeAdversBlock, 1, 0);

    gridLayout->setRowStretch(0, 1);
    gridLayout->setRowStretch(1, 2);
    gridLayout->setColumnStretch(0, 1);

}
