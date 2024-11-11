#include "viewingad.h"

viewingad::viewingad(QWidget *parent) : QWidget(parent) {
    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Viewing ad", this);

    layout->addWidget(label);
    setLayout(layout);
}
