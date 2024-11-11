#include "profile.h"

profile::profile(QWidget *parent) : QWidget(parent) {
    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Profile", this);

    layout->addWidget(label);
    setLayout(layout);
}
