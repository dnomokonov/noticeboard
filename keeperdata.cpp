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

QStringList KeeperData::getSelectedCategories() {
    return selectedCategories;
}

// Change data

void KeeperData::setUsername(QString newUsername) {
    username = newUsername;
    saveToSettings();
}

void KeeperData::setNamePerson(QString newName) {
    namePerson = newName;
    saveToSettings();
}

void KeeperData::setSurnamePerson(QString newSurname) {
    surnamePerson = newSurname;
    saveToSettings();
}

void KeeperData::setUserAvatar(QPixmap newAvatar) {
    userAvatar = newAvatar;
    saveToSettings();
}

void KeeperData::setAuthStatus(bool newAuthStatus) {
    isAuthPerson = newAuthStatus;
    saveToSettings();
}

void KeeperData::setCurrentLocation(QString newGeo) {
    locationCityNow = newGeo;
    saveToSettings();
}

void KeeperData::setSelectedCategories(QStringList newSelected) {
    selectedCategories = newSelected;
    saveToSettings();
}

// Settings

void KeeperData::loadFromSettings() {
    QSettings settings("bydn", "noticeboard");

    username = settings.value("username", username).toString();
    namePerson = settings.value("namePerson", namePerson).toString();
    surnamePerson = settings.value("surnamePerson", surnamePerson).toString();
    isAuthPerson = settings.value("isAuthPerson", isAuthPerson).toBool();
    locationCityNow = settings.value("locationCityNow", locationCityNow).toString();
    selectedCategories = settings.value("selectedCategories", selectedCategories).toStringList();
}

void KeeperData::saveToSettings() {
    QSettings settings("bydn", "noticeboard");

    settings.setValue("username", username);
    settings.setValue("namePerson", namePerson);
    settings.setValue("surnamePerson", surnamePerson);
    settings.setValue("isAuthPerson", isAuthPerson);
    settings.setValue("locationCityNow", locationCityNow);
    settings.setValue("selectedCategories", selectedCategories);
}
