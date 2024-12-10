#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QDialog>
#include <QComboBox>
#include <QListWidget>
#include <QStringList>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "keeperdata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStackedWidget* getStackedWidget();
    KeeperData *getKeeperData();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    QString locationCityNow = "none";
    KeeperData* keeper = new KeeperData();
    bool connectToDatabase();
    void openWindowAuth();
};
#endif // MAINWINDOW_H
