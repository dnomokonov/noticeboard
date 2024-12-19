#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFile>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

private:
    Ui::AuthWindow *ui;
    bool connectToDatabase();
    void openMainWindowUI();
};

#endif // AUTHWINDOW_H
