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

#include "keeperdata.h"

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = NULL);

private:
    KeeperData *keeper = new KeeperData();

    QPixmap createRoundedPixmap(const QPixmap &src, int radius);
};

#endif // PROFILE_H
