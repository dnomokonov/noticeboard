#ifndef CREATEADVERTISING_H
#define CREATEADVERTISING_H

#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>

#include <QDebug>

#include "mainwindow.h"

class createadvertising : public QWidget
{
    Q_OBJECT

public:
    explicit createadvertising(QWidget *parent = NULL, MainWindow *mainwindow = NULL);

private:
    MainWindow *mainWindow;
    KeeperData* keeper = mainWindow->getKeeperData();
};

#endif // CREATEADVERTISING_H
