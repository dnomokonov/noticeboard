#ifndef FAVOURITES_H
#define FAVOURITES_H

#include <QWidget>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>

class favourites : public QWidget
{
    Q_OBJECT

public:
    explicit favourites(QWidget *parent = NULL);
};

#endif // FAVOURITES_H
