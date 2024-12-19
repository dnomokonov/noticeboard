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
#include <QString>
#include <QStringList>
#include <QShowEvent>

#include "mainwindow.h"

class listAdverts : public QWidget
{
    Q_OBJECT

public:
    explicit listAdverts(MainWindow *mainWindow, QWidget *parent = NULL);
    void setFilters(const QString &searchWords, const QStringList &categories, const QString &location);
    void updateFiltersAndReload();

protected:
    void showEvent(QShowEvent *event) override;

private:
    MainWindow *mainWindow;
    KeeperData* keeper = mainWindow->getKeeperData();
    QString searchWords;
    QStringList categories;
    QString location;

    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QGridLayout *contentLayout;

    void updateContent(const QString &searchWords, const QStringList &categories, const QString &location);
    void clearLayout(QLayout *layout);
};

#endif // LISTADVERTS_H
