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
    KeeperData *keeper = new KeeperData();
    QPixmap createRoundedPixmap(const QPixmap &src, int radius);
    void loadAnnouncements(QWidget* container, bool isActive);

    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QGridLayout *contentLayout;
};

#endif // PROFILE_H
