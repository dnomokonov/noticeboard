#include "keeperdata.h"

// Receipt data

QString KeeperData::getUsername() {
    return username;
}

QString KeeperData::getNamePerson() {
    return namePerson;
}

QString KeeperData::getSurnamePerson() {
    return surnamePerson;
}

QPixmap KeeperData::getUserAvatar() {
    return userAvatar;
}

bool KeeperData::getAuthStatus() {
    return isAuthPerson;
}

QString KeeperData::getCurrentLocation() {
    return locationCityNow;
}

// Change data

void KeeperData::setUsername(QString newUsername) {
    username = newUsername;
}

void KeeperData::setNamePerson(QString newName) {
    namePerson = newName;
}

void KeeperData::setSurnamePerson(QString newSurname) {
    surnamePerson = newSurname;
}

void KeeperData::setUserAvatar(QPixmap newAvatar) {
    userAvatar = newAvatar;
}

void KeeperData::setAuthStatus(bool newAuthStatus) {
    isAuthPerson = newAuthStatus;
}

void KeeperData::setCurrentLocation(QString newGeo) {
    locationCityNow = newGeo;
}
