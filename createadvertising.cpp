    #include "createadvertising.h"

createadvertising::createadvertising(QWidget *parent, MainWindow *mainwindow) : QWidget(parent), mainWindow(mainwindow) {
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
    priceEdit->setValidator(new QDoubleValidator(0, 1000000, 2, this));

    QLabel *phoneLabel = new QLabel("Номер телефона:");
    phoneLabel->setObjectName("titleLabelCreateBlock");
    QLineEdit *phoneEdit = new QLineEdit();
    phoneEdit->setMaxLength(15);
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

    connect(cancelButton, &QPushButton::clicked, this, [=]() {
        if (mainwindow) {
            QStackedWidget *stackedWidget = mainwindow->getStackedWidget();
            stackedWidget->setCurrentIndex(0);
        } else {
            qDebug() << "MainWindow is nullptr!";
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
