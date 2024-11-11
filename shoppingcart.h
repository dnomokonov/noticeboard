#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QWidget>
#include <QFile>
#include <QVBoxLayout>
#include <QLabel>

class shoppingcart : public QWidget
{
    Q_OBJECT

public:
    explicit shoppingcart(QWidget *parent = NULL);
};

#endif // SHOPPINGCART_H
