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

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = NULL);
};

#endif // PROFILE_H
