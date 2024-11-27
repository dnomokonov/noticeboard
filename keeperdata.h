#ifndef KEEPERDATA_H
#define KEEPERDATA_H

#include <QString>
#include <QList>
#include <QPixmap>

class KeeperData
{
public:
    KeeperData(QString usname = "username", QString nameper = "user", QString sunameper = "surname", bool authStatus = false, QString locationNow = "Moscow") {
        username = usname;
        namePerson = nameper;
        surnamePerson = sunameper;
        isAuthPerson = authStatus;
        locationCityNow = locationNow;
    };

// Receipt data
    QString getUsername();
    QString getNamePerson();
    QString getSurnamePerson();
    QPixmap getUserAvatar();
    bool getAuthStatus();
    QString getCurrentLocation();

// Change data
    void setUsername(QString newUsername);
    void setNamePerson(QString newName);
    void setSurnamePerson(QString newSurname);
    void setUserAvatar(QPixmap newAvatar);
    void setAuthStatus(bool newAuthStatus);
    void setCurrentLocation(QString newGeo);

private:
// Info about user
    QString username;
    QString namePerson;
    QString surnamePerson;
    QPixmap userAvatar;
    bool isAuthPerson;

// Info about user select geo or categories
    QString locationCityNow;
    QList<QString> selectedCategories;

};

#endif // KEEPERDATA_H
