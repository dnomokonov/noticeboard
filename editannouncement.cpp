#include "editannouncement.h"

EditAnnouncement::EditAnnouncement(MainWindow *mainWindow, QWidget *parent)
    : mainWindow(mainWindow), QWidget(parent)
{
    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QWidget *mainContainer = new QWidget(this);
    mainContainer->setFixedSize(1300, 640);
    mainContainer->setObjectName("blockCreateAd");
    QGridLayout *gridLayout = new QGridLayout(mainContainer);

    QLabel *titleLabel = new QLabel("Заголовок:");
    titleLabel->setObjectName("titleLabelCreateBlock");

    titleEdit = new QLineEdit();
    titleEdit->setFixedWidth(550);
    titleEdit->setObjectName("customFieldCreateAd");
    titleEdit->setPlaceholderText("Введите заголовок объявления");

    QLabel *descriptionLabel = new QLabel("Описание:");
    descriptionLabel->setObjectName("titleLabelCreateBlock");

    descriptionEdit = new QTextEdit();
    descriptionEdit->setFixedWidth(550);
    descriptionEdit->setObjectName("customFieldCreateAd");
    descriptionEdit->setPlaceholderText("Введите описание объявления");

    QLabel *categoryLabel = new QLabel("Категория:");
    categoryLabel->setObjectName("titleLabelCreateBlock");

    categoryCombo = new QComboBox();
    categoryCombo->setObjectName("categoryCustom");
    categoryCombo->setFixedWidth(200);
    categoryCombo->addItems({"Электроника", "Одежда", "Дом и сад", "Авто", "Недвижимость", "Услуги"});

    QLabel *priceLabel = new QLabel("Цена:");
    priceLabel->setObjectName("titleLabelCreateBlock");

    priceEdit = new QLineEdit();
    priceEdit->setFixedWidth(550);
    priceEdit->setObjectName("customFieldCreateAd");
    priceEdit->setPlaceholderText("Введите цену");

    QDoubleValidator *validator = new QDoubleValidator(0, 1000000, 2, this);
    validator->setLocale(QLocale::C);
    QLocale locale = QLocale(QLocale::Russian);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    validator->setLocale(locale);
    priceEdit->setValidator(validator);

    QLabel *phoneLabel = new QLabel("Номер телефона:");
    phoneLabel->setObjectName("titleLabelCreateBlock");

    phoneEdit = new QLineEdit();
    phoneEdit->setMaxLength(12);
    phoneEdit->setFixedWidth(550);
    phoneEdit->setObjectName("customFieldCreateAd");
    phoneEdit->setPlaceholderText("Введите номер телефона");

    QLabel *addressLabel = new QLabel("Адрес:");
    addressLabel->setObjectName("titleLabelCreateBlock");

    cityEdit = new QLineEdit();
    cityEdit->setFixedWidth(225);
    cityEdit->setObjectName("customFieldCreateAd");
    cityEdit->setPlaceholderText("Город");

    streetEdit = new QLineEdit();
    streetEdit->setFixedWidth(225);
    streetEdit->setObjectName("customFieldCreateAd");
    streetEdit->setPlaceholderText("Улица");

    houseEdit = new QLineEdit();
    houseEdit->setFixedWidth(80);
    houseEdit->setObjectName("customFieldCreateAd");
    houseEdit->setPlaceholderText("Дом");

    QHBoxLayout *addressLayout = new QHBoxLayout();
    addressLayout->addWidget(cityEdit);
    addressLayout->addSpacing(10);
    addressLayout->addWidget(streetEdit);
    addressLayout->addSpacing(10);
    addressLayout->addWidget(houseEdit);

    gridLayout->addWidget(titleLabel, 0, 0);
    gridLayout->addWidget(titleEdit, 1, 0);

    gridLayout->addWidget(descriptionLabel, 2, 0);
    gridLayout->addWidget(descriptionEdit, 3, 0);

    gridLayout->addWidget(categoryLabel, 4, 0);
    gridLayout->addWidget(categoryCombo, 5, 0);

    gridLayout->addWidget(priceLabel, 6, 0);
    gridLayout->addWidget(priceEdit, 7, 0);

    gridLayout->addWidget(phoneLabel, 8, 0);
    gridLayout->addWidget(phoneEdit, 9, 0);

    gridLayout->addWidget(addressLabel, 10, 0);
    gridLayout->addLayout(addressLayout, 11, 0, Qt::AlignLeft);

    imageDisplay = new QLabel();
    imageDisplay->setObjectName("uploadImageBlock");
    imageDisplay->setFixedSize(400, 400);
    imageDisplay->setAlignment(Qt::AlignCenter);

    QPushButton *uploadImageButton = new QPushButton("Загрузить изображение");
    uploadImageButton->setObjectName("uploadButton");
    uploadImageButton->setFixedSize(200, 35);

    QSpacerItem *rightSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(rightSpacer, 1, 2, 11, 1);
    gridLayout->addWidget(imageDisplay, 1, 1, 11, 1, Qt::AlignCenter);
    gridLayout->addWidget(uploadImageButton, 12, 1, Qt::AlignCenter);

    QHBoxLayout *bntControlLayout = new QHBoxLayout();
    bntControlLayout->setSpacing(10);

    QPushButton *submitButton = new QPushButton("Сохранить");
    submitButton->setFixedSize(120, 35);
    submitButton->setObjectName("createAdButton");

    QPushButton *archiveButton = new QPushButton("Архив");
    archiveButton->setFixedSize(100, 35);
    archiveButton->setObjectName("clearButton");

    bntControlLayout->addWidget(submitButton);
    bntControlLayout->addWidget(archiveButton);

    QPushButton *deleteButton = new QPushButton("Удалить");
    deleteButton->setFixedSize(100, 35);
    deleteButton->setObjectName("cancelButton");

    gridLayout->addLayout(bntControlLayout, 12, 0, Qt::AlignLeft);
    gridLayout->addWidget(deleteButton, 12, 0, Qt::AlignRight);

    gridLayout->setHorizontalSpacing(30);
    gridLayout->setVerticalSpacing(10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(mainContainer, Qt::AlignCenter, Qt::AlignCenter);
    mainLayout->addLayout(centerLayout);
    setLayout(mainLayout);

    connect(submitButton, &QPushButton::clicked, this, [=]() {
        saveAnnouncementData();

        QStackedWidget* stackedWidget = mainWindow->getStackedWidget();
        stackedWidget->setCurrentIndex(4);
    });

    connect(archiveButton, &QPushButton::clicked, this, [=]() {
        archiveAnnouncementData();

        QStackedWidget* stackedWidget = mainWindow->getStackedWidget();
        stackedWidget->setCurrentIndex(4);
    });

    connect(deleteButton, &QPushButton::clicked, this, [=]() {
        deleteAnnouncementData();

        QStackedWidget* stackedWidget = mainWindow->getStackedWidget();
        stackedWidget->setCurrentIndex(4);
    });

    loadAnnouncementData();
}

void EditAnnouncement::setIDAnnouncement(int id) {
    this->currentID = id;
}

void EditAnnouncement::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    loadAnnouncementData();
}

