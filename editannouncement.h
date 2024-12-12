#ifndef EDITANNOUNCEMENT_H
#define EDITANNOUNCEMENT_H

#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>

#include "mainwindow.h"

class EditAnnouncement : public QWidget
{
    Q_OBJECT

public:
    explicit EditAnnouncement(MainWindow *mainWindow, QWidget *parent = NULL);
    void setIDAnnouncement(int id);

protected:
    void showEvent(QShowEvent *event) override;

private:
    MainWindow *mainWindow;
    int currentID;
    void loadAnnouncementData();
    void updateContent();
    void saveAnnouncementData();
    void deleteAnnouncementData();
    void archiveAnnouncementData();

    QLineEdit *titleEdit;
    QTextEdit *descriptionEdit;
    QComboBox *categoryCombo;
    QLineEdit *priceEdit;
    QLineEdit *phoneEdit;
    QLineEdit *cityEdit;
    QLineEdit *streetEdit;
    QLineEdit *houseEdit;
    QLabel *imageDisplay;
};

#endif // EDITANNOUNCEMENT_H
