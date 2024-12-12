#ifndef FAVOURITES_H
#define FAVOURITES_H

#include <QWidget>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QSqlQuery>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"

class favourites : public QWidget
{
    Q_OBJECT

public:
    explicit favourites(MainWindow *mainWindow, QWidget *parent = NULL);

protected:
    void showEvent(QShowEvent *event) override;

private:
    MainWindow *mainWindow;
    KeeperData* keeper = mainWindow->getKeeperData();

    QVBoxLayout *mainLayout;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QGridLayout *contentLayout;
    void updateContent();
};

#endif // FAVOURITES_H