void EditAnnouncement::loadAnnouncementData() {
    qDebug() << this->currentID;

    if (this->currentID <= 0) return;

    QSqlQuery query;
    query.prepare("SELECT title, description, category, cost, phone, location, photo FROM Announcements WHERE id = :id");
    query.bindValue(":id", this->currentID);

    if (!query.exec() || !query.next()) {
        qDebug() << "Ошибка загрузки данных объявления:" << query.lastError().text();
        return;
    }

    QString title = query.value("title").toString();
    QString description = query.value("description").toString();
    QString category = query.value("category").toString();
    double cost = query.value("cost").toDouble();
    QString phone = query.value("phone").toString();
    QStringList location = query.value("location").toString().split(",");
    QByteArray photoData = query.value("photo").toByteArray();

    titleEdit->setText(title);
    descriptionEdit->setPlainText(description);
    categoryCombo->setCurrentText(category);
    priceEdit->setText(QString::number(cost, 'f', 2));
    phoneEdit->setText(phone);

    if (location.size() >= 3) {
        cityEdit->setText(location.at(0).trimmed());
        streetEdit->setText(location.at(1).trimmed());
        houseEdit->setText(location.at(2).trimmed());
    }

    QPixmap pixmap;
    if (pixmap.loadFromData(photoData)) {
        imageDisplay->setPixmap(pixmap.scaled(imageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageDisplay->setText("Нет изображения");
    }
}

void EditAnnouncement::saveAnnouncementData() {
    if (this->currentID <= 0) return;

    int isActive = 1;

    QSqlQuery query;
    query.prepare("UPDATE Announcements SET title = :title, description = :description, category = :category, cost = :cost, phone = :phone, active = :active, location = :location, photo = :photo WHERE id = :id");
    query.bindValue(":title", titleEdit->text());
    query.bindValue(":description", descriptionEdit->toPlainText());
    query.bindValue(":category", categoryCombo->currentText());
    query.bindValue(":cost", priceEdit->text().toDouble());
    query.bindValue(":phone", phoneEdit->text());
    query.bindValue(":active", isActive);

    QString location = QString("%1, %2, %3")
                           .arg(cityEdit->text().trimmed())
                           .arg(streetEdit->text().trimmed())
                           .arg(houseEdit->text().trimmed());
    query.bindValue(":location", location);

    QPixmap pixmap = imageDisplay->pixmap(Qt::ReturnByValue);
    QByteArray photoData;
    if (!pixmap.isNull()) {
        QBuffer buffer(&photoData);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");
    }
    query.bindValue(":photo", photoData);
    query.bindValue(":id", this->currentID);

    if (!query.exec()) {
        qDebug() << "Ошибка сохранения данных объявления:" << query.lastError().text();
    }

    QMessageBox::information(nullptr, "Статус операции", "Данные объявления обновлены!");
}

void EditAnnouncement::archiveAnnouncementData() {
    if (this->currentID <= 0) return;

    QSqlQuery query;
    query.prepare("UPDATE Announcements SET active = :active WHERE id = :id");
    query.bindValue(":active", 0);
    query.bindValue(":id", this->currentID);

    if (!query.exec()) {
        qDebug() << "Ошибка переноса объявления:" << query.lastError().text();
    }

    // Запрос для увеличения количества продаж пользователя в таблице Users
    query.prepare(R"(
        UPDATE Users
        SET sales = sales + 1
        WHERE id = (SELECT id_user FROM Announcements WHERE id = :id)
    )");
    query.bindValue(":id", this->currentID);

    if (!query.exec()) {
        qDebug() << "Ошибка обновления количества продаж:" << query.lastError().text();
    } else {
        keeper->setSalesUser(keeper->getSalesUser() + 1);
        QMessageBox::information(nullptr, "Статус операции", "Объявление перенесено в архив!");
    }
}

void EditAnnouncement::deleteAnnouncementData() {
    if (this->currentID <= 0) return;

    QSqlQuery query;
    query.prepare("DELETE FROM Announcements WHERE id = :id");
    query.bindValue(":id", this->currentID);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления объявления:" << query.lastError().text();
    }

    QMessageBox::information(nullptr, "Статус операции", "Объявление удалено!");
}
