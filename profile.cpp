#include "profile.h"
#include "viewingad.h"

profile::profile(MainWindow *mainWindow, QWidget *parent) : mainWindow(mainWindow), QWidget(parent) {

    keeper->loadFromSettings();

    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QGridLayout *gridLayout = new QGridLayout(this);

    QWidget *personBlock = new QWidget(this);
    QWidget *personeAdversBlock = new QWidget(this);

    gridLayout->addWidget(personBlock, 0, 0);
    gridLayout->addWidget(personeAdversBlock, 1, 0);

    QHBoxLayout *userInfoLayout = new QHBoxLayout(personBlock);
    QGridLayout *salesLayout = new QGridLayout();

    int salesUser = keeper->getSalesUser();
    QString salesCount = QString::number(salesUser);
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

    activeAdvertsWidget->setStyleSheet("background: #D6D6D6");
    archiveAdvertsWidget->setStyleSheet("background: #6771E0");

    // QScrollArea* activeScrollArea = new QScrollArea(activeAdvertsWidget);
    // activeScrollArea->setWidgetResizable(true); // Позволяет содержимому прокручивать область
    // QWidget* activeContentWidget = new QWidget(); // Контейнер для содержимого
    // QVBoxLayout* activeLayout = new QVBoxLayout(activeContentWidget); // Макет содержимого
    // activeContentWidget->setLayout(activeLayout);

    // // Настраиваем QScrollArea
    // activeScrollArea->setWidget(activeContentWidget);
    // activeScrollArea->setWidgetResizable(true); // Устанавливаем размер совпадающий с виджетом

    // // Аналогично для archiveAdvertsWidget
    // QScrollArea* archiveScrollArea = new QScrollArea(archiveAdvertsWidget);
    // archiveScrollArea->setWidgetResizable(true);
    // QWidget* archiveContentWidget = new QWidget();
    // QVBoxLayout* archiveLayout = new QVBoxLayout(archiveContentWidget);
    // archiveContentWidget->setLayout(archiveLayout);

    // archiveScrollArea->setWidget(archiveContentWidget);
    // archiveScrollArea->setWidgetResizable(true);

    advertsMainLayout->addLayout(buttonsLayout);
    advertsMainLayout->addWidget(advertsListWidget);

    gridLayout->setRowStretch(0, 1);
    gridLayout->setRowStretch(1, 2);
    gridLayout->setColumnStretch(0, 1);

    // <--- Connects --->

    connect(activeAdvertsButton, &QPushButton::clicked, this, [=]() {
        advertsListWidget->setCurrentWidget(activeAdvertsWidget);
    });

    connect(archiveAdvertsButton, &QPushButton::clicked, this, [=]() {
        advertsListWidget->setCurrentWidget(archiveAdvertsWidget);
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

}

void profile::loadAnnouncements(QWidget* container, bool isActive) {
    int currentUserId = keeper->getUserID();

    QSqlQuery query;
    query.prepare(R"(
        SELECT Announcements.id, Announcements.title, Announcements.cost,
               Announcements.location, Announcements.photo
        FROM Announcements
        WHERE Announcements.id_user = :id_user AND Announcements.active = :is_active
    )");
    query.bindValue(":id_user", currentUserId);
    query.bindValue(":is_active", isActive);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return;
    }

    int columnCount = 4;
    int row = 0;
    int col = 0;

    while (query.next()) {
        int advertId = query.value("id").toInt();
        QString title = query.value("title").toString();
        double cost = query.value("cost").toDouble();
        QString location = query.value("location").toString().split(",").first();
        QByteArray photoData = query.value("photo").toByteArray();

        QWidget* advertCard = new QWidget(container);
        advertCard->setFixedSize(240, 320);
        advertCard->setStyleSheet("background: #F3F3F3;");

        QVBoxLayout* cardLayout = new QVBoxLayout(advertCard);
        cardLayout->setSpacing(5);
        cardLayout->setContentsMargins(5, 10, 5, 5);

        QLabel* photoLabel = new QLabel(advertCard);
        photoLabel->setAlignment(Qt::AlignCenter);
        QPixmap pixmap;
        if (pixmap.loadFromData(photoData)) {
            photoLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            photoLabel->setText("Нет изображения");
        }
        cardLayout->addWidget(photoLabel);

        QLabel* titleLabel = new QLabel(title, advertCard);
        titleLabel->setObjectName("titleCard");
        cardLayout->addWidget(titleLabel);

        QLabel* costLabel = new QLabel(QString("%1 руб.").arg(cost), advertCard);
        costLabel->setObjectName("costCard");
        cardLayout->addWidget(costLabel);

        QLabel* locationLabel = new QLabel(location, advertCard);
        locationLabel->setObjectName("locationCard");
        cardLayout->addWidget(locationLabel);

        QPushButton* viewButton = new QPushButton("Посмотреть", advertCard);
        viewButton->setObjectName("cardButton");
        cardLayout->addWidget(viewButton);

        connect(viewButton, &QPushButton::clicked, this, [=]() {
            QStackedWidget* stackedWidget = mainWindow->getStackedWidget();

            keeper->setSelectedAnnouncemen(advertId);

            viewingad* viewWidget = qobject_cast<viewingad*>(stackedWidget->widget(5));
            if (viewWidget) {
                viewWidget->loadAdData(advertId);
            }
            stackedWidget->setCurrentIndex(5);
        });

        col++;
        if (col >= columnCount) {
            col = 0;
            row++;
        }
    }
}
