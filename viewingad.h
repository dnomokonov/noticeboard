#ifndef VIEWINGAD_H
#define VIEWINGAD_H

#include <QWidget>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>

#include "mainwindow.h"

class viewingad : public QWidget
{
    Q_OBJECT

public:
    explicit viewingad(MainWindow *mainWindow, QWidget *parent = NULL);
    void loadAdData(int announcementID);

private:
    MainWindow *mainWindow;
    KeeperData* keeper = mainWindow->getKeeperData();

    QLabel *titleLabel;
    QLabel *descriptionLabel;
    QLabel *costLabel;
    QLabel *phoneLabel;
    QLabel *categoryLabel;
    QLabel *locationLabel;
    QLabel *photoLabel;
    QWidget *sellerWidget;
    QGridLayout *sellerLayout;
    QLabel *sellerHeader;
    QGridLayout *sellerBlock;
    QLabel *sellerFullName;
    QGridLayout *starsGridLayout;

    QPixmap createRoundedPixmap(const QPixmap &src, int radius);

};

#endif // VIEWINGAD_H
