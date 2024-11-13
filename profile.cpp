#include "profile.h"

profile::profile(QWidget *parent) : QWidget(parent) {
    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QGridLayout *gridLayout = new QGridLayout(this);

    QWidget *personBlock = new QWidget(this);
    QWidget *personeAdversBlock = new QWidget(this);

    personBlock->setStyleSheet("background-color: #f5f5f5;");
    personeAdversBlock->setStyleSheet("background-color: #e0e0e0;");

    gridLayout->addWidget(personBlock, 0, 0);
    gridLayout->addWidget(personeAdversBlock, 1, 0);

    QHBoxLayout *userInfoLayout = new QHBoxLayout(personBlock);

    QVBoxLayout *salesLayout = new QVBoxLayout();
    QLabel *salesLabel = new QLabel("Количество продаж", personBlock);
    QLabel *salesValue = new QLabel("150", personBlock);
    salesLayout->addWidget(salesLabel);
    salesLayout->addWidget(salesValue);

    QVBoxLayout *avatarLayout = new QVBoxLayout();
    QLabel *avatarLabel = new QLabel(personBlock);
    avatarLabel->setPixmap(QPixmap(":/avatar/ava").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QLabel *nameLabel = new QLabel("{Name} {Surname}", personBlock);
    avatarLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);
    avatarLayout->addWidget(nameLabel, 0, Qt::AlignCenter);

    QVBoxLayout *ratingLayout = new QVBoxLayout(personBlock);
    ratingLayout->setAlignment(Qt::AlignCenter);
    ratingLayout->setSpacing(0);
    ratingLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *ratingLabel = new QLabel("Рейтинг", personBlock);
    ratingLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout *starsLayout = new QHBoxLayout();
    starsLayout->setAlignment(Qt::AlignCenter);
    starsLayout->setSpacing(0);
    starsLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 5; i++) {
        QLabel *ratingStars = new QLabel();
        ratingStars->setPixmap(QPixmap(":/icons/star_empty"));

        qDebug() << "i = " << i;

        starsLayout->addWidget(ratingStars);
    }

    ratingLayout->addWidget(ratingLabel, Qt::AlignCenter);
    ratingLayout->addLayout(starsLayout, Qt::AlignCenter);

    userInfoLayout->addLayout(salesLayout);
    userInfoLayout->addLayout(avatarLayout);
    userInfoLayout->addLayout(ratingLayout);

    gridLayout->setRowStretch(0, 1);
    gridLayout->setRowStretch(1, 2);
    gridLayout->setColumnStretch(0, 1);
}
