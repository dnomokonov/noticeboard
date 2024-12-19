#include "viewingad.h"

viewingad::viewingad(MainWindow *mainWindow, QWidget *parent)
    : QWidget(parent), mainWindow(mainWindow) {

    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *centerLayout = new QVBoxLayout();

    QWidget *mainContainer = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(mainContainer);
    mainContainer->setObjectName("AnnouncementBlock");
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(30, 10, 30, 10);

    titleLabel = new QLabel(mainContainer);
    titleLabel->setObjectName("AnnouncementTitle");

    descriptionLabel = new QLabel(mainContainer);
    descriptionLabel->setObjectName("AnnouncementDesc");

    costLabel = new QLabel(mainContainer);
    costLabel->setObjectName("AnnouncementCost");

    phoneLabel = new QLabel(mainContainer);
    phoneLabel->setObjectName("AnnouncementPhone");

    categoryLabel = new QLabel(mainContainer);
    categoryLabel->setObjectName("AnnouncementCategory");

    locationLabel = new QLabel(mainContainer);

    QLabel *descriptionHeader = new QLabel("Описание:", mainContainer);

    QLabel *costHeader = new QLabel("Цена:", mainContainer);
    costHeader->setFixedWidth(40);

    QLabel *phonenHeader = new QLabel("Тел.:", mainContainer);
    phonenHeader->setFixedWidth(30);

    QLabel *categoryHeader = new QLabel("Категория товара:", mainContainer);
    categoryHeader->setFixedWidth(120);

    QLabel *locationHeader = new QLabel("Адрес:", mainContainer);
    locationHeader->setFixedWidth(50);

    photoLabel = new QLabel(mainContainer);
    photoLabel->setObjectName("uploadImageBlock");
    photoLabel->setFixedSize(380, 380);
    photoLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout *costLayout = new QHBoxLayout();
    costLayout->addWidget(costHeader);
    costLayout->addWidget(costLabel);

    QHBoxLayout *categoryLayout = new QHBoxLayout();
    categoryLayout->addWidget(categoryHeader);
    categoryLayout->addWidget(categoryLabel);

    QHBoxLayout *phoneLayout = new QHBoxLayout();
    phoneLayout->addWidget(phonenHeader);
    phoneLayout->addWidget(phoneLabel);

    QHBoxLayout *locationLayout = new QHBoxLayout();
    locationLayout->addWidget(locationHeader);
    locationLayout->addWidget(locationLabel);

    sellerWidget = new QWidget(mainContainer);
    sellerLayout = new QGridLayout(sellerWidget);
    sellerHeader = new QLabel("Продавец:");
    sellerBlock = new QGridLayout(sellerWidget);
    sellerFullName = new QLabel(sellerWidget);

    QLabel *sellerAvatar = new QLabel();
    sellerAvatar->setObjectName("sellerAvatar");
    sellerAvatar->setFixedSize(60, 60);
    QPixmap sellerAvatarPixmap(":/avatar/user");
    sellerAvatar->setPixmap(createRoundedPixmap(sellerAvatarPixmap, 90).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    sellerLayout->addWidget(sellerAvatar, 1, 0);

    gridLayout->addWidget(titleLabel, 0, 0);
    gridLayout->addLayout(costLayout, 2, 0);
    gridLayout->addWidget(descriptionHeader, 3, 0);
    gridLayout->addWidget(descriptionLabel, 4, 0);
    gridLayout->addWidget(sellerWidget, 6, 0);
    gridLayout->addLayout(phoneLayout, 7, 0);
    gridLayout->addLayout(categoryLayout, 10, 0);
    gridLayout->addLayout(locationLayout, 11, 0);

    gridLayout->addWidget(photoLabel, 2, 1, 11, 1, Qt::AlignTop);

    centerLayout->addWidget(mainContainer, 0, Qt::AlignCenter);
    mainLayout->addLayout(centerLayout);
    setLayout(mainLayout);
}

void viewingad::loadAdData(int announcementID) {
    QSqlQuery query;

    query.prepare("SELECT title, description, cost, phone, category, location, photo, id_user FROM Announcements WHERE id = :id");
    query.bindValue(":id", announcementID);

    if (query.exec() && query.next()) {
        QString title = query.value("title").toString();
        QString description = query.value("description").toString();
        double cost = query.value("cost").toDouble();
        QString phone = query.value("phone").toString();
        QString category = query.value("category").toString();
        QString location = query.value("location").toString();
        QByteArray photoData = query.value("photo").toByteArray();
        int userId = query.value("id_user").toInt();

        titleLabel->setText(title);
        descriptionLabel->setText(description);
        costLabel->setText(QString("%1 руб.").arg(cost));
        phoneLabel->setText(phone);
        categoryLabel->setText(category);
        locationLabel->setText(location);

        QPixmap pixmap;
        if (pixmap.loadFromData(photoData)) {
            photoLabel->setPixmap(pixmap);
        } else {
            photoLabel->setText("No image available");
        }

        query.prepare("SELECT name, surname, rating FROM Users WHERE id = :id");
        query.bindValue(":id", userId);

        if (query.exec() && query.next()) {
            QString name = query.value("name").toString();
            QString surname = query.value("surname").toString();
            double rating = query.value("rating").toDouble();

            sellerFullName->setText(name + " " + surname);

            QGridLayout *starsGridLayout = new QGridLayout();
            starsGridLayout->setSpacing(5);
            starsGridLayout->setContentsMargins(0, 0, 0, 0);

            for (int i = 0; i < 5; i++) {
                QLabel *ratingStar = new QLabel();
                if (i < rating) {
                    ratingStar->setPixmap(QPixmap(":/icons/star_full").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                } else {
                    ratingStar->setPixmap(QPixmap(":/icons/star_empty").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
                ratingStar->setFixedSize(20, 20);
                starsGridLayout->addWidget(ratingStar, 0, i, Qt::AlignCenter);
            }

            sellerBlock->addWidget(sellerFullName, 0, 0);
            sellerBlock->addLayout(starsGridLayout, 1, 0, Qt::AlignLeft);

            sellerLayout->addWidget(sellerHeader, 0, 0);
            sellerLayout->addLayout(sellerBlock, 1, 1);
        } else {
            qDebug() << "Error fetching user data:" << query.lastError().text();
        }
    } else {
        qDebug() << "Error fetching ad data:" << query.lastError().text();
    }
}

QPixmap viewingad::createRoundedPixmap(const QPixmap &src, int radius) {
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
