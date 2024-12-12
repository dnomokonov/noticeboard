#include "profile.h"

profile::profile(QWidget *parent) : QWidget(parent) {

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

    // Описание activeAdvertsWidget и archiveAdvertsWidget

    activeAdvertsWidget->setStyleSheet("background: #D6D6D6");
    archiveAdvertsWidget->setStyleSheet("background: #6771E0");

    // ---

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
