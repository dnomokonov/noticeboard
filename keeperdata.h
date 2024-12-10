#ifndef KEEPERDATA_H
#define KEEPERDATA_H

#include <QString>
#include <QList>
#include <QPixmap>
#include <QStringList>
#include <QSettings>

class KeeperData
{
public:
    KeeperData(int user_id = 0, QString usname = "username", QString nameper = "user", QString sunameper = "surname", double rating = 0, int salesCount = 0, bool authStatus = false, QString locationNow = "Moscow") {
        userID = user_id;
        username = usname;
        namePerson = nameper;
        surnamePerson = sunameper;
        ratingUser = rating;
        salesUser = salesCount;
        isAuthPerson = authStatus;
        locationCityNow = locationNow;

        loadFromSettings();
    }

// Receipt data
    int getUserID();
    QString getUsername();
    QString getNamePerson();
    QString getSurnamePerson();
    double getRatingUser();
    int getSalesUser();
    QPixmap getUserAvatar();
    bool getAuthStatus();
    QString getCurrentLocation();
    QStringList getSelectedCategories();

// Change data
    void setUserID(int newID);
    void setUsername(QString newUsername);
    void setNamePerson(QString newName);
    void setSurnamePerson(QString newSurname);
    void setRatingUser(double newRating);
    void setSalesUser(int newSalesCount);
    void setUserAvatar(QPixmap newAvatar);
    void setAuthStatus(bool newAuthStatus);
    void setCurrentLocation(QString newGeo);
    void setSelectedCategories(QStringList newSelected);

// Settings
    void loadFromSettings();
    void saveToSettings();

private:
// Info about user
    int userID;
    QString username;
    QString namePerson;
    QString surnamePerson;
    double ratingUser;
    int salesUser;
    QPixmap userAvatar;
    bool isAuthPerson;
// Info about user select geo or categories
    QString locationCityNow;
    QStringList selectedCategories;

};

#endif // KEEPERDATA_H
