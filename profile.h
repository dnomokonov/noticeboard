#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>

class profile : public QWidget
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = NULL);
};

#endif // PROFILE_H
