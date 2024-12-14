#include "profile.h"
#include "viewingad.h"
#include "editannouncement.h"

profile::profile(MainWindow *mainWindow, QWidget *parent) : mainWindow(mainWindow), QWidget(parent) {

    keeper->loadFromSettings();
    updateSales();

    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QGridLayout *gridLayout = new QGridLayout(this);

    // Добавляем кнопку "Выход"
    QPushButton *exitButton = new QPushButton("Выход", this);
    exitButton->setObjectName("defaultButton");
    exitButton->setFixedSize(100, 30);

    // Создаём новый layout для кнопки выхода
    QHBoxLayout *exitLayout = new QHBoxLayout();
    exitLayout->addStretch(2);
    exitLayout->addWidget(exitButton);
    exitLayout->setAlignment(Qt::AlignRight);

    // Добавляем строку с кнопкой "Выход" на позицию (0, 0)
    gridLayout->addLayout(exitLayout, 0, 0);

    QWidget *personBlock = new QWidget(this);
    QWidget *personeAdversBlock = new QWidget(this);

    gridLayout->addWidget(personBlock, 1, 0);
    gridLayout->addWidget(personeAdversBlock, 2, 0);

    QHBoxLayout *userInfoLayout = new QHBoxLayout(personBlock);
    QGridLayout *salesLayout = new QGridLayout();

    int salesUser = keeper->getSalesUser();
    QString salesCount = QString::number(this->countSales);
    QLabel *salesLabel = new QLabel("Количество продаж", personBlock);
    QLabel *salesValue = new QLabel(salesCount, personBlock);

    salesLabel->setAlignment(Qt::AlignCenter);
    salesValue->setAlignment(Qt::AlignCenter);

    salesLayout->addWidget(salesLabel, 0, 0, Qt::AlignBottom);
    salesLayout->addWidget(salesValue, 1, 0, Qt::AlignTop);

    QGridLayout *avatarLayout = new QGridLayout();
    avatarLayout->setContentsMargins(0, 20, 0, 0);

    QLabel *avatarLabel = new QLabel(personBlock);
    avatarLabel->setObjectName("profileAvatar");

    QPixmap originalPixmap(":/avatar/user");
    avatarLabel->setPixmap(createRoundedPixmap(originalPixmap, 90).scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QString FullName = keeper->getNamePerson() + " " + keeper->getSurnamePerson();

    QLabel *nameLabel = new QLabel(FullName, personBlock);
    nameLabel->setContentsMargins(0, 10, 0, 0);
    nameLabel->setAlignment(Qt::AlignCenter);

    avatarLayout->addWidget(avatarLabel, 0, 0, Qt::AlignCenter);
    avatarLayout->addWidget(nameLabel, 1, 0, Qt::AlignTop);

    QVBoxLayout *ratingLayout = new QVBoxLayout(personBlock);
    ratingLayout->setAlignment(Qt::AlignCenter);

    QLabel *ratingLabel = new QLabel("Рейтинг", personBlock);
    ratingLabel->setAlignment(Qt::AlignCenter);

    QGridLayout *starsGridLayout = new QGridLayout();
    starsGridLayout->setSpacing(5);
    starsGridLayout->setContentsMargins(0, 0, 0, 0);

    // Доработать систему отображения рейтинга
    for (int i = 0; i < 5; i++) {
        QLabel *ratingStar = new QLabel();

        if (keeper->getRatingUser() > i) {
            ratingStar->setPixmap(QPixmap(":/icons/star_full").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }else {
            ratingStar->setPixmap(QPixmap(":/icons/star_empty").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        ratingStar->setFixedSize(20, 20);

        starsGridLayout->addWidget(ratingStar, 0, i, Qt::AlignCenter);
    }

    ratingLayout->addWidget(ratingLabel, 0, Qt::AlignCenter);
    ratingLayout->addLayout(starsGridLayout);

    userInfoLayout->addLayout(salesLayout);
    userInfoLayout->addLayout(avatarLayout);
    userInfoLayout->addLayout(ratingLayout);

    QVBoxLayout *advertsMainLayout = new QVBoxLayout(personeAdversBlock);
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setContentsMargins(20, 0, 0, 0);

    QPushButton *activeAdvertsButton = new QPushButton("Активные", personeAdversBlock);
    activeAdvertsButton->setObjectName("defaultColorButton");
    activeAdvertsButton->setFixedSize(100, 30);

    QPushButton *archiveAdvertsButton = new QPushButton("Архив", personeAdversBlock);
    archiveAdvertsButton->setObjectName("defaultButton");
    archiveAdvertsButton->setFixedSize(100, 30);

    buttonsLayout->addWidget(activeAdvertsButton);
    buttonsLayout->addWidget(archiveAdvertsButton);
    buttonsLayout->setAlignment(Qt::AlignLeft);

    QStackedWidget *advertsListWidget = new QStackedWidget(personeAdversBlock);
    advertsListWidget->setStyleSheet("background: #D6D6D6");

    // временно лежат тут (возможен перенос)
    QWidget *activeAdvertsWidget = new QWidget();
    QWidget *archiveAdvertsWidget = new QWidget();

    advertsListWidget->addWidget(activeAdvertsWidget);
    advertsListWidget->addWidget(archiveAdvertsWidget);

    activeAdvertsWidget->setStyleSheet("background: #6771E0");
    archiveAdvertsWidget->setStyleSheet("background: #D6D6D6");

    QVBoxLayout *activeAdvertsLayout = new QVBoxLayout(activeAdvertsWidget);
    QVBoxLayout *archiveAdvertsLayout = new QVBoxLayout(archiveAdvertsWidget);

    // Active block
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background: white; border:none;");

    scrollContent = new QWidget(scrollArea);
    contentLayout = new QGridLayout(scrollContent);
    contentLayout->setSpacing(10);
    contentLayout->setContentsMargins(10, 10, 10, 10);

    scrollContent->setLayout(contentLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);

    activeAdvertsLayout->addWidget(scrollArea);

    // Archive block
    QScrollArea *scrollAreaArchive = new QScrollArea(this);
    scrollAreaArchive->setStyleSheet("background: white; border:none;");

    scrollArchiveContent = new QWidget(scrollAreaArchive);
    contentArchiveLayout = new QGridLayout(scrollArchiveContent);
    contentArchiveLayout->setSpacing(10);
    contentArchiveLayout->setContentsMargins(10, 10, 10, 10);

    scrollArchiveContent->setLayout(contentArchiveLayout);
    scrollAreaArchive->setWidget(scrollArchiveContent);
    scrollAreaArchive->setWidgetResizable(true);

    archiveAdvertsLayout->addWidget(scrollAreaArchive);

    advertsMainLayout->addLayout(buttonsLayout);
    advertsMainLayout->addWidget(advertsListWidget);

    gridLayout->setRowStretch(0, 0);
    gridLayout->setRowStretch(1, 1);
    gridLayout->setRowStretch(2, 4);
    gridLayout->setColumnStretch(0, 1);

    // <--- Connects --->

    connect(activeAdvertsButton, &QPushButton::clicked, this, [=]() {
        loadActiveAnnouncements();
        advertsListWidget->setCurrentWidget(activeAdvertsWidget);
    });

    connect(archiveAdvertsButton, &QPushButton::clicked, this, [=]() {
        loadArchiveAnnouncements();
        advertsListWidget->setCurrentWidget(archiveAdvertsWidget);
    });

    connect(exitButton, &QPushButton::clicked, this, [=]() {
        QSettings settings("bydn", "noticeboard");
        settings.clear();

        QCoreApplication::quit();  // Завершаем выполнение приложения

        // Перезапуск приложения
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    });
}

QPixmap profile::createRoundedPixmap(const QPixmap &src, int radius) {
    QPixmap roundedPixmap(src.size());
    roundedPixmap.fill(Qt::transparent);

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addEllipse(0, 0, src.width(), src.height());
    painter.setClipPath(path);

    painter.drawPixmap(0, 0, src);
    return roundedPixmap;
}

void profile::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    updateSales();
    loadActiveAnnouncements();
    loadArchiveAnnouncements();
}

void profile::updateSales() {
    int currentUserId = keeper->getUserID();

    QSqlQuery query;
    query.prepare("SELECT sales FROM Users WHERE id = :id_user");
    query.bindValue(":id_user", currentUserId);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        this->countSales = query.value("sales").toInt();
    } else {
        qDebug() << "Не удалось найти пользователя с таким ID.";
    }
}

void profile::loadActiveAnnouncements() {
    QLayoutItem *child;
    while ((child = contentLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    int currentUserId = keeper->getUserID();
    int statusActive = 1;

    QSqlQuery query;
    query.prepare(R"(
        SELECT Announcements.id, Announcements.title, Announcements.cost,
               Announcements.location, Announcements.photo
        FROM Announcements
        WHERE Announcements.id_user = :id_user AND Announcements.active = :is_active
    )");
    query.bindValue(":id_user", currentUserId);
    query.bindValue(":is_active", statusActive);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    bool hasResults = false;
    int columnCount = 4;
    int row = 0;
    int col = 0;

    while(query.next()) {
        hasResults = true;

        int advertId = query.value("id").toInt();
        QString title = query.value("title").toString();
        double cost = query.value("cost").toDouble();
        QString location = query.value("location").toString().split(",").first();
        QByteArray photoData = query.value("photo").toByteArray();

        QWidget *advertCard = new QWidget(scrollContent);
        advertCard->setFixedSize(240, 320);
        advertCard->setStyleSheet("background: #F3F3F3;");
        advertCard->setObjectName("CardWidget");

        QVBoxLayout *cardLayout = new QVBoxLayout(advertCard);
        cardLayout->setSpacing(5);
        cardLayout->setContentsMargins(5, 10, 5, 5);

        QHBoxLayout *imageLayout = new QHBoxLayout();
        imageLayout->setContentsMargins(0, 0, 0, 0);

        QLabel *photoLabel = new QLabel(advertCard);
        photoLabel->setAlignment(Qt::AlignCenter);
        QPixmap pixmap;
        if (pixmap.loadFromData(photoData)) {
            photoLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            photoLabel->setText("Нет изображения");
            photoLabel->setAlignment(Qt::AlignCenter);
        }
        imageLayout->addWidget(photoLabel);

        cardLayout->addLayout(imageLayout);

        QLabel *titleLabel = new QLabel(title, advertCard);
        titleLabel->setObjectName("titleCard");
        cardLayout->addWidget(titleLabel);

        QLabel *costLabel = new QLabel(QString("%1 руб.").arg(cost), advertCard);
        costLabel->setObjectName("costCard");
        cardLayout->addWidget(costLabel);

        QLabel *locationLabel = new QLabel(location, advertCard);
        locationLabel->setObjectName("locationCard");
        cardLayout->addWidget(locationLabel);

        QHBoxLayout *buttonLayout = new QHBoxLayout();

        QPushButton *ebitButton = new QPushButton("Редактировать", advertCard);
        ebitButton->setObjectName("cardButton");

        QPushButton *viewButton = new QPushButton("Посмотреть", advertCard);
        viewButton->setObjectName("cardButton");

        buttonLayout->addStretch();
        buttonLayout->addWidget(ebitButton);
        buttonLayout->addWidget(viewButton);

        cardLayout->addLayout(buttonLayout);
        advertCard->setLayout(cardLayout);

        contentLayout->addWidget(advertCard, row, col);

        col++;
        if (col >= columnCount) {
            col = 0;
            row++;
        }

        connect(ebitButton, &QPushButton::clicked, this, [=]() {
            QStackedWidget* stackedWidget = mainWindow->getStackedWidget();

            EditAnnouncement* editPage = qobject_cast<EditAnnouncement*>(stackedWidget->widget(6));

            editPage->setIDAnnouncement(advertId);

            stackedWidget->setCurrentIndex(6);
        });

        connect(viewButton, &QPushButton::clicked, this, [=]() {
            QStackedWidget* stackedWidget = mainWindow->getStackedWidget();

            keeper->setSelectedAnnouncemen(advertId);

            viewingad* viewWidget = qobject_cast<viewingad*>(stackedWidget->widget(5));
            if (viewWidget) {
                viewWidget->loadAdData(advertId);
            }
            stackedWidget->setCurrentIndex(5);
        });

    }


    // Если объявлений нет, показываем сообщение "Нет объявлений"
    if (!hasResults) {
        QLabel* noResultsLabel = new QLabel("Нет объявлений");
        noResultsLabel->setAlignment(Qt::AlignCenter);
        contentLayout->addWidget(noResultsLabel, 0, 0, 1, columnCount);
    }
}

void profile::loadArchiveAnnouncements() {
    QLayoutItem *child;
    while ((child = contentArchiveLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    int currentUserId = keeper->getUserID();
    int statusActive = 0;

    QSqlQuery query;
    query.prepare(R"(
        SELECT Announcements.id, Announcements.title, Announcements.cost,
               Announcements.location, Announcements.photo
        FROM Announcements
        WHERE Announcements.id_user = :id_user AND Announcements.active = :is_active
    )");
    query.bindValue(":id_user", currentUserId);
    query.bindValue(":is_active", statusActive);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }


    bool hasResults = false;
    int columnCount = 4;
    int row = 0;
    int col = 0;

    while(query.next()) {
        hasResults = true;

        int advertId = query.value("id").toInt();
        QString title = query.value("title").toString();
        double cost = query.value("cost").toDouble();
        QString location = query.value("location").toString().split(",").first();
        QByteArray photoData = query.value("photo").toByteArray();

        QWidget *advertCard = new QWidget(scrollContent);
        advertCard->setFixedSize(240, 320);
        advertCard->setStyleSheet("background: #F3F3F3;");
        advertCard->setObjectName("CardWidget");

        QVBoxLayout *cardLayout = new QVBoxLayout(advertCard);
        cardLayout->setSpacing(5);
        cardLayout->setContentsMargins(5, 10, 5, 5);

        QHBoxLayout *imageLayout = new QHBoxLayout();
        imageLayout->setContentsMargins(0, 0, 0, 0);

        QLabel *photoLabel = new QLabel(advertCard);
        photoLabel->setAlignment(Qt::AlignCenter);
        QPixmap pixmap;
        if (pixmap.loadFromData(photoData)) {
            photoLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            photoLabel->setText("Нет изображения");
            photoLabel->setAlignment(Qt::AlignCenter);
        }
        imageLayout->addWidget(photoLabel);

        cardLayout->addLayout(imageLayout);

        QLabel *titleLabel = new QLabel(title, advertCard);
        titleLabel->setObjectName("titleCard");
        cardLayout->addWidget(titleLabel);

        QLabel *costLabel = new QLabel(QString("%1 руб.").arg(cost), advertCard);
        costLabel->setObjectName("costCard");
        cardLayout->addWidget(costLabel);

        QLabel *locationLabel = new QLabel(location, advertCard);
        locationLabel->setObjectName("locationCard");
        cardLayout->addWidget(locationLabel);

        QHBoxLayout *buttonLayout = new QHBoxLayout();

        QPushButton *ebitButton = new QPushButton("Редактировать", advertCard);
        ebitButton->setObjectName("cardButton");

        QPushButton *viewButton = new QPushButton("Посмотреть", advertCard);
        viewButton->setObjectName("cardButton");

        buttonLayout->addStretch();
        buttonLayout->addWidget(ebitButton);
        buttonLayout->addWidget(viewButton);

        cardLayout->addLayout(buttonLayout);
        advertCard->setLayout(cardLayout);

        contentArchiveLayout->addWidget(advertCard, row, col);

        col++;
        if (col >= columnCount) {
            col = 0;
            row++;
        }

        connect(ebitButton, &QPushButton::clicked, this, [=]() {
            QStackedWidget* stackedWidget = mainWindow->getStackedWidget();

            EditAnnouncement* editPage = qobject_cast<EditAnnouncement*>(stackedWidget->widget(6));

            editPage->setIDAnnouncement(advertId);

            stackedWidget->setCurrentIndex(6);
        });

        connect(viewButton, &QPushButton::clicked, this, [=]() {
            QStackedWidget* stackedWidget = mainWindow->getStackedWidget();

            keeper->setSelectedAnnouncemen(advertId);

            viewingad* viewWidget = qobject_cast<viewingad*>(stackedWidget->widget(5));
            if (viewWidget) {
                viewWidget->loadAdData(advertId);
            }
            stackedWidget->setCurrentIndex(5);
        });

    }


    // Если объявлений нет, показываем сообщение "Нет объявлений"
    if (!hasResults) {
        QLabel* noResultsLabel = new QLabel("Нет объявлений");
        noResultsLabel->setAlignment(Qt::AlignCenter);
        contentArchiveLayout->addWidget(noResultsLabel, 0, 0, 1, columnCount);
    }
}
