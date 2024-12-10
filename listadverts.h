#ifndef LISTADVERTS_H
#define LISTADVERTS_H

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>
#include <QBuffer>
#include <QScrollArea>

#include "mainwindow.h"

class listAdverts : public QWidget
{
    Q_OBJECT

public:
    explicit listAdverts(MainWindow *mainWindow, QWidget *parent = NULL);

private:
    MainWindow *mainWindow;
    KeeperData* keeper = mainWindow->getKeeperData();
};

#endif // LISTADVERTS_H
