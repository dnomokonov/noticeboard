    #include "createadvertising.h"

createadvertising::createadvertising(QWidget *parent, MainWindow *mainwindow) : QWidget(parent), mainWindow(mainwindow) {
    keeper->loadFromSettings();

    qDebug() << "UserID keeper:" << keeper->getUserID();

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
    QLineEdit *titleEdit = new QLineEdit();
    titleEdit->setFixedWidth(550);
    titleEdit->setObjectName("customFieldCreateAd");
    titleEdit->setPlaceholderText("Введите заголовок объявления");

    QLabel *descriptionLabel = new QLabel("Описание:");
    descriptionLabel->setObjectName("titleLabelCreateBlock");
    QTextEdit *descriptionEdit = new QTextEdit();
    descriptionEdit->setFixedWidth(550);
    descriptionEdit->setObjectName("customFieldCreateAd");
    descriptionEdit->setPlaceholderText("Введите описание объявления");

    QLabel *categoryLabel = new QLabel("Категория:");
    categoryLabel->setObjectName("titleLabelCreateBlock");
    QComboBox *categoryCombo = new QComboBox();
    categoryCombo->setObjectName("categoryCustom");
    categoryCombo->setFixedWidth(200);
    categoryCombo->addItems({"Электроника", "Одежда", "Дом и сад", "Авто", "Недвижимость", "Услуги"});

    QLabel *priceLabel = new QLabel("Цена:");
    priceLabel->setObjectName("titleLabelCreateBlock");

    QLineEdit *priceEdit = new QLineEdit();
    priceEdit->setFixedWidth(550);
    priceEdit->setObjectName("customFieldCreateAd");
    priceEdit->setPlaceholderText("Введите цену");
    // priceEdit->setValidator(new QDoubleValidator(0, 1000000, 2, this));

    QDoubleValidator *validator = new QDoubleValidator(0, 1000000, 2, this);
    validator->setLocale(QLocale::C);
    QLocale locale = QLocale(QLocale::Russian);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    validator->setLocale(locale);
    priceEdit->setValidator(validator);

    QLabel *phoneLabel = new QLabel("Номер телефона:");
    phoneLabel->setObjectName("titleLabelCreateBlock");
    QLineEdit *phoneEdit = new QLineEdit();
    phoneEdit->setMaxLength(12);
    phoneEdit->setFixedWidth(550);
    phoneEdit->setObjectName("customFieldCreateAd");
    phoneEdit->setPlaceholderText("Введите номер телефона");

    QLabel *addressLabel = new QLabel("Адрес:");
    addressLabel->setObjectName("titleLabelCreateBlock");
    QLineEdit *cityEdit = new QLineEdit();
    cityEdit->setFixedWidth(225);
    cityEdit->setObjectName("customFieldCreateAd");
    cityEdit->setPlaceholderText("Город");
    QLineEdit *streetEdit = new QLineEdit();
    streetEdit->setFixedWidth(225);
    streetEdit->setObjectName("customFieldCreateAd");
    streetEdit->setPlaceholderText("Улица");
    QLineEdit *houseEdit = new QLineEdit();
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

    QLabel *imageDisplay = new QLabel();
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

    QPushButton *submitButton = new QPushButton("Опубликовать");
    submitButton->setFixedSize(130, 35);
    submitButton->setObjectName("createAdButton");

    QHBoxLayout *cancelAndClearLayout = new QHBoxLayout();
    cancelAndClearLayout->setSpacing(10);

    QPushButton *clearButton = new QPushButton("Очистить");
    clearButton->setFixedSize(100, 35);
    clearButton->setObjectName("clearButton");
    cancelAndClearLayout->addWidget(clearButton, Qt::AlignCenter);

    QPushButton *cancelButton = new QPushButton("Отмена");
    cancelButton->setFixedSize(100, 35);
    cancelButton->setObjectName("cancelButton");
    cancelAndClearLayout->addWidget(cancelButton, Qt::AlignCenter);

    gridLayout->addWidget(submitButton, 12, 0, Qt::AlignLeft);
    gridLayout->addLayout(cancelAndClearLayout, 12, 0, Qt::AlignRight);

    gridLayout->setHorizontalSpacing(30);
    gridLayout->setVerticalSpacing(10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *centerLayout = new QVBoxLayout();
    centerLayout->addWidget(mainContainer, Qt::AlignCenter, Qt::AlignCenter);
    mainLayout->addLayout(centerLayout);
    setLayout(mainLayout);

    connect(submitButton, &QPushButton::clicked, this, [=]() {
        QString title = titleEdit->text();
        QString description = descriptionEdit->toPlainText();
        QString category = categoryCombo->currentText();

        QLocale locale = QLocale(QLocale::Russian);
        double cost = locale.toDouble(priceEdit->text());

        QString phone = phoneEdit->text();
        QString location = cityEdit->text() + ", " + streetEdit->text() + ", " + houseEdit->text();

        qDebug() << "Cost = " << cost;

        if (title.isEmpty() || description.isEmpty() || category.isEmpty() || cost <= 0 || phone.isEmpty() || location.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все обязательные поля.");
            return;
        }

        qDebug() << "Phone: " << phone;

        QRegularExpression phoneRegex("^\\+7\\d{10}$");
        if (!phoneRegex.match(phone).hasMatch()) {
            QMessageBox::warning(this, "Ошибка", "Введите номер телефона в формате +7XXXXXXXXXX.");
            return;
        }

        QPixmap pixmap = imageDisplay->pixmap();
        if (pixmap.isNull()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, загрузите изображение.");
            return;
        }

        QByteArray imageBytes;
        QBuffer buffer(&imageBytes);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");

        QSqlQuery query;
        query.prepare("INSERT INTO Announcements (id_user, title, description, category, cost, phone, location, photo) "
                      "VALUES (:id_user, :title, :description, :category, :cost, :phone, :location, :photo)");
        query.bindValue(":id_user", keeper->getUserID());
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":category", category);
        query.bindValue(":cost", cost);
        query.bindValue(":phone", phone);
        query.bindValue(":location", location);
        query.bindValue(":photo", imageBytes);

        if (!query.exec()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить объявление: " + query.lastError().text());
        } else {
            QMessageBox::information(this, "Успех", "Объявление успешно добавлено!");

            titleEdit->clear();
            descriptionEdit->clear();
            categoryCombo->setCurrentIndex(0);
            priceEdit->clear();
            phoneEdit->clear();
            cityEdit->clear();
            streetEdit->clear();
            houseEdit->clear();
            imageDisplay->clear();
        }
    });

    connect(uploadImageButton, &QPushButton::clicked, this, [=]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Выберите изображение", "", "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!filePath.isEmpty()) {
            QPixmap pixmap(filePath);
            if (!pixmap.isNull()) {
                imageDisplay->setPixmap(pixmap.scaled(imageDisplay->size(), Qt::KeepAspectRatio));
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение.");
            }
        }
    });

    connect(cancelButton, &QPushButton::clicked, this, [=]() {
        if (mainwindow) {
            QStackedWidget *stackedWidget = mainwindow->getStackedWidget();
            stackedWidget->setCurrentIndex(0);
        }
    });

    connect(clearButton, &QPushButton::clicked, this, [=]() {
        titleEdit->clear();
        descriptionEdit->clear();
        categoryCombo->setCurrentIndex(0);
        priceEdit->clear();
        phoneEdit->clear();
        cityEdit->clear();
        streetEdit->clear();
        houseEdit->clear();
    });

}
