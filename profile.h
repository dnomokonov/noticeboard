#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QStackedWidget>
#include <QStyle>
#include <string>
#include <QScrollArea>

#include "mainwindow.h"

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(MainWindow *mainWindow, QWidget *parent = NULL);

protected:
    void showEvent(QShowEvent *event) override;

private:
    MainWindow *mainWindow;
    KeeperData *keeper = mainWindow->getKeeperData();
    QPixmap createRoundedPixmap(const QPixmap &src, int radius);

    int countSales = 0;

    QWidget *scrollContent;
    QGridLayout *contentLayout;

    QWidget *scrollArchiveContent;
    QGridLayout *contentArchiveLayout;

    void updateSales();
    void loadActiveAnnouncements();
    void loadArchiveAnnouncements();
};

#endif // PROFILE_H
